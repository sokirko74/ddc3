cmake_minimum_required(VERSION 3.5)

project(ddc VERSION 3.0 LANGUAGES C CXX)
if("${PROJECT_VERSION_PATCH}" STREQUAL "")
    set(DDC_VERSION_MICRO 0)
else()
    set(DDC_VERSION_MICRO ${PROJECT_VERSION_PATCH})
endif()

set (CMAKE_CXX_STANDARD 17)

#-----------------------------------------------------------------------
# options (formerly ./configure --enable-*/--with-*)
option(DDC_ENABLE_MMAP "enable mmap virtual memory support" ON)
option(DDC_JSON_DEEP_CONTEXT "deep encoding of extra-sentential context tokens in JSON output" OFF)
option(DDC_ENABLE_CURL_UNIX_URLS "enable UNIX socket URL parsing for CCurl" ON)
if(CMAKE_BUILD_TYPE MATCHES "Debug")
    set(_ddc_hires_default ON)
else()
    set(_ddc_hires_default OFF)
endif()
option(DDC_USE_HIRES_CLOCK "enable high-resolution clock (requires clock_gettime)" ${_ddc_hires_default})
set(DDC_STATIC_BUFLEN 4096 CACHE STRING "size in bytes of large static internal string buffers")

#-----------------------------------------------------------------------
# system checks (formerly configure.ac) -> ddcConfigAuto.h
include(CheckIncludeFile)
include(CheckFunctionExists)
include(CheckSymbolExists)

foreach(_h malloc.h netdb.h syslog.h sys/mman.h sys/resource.h sys/stat.h sys/types.h unistd.h sys/socket.h sys/un.h)
    string(TOUPPER "HAVE_${_h}" _var)
    string(REGEX REPLACE "[/.]" "_" _var "${_var}")
    check_include_file(${_h} ${_var})
endforeach()

set(CMAKE_REQUIRED_LIBRARIES rt)
check_function_exists(clock_gettime HAVE_CLOCK_GETTIME)
unset(CMAKE_REQUIRED_LIBRARIES)
foreach(_f erand48 jrand48 nrand48 rand_r malloc_trim strerror_r mmap)
    string(TOUPPER "HAVE_${_f}" _var)
    check_function_exists(${_f} ${_var})
endforeach()

if(DDC_ENABLE_MMAP AND NOT (HAVE_SYS_MMAN_H AND HAVE_SYS_STAT_H AND HAVE_MMAP))
    message(WARNING "mmap not available: DDC_ENABLE_MMAP disabled")
    set(DDC_ENABLE_MMAP OFF)
endif()
if(DDC_USE_HIRES_CLOCK AND NOT HAVE_CLOCK_GETTIME)
    message(WARNING "clock_gettime() not found: high-resolution clock disabled")
    set(DDC_USE_HIRES_CLOCK OFF)
endif()

if(HAVE_SYS_TYPES_H AND HAVE_SYS_SOCKET_H AND HAVE_SYS_UN_H)
    set(DDC_HAVE_UNIX_SOCKET_HEADERS ON)
endif()

find_package(pugixml REQUIRED)   # XML parser with XPath (Debian/Ubuntu: libpugixml-dev)
find_package(CURL)
if(CURL_FOUND)
    set(HAVE_LIBCURL ON)
    set(CMAKE_REQUIRED_INCLUDES ${CURL_INCLUDE_DIRS})
    check_symbol_exists(CURLOPT_UNIX_SOCKET_PATH curl/curl.h DDC_HAVE_CURL_UNIX_SUPPORT)
    check_symbol_exists(CURL_SOCKOPT_ALREADY_CONNECTED curl/curl.h DDC_HAVE_CURL_ALREADY_CONNECTED)
    unset(CMAKE_REQUIRED_INCLUDES)
    if(DDC_HAVE_UNIX_SOCKET_HEADERS AND NOT DDC_HAVE_CURL_UNIX_SUPPORT)
        set(DDC_ENABLE_CURL_UNIX_SOCKETS ON)
    endif()
else()
    message(WARNING "libcurl not found: CURL support disabled")
endif()

configure_file(CommonLib/ddcConfigAuto.h.cmake ${CMAKE_BINARY_DIR}/generated/ddcConfigAuto.h)
include_directories(${CMAKE_BINARY_DIR}/generated)
if(CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
endif()

SET (CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -pthread")
SET (FLEX_TOOL flex) 
SET (BISON_TOOL bison) 


if(CMAKE_BUILD_TYPE MATCHES "Debug")
    message ("compile debug")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
    message ("enable_testing")
    enable_testing()
else()
    message ("compile release")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_RELEASE} -O2")
endif()


#-----------------------------------------------------------------------
# nlp_base (git submodule): morphology + common utilities shared with RML
macro (declare_cmake_min_version)
    cmake_minimum_required(VERSION 3.24)
endmacro()
if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/nlp_base/CMakeLists.txt)
    message(FATAL_ERROR "src/nlp_base is empty: run 'git submodule update --init'")
endif()
find_package(ZLIB REQUIRED)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/nlp_base/contrib/plog)
add_subdirectory (nlp_base/contrib/iconv_subset)
add_subdirectory (nlp_base/common)
add_subdirectory (nlp_base/agramtab)
add_subdirectory (nlp_base/morph_wizard)
add_subdirectory (nlp_base/lemmatizer_base_lib)

#-- morphology dictionaries: built from nlp_base/data into ${CMAKE_BINARY_DIR}/dict/Morph/<Language>
#   ($RML/dict/Morph should point there; see Bin/rml.ini)
add_executable(morph_gen nlp_base/morph_gen/morph_gen.cpp)
target_link_libraries(morph_gen lemmatizer_base_lib)
set(DDC_MORPH_DICTS_DIR ${CMAKE_BINARY_DIR}/dict/Morph)
set(_ddc_morph_outputs)
foreach(_lang Russian English German)
    set(_in  ${CMAKE_CURRENT_SOURCE_DIR}/nlp_base/data/${_lang})
    set(_out ${DDC_MORPH_DICTS_DIR}/${_lang})
    set(_files ${_out}/morph.bases ${_out}/morph.annot ${_out}/morph.forms_autom ${_out}/gramtab.json)
    add_custom_command(
        OUTPUT ${_files}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${_out}
        COMMAND ${CMAKE_COMMAND} -E copy ${_in}/gramtab.json ${_out}/gramtab.json
        COMMAND morph_gen --input project.mwz --output-folder ${_out} --postfix-len 5 --min-freq 3
        DEPENDS morph_gen ${_in}/morphs.json ${_in}/project.mwz ${_in}/gramtab.json
        WORKING_DIRECTORY ${_in}
        COMMENT "Building ${_lang} morphology dictionary"
        VERBATIM
    )
    list(APPEND _ddc_morph_outputs ${_files})
endforeach()
add_custom_target(ddc_nlp_bases ALL DEPENDS ${_ddc_morph_outputs})

#-- graphematics and structural dictionaries (Ross) from nlp_base (nlp_base)
add_subdirectory (nlp_base/dicts/StructDictLib)
add_subdirectory (nlp_base/dicts/StructDictLoader)
add_subdirectory (nlp_base/graphan/GraphanLib)

#-- graphematical dictionaries: ${CMAKE_BINARY_DIR}/dict/GraphAn (plain files) and the binary
#   dictionaries of fixed expressions ${CMAKE_BINARY_DIR}/dict/{Obor,GerObor,EngObor}
#   ($RML/dict should point there; see Bin/rml.ini)
set(DDC_DICTS_DIR ${CMAKE_BINARY_DIR}/dict)
set(_ddc_graphan_outputs)
file(GLOB _graphan_files ${CMAKE_CURRENT_SOURCE_DIR}/nlp_base/data/GraphAn/*)
foreach(_f ${_graphan_files})
    get_filename_component(_n ${_f} NAME)
    add_custom_command(
        OUTPUT ${DDC_DICTS_DIR}/GraphAn/${_n}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${_f} ${DDC_DICTS_DIR}/GraphAn/${_n}
        DEPENDS ${_f}
        VERBATIM
    )
    list(APPEND _ddc_graphan_outputs ${DDC_DICTS_DIR}/GraphAn/${_n})
endforeach()
foreach(_dict Obor GerObor EngObor)
    set(_src ${CMAKE_CURRENT_SOURCE_DIR}/nlp_base/data/${_dict})
    set(_dst ${DDC_DICTS_DIR}/${_dict})
    set(_scheme ${_src}/ross.txt ${_src}/fields.json ${_src}/domains.json ${_src}/domitems.tsv ${_src}/config.rcf)
    file(MAKE_DIRECTORY ${_dst})
    add_custom_command(
        OUTPUT ${_dst}/units.bin ${_dst}/cortege.bin ${_dst}/comments.bin
        COMMAND ${CMAKE_COMMAND} -E make_directory ${_dst}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${_scheme} ${_dst}
        COMMAND StructDictLoader --action from_txt --input-file ross.txt --output-ross-folder .
        DEPENDS StructDictLoader ${_scheme}
        WORKING_DIRECTORY ${_dst}
        COMMENT "Building the ${_dict} dictionary"
        VERBATIM
    )
    list(APPEND _ddc_graphan_outputs ${_dst}/units.bin)
endforeach()
add_custom_target(ddc_graphan_dicts ALL DEPENDS ${_ddc_graphan_outputs})

add_subdirectory (PCRE)
add_subdirectory (CommonLib)
add_subdirectory (RmlTar)
add_subdirectory (ConcordLib)
add_subdirectory (ConcordDmnLib)

add_subdirectory (ddc_console)
add_subdirectory (ddc_daemon)
add_subdirectory (ddc_dump)
add_subdirectory (ddc_index)
add_subdirectory (ddc_expand)
add_subdirectory (ddc_search)
add_subdirectory (ddc_simple)
add_subdirectory (ddc_split)
add_subdirectory (ddc_stats)
add_subdirectory (ddc_union)
add_subdirectory (ddc_xml)
add_subdirectory (tests)
add_subdirectory (jsoncpp)