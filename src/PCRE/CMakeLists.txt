cmake_minimum_required(VERSION 3.5)

project(PCRE)

find_path(PCRE2_INCLUDE_DIR pcre2.h)
find_library(PCRE2_LIBRARY pcre2-8)
if(NOT PCRE2_INCLUDE_DIR OR NOT PCRE2_LIBRARY)
    message(FATAL_ERROR "PCRE2 not found (install libpcre2-dev)")
endif()

add_library(PCRE
	pcre_rml.cpp
)

target_include_directories(PCRE PUBLIC ${PCRE2_INCLUDE_DIR})
target_compile_definitions(PCRE PUBLIC PCRE2_CODE_UNIT_WIDTH=8)

target_link_libraries(PCRE
    ${PCRE2_LIBRARY}
    CommonLib
)
