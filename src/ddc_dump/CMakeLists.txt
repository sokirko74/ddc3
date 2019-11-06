project(ddc_dump)

add_executable (ddc_dump ddc_dump.cpp)

target_link_libraries(ddc_dump 
    ConcordLib
)
