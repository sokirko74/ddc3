cmake_minimum_required(VERSION 3.24)

project(ddc VERSION 3.0 LANGUAGES C CXX)
if("${PROJECT_VERSION_PATCH}" STREQUAL "")
    set(DDC_VERSION_MICRO 0)
else()
    set(DDC_VERSION_MICRO ${PROJECT_VERSION_PATCH})
endif()

set (CMAKE_CXX_STANDARD 17)

if(CMAKE_BUILD_TYPE MATCHES "Debug")
    message ("compile debug")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
    message ("enable_testing")
    enable_testing()
else()
    message ("compile release")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_RELEASE} -O2")
endif()

function (add_test)
    _add_test (${ARGV})
    if ("${ARGV0}" STREQUAL "NAME")
        set_property (DIRECTORY APPEND PROPERTY DDC_TESTS_IN_ORDER ${ARGV1})
    else ()
        set_property (DIRECTORY APPEND PROPERTY DDC_TESTS_IN_ORDER ${ARGV0})
    endif ()
endfunction ()

add_subdirectory (src)

# ctest -j: the tests of one directory are steps of one scenario (copy -> index -> query -> compare, start a daemon ->
# query it -> stop it), so each one depends on the previous one of its directory (in the order of add_test, remembered
# here, since the TESTS property of a directory is not ordered); the directories run in parallel.
# The tests find config/rml.ini and the dictionaries of this source tree via $DDC3.
function (serialize_tests_of_directories dir)
    get_property (tests DIRECTORY ${dir} PROPERTY DDC_TESTS_IN_ORDER)
    set (prev "")
    foreach (t IN LISTS tests)
        set_property (TEST ${t} DIRECTORY ${dir} APPEND PROPERTY ENVIRONMENT "DDC3=${CMAKE_SOURCE_DIR}")
        if (prev)
            set_property (TEST ${t} DIRECTORY ${dir} APPEND PROPERTY DEPENDS ${prev})
        endif ()
        set (prev ${t})
    endforeach ()
    get_property (subdirs DIRECTORY ${dir} PROPERTY SUBDIRECTORIES)
    foreach (d IN LISTS subdirs)
        serialize_tests_of_directories (${d})
    endforeach ()
endfunction ()
serialize_tests_of_directories (${CMAKE_SOURCE_DIR})
