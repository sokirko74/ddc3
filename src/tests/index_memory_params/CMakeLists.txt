macro (index_mem_params corpus)
    set (dir ${CMAKE_BINARY_DIR}/tests/index_memory_params)
    add_test(
            NAME index_mem_params_copy_${corpus}
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/index_memory_params  ${dir}
    )
    add_test(
            NAME index_mem_params_${corpus}
            COMMAND ddc_index ${corpus}
            WORKING_DIRECTORY  ${dir}
    )
    add_test(
            NAME index_mem_params_dump_${corpus}
            COMMAND ddc_dump -t -o . -f ${corpus}
            WORKING_DIRECTORY  ${dir}
    )
    add_test(
            NAME index_mem_params_comp_0_${corpus}
            COMMAND ${CMAKE_COMMAND} -E compare_files 0.tabs canon0.txt
            WORKING_DIRECTORY  ${dir}
    )
    add_test(
            NAME index_mem_params_comp_1_${corpus}
            COMMAND ${CMAKE_COMMAND} -E compare_files 1.tabs canon1.txt
            WORKING_DIRECTORY  ${dir}
    )

endmacro()

#index_mem_params (m_small.con)
index_mem_params (m_middle.con)
#index_mem_params (m_default.con)
