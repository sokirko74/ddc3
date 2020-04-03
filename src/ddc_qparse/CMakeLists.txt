project(ddc_qparse)

add_executable (ddc_qparse ddc_qparse.cpp)

target_link_libraries(ddc_qparse 
    ConcordLib
)
