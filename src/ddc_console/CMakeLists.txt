project(ddc_console)

add_executable (ddc_console ddc_console.cpp)

target_link_libraries(ddc_console 
    ConcordLib
)
