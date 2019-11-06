project(ddc_split)

add_executable (ddc_split ddc_split.cpp)

target_link_libraries(ddc_split 
    ConcordLib
)
