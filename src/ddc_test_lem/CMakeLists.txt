cmake_minimum_required(VERSION 3.5)

project(ddc_test_lem)

add_executable (ddc_test_lem ddc_test_lem.cpp)

target_link_libraries(ddc_test_lem
    LemmatizerLib
)
