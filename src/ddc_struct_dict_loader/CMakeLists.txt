project(ddc_struct_dict_loader)

add_executable (ddc_struct_dict_loader ddc_struct_dict_loader.cpp)

target_link_libraries(ddc_struct_dict_loader 
    ConcordLib
)
