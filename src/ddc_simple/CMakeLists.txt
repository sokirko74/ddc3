project(ddc_simple)

add_executable (ddc_simple ddc_simple.cpp)

target_link_libraries(ddc_simple 
    ConcordLib
    jsoncpp_lib_static
)
