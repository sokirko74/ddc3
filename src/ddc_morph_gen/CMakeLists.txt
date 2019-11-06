cmake_minimum_required(VERSION 3.5)

project(ddc_morph_gen)

add_executable (ddc_morph_gen ddc_morph_gen.cpp)

target_link_libraries(ddc_morph_gen 
    LemmatizerLib
)
