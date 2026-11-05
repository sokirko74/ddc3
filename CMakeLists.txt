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

add_subdirectory (src)
