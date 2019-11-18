macro (free_index)
    set (dir ${CMAKE_BINARY_DIR}/tests/free_index)
    add_test(
            NAME free_index_copy
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/free_index  ${dir}
    )
    add_test(
            NAME free_index
            COMMAND ddc_index m.con
            WORKING_DIRECTORY  ${dir}
    )
    add_test(
            NAME free_index_query
            COMMAND ddc_simple -pretty m.con $l=MUTTER new_result.json
            WORKING_DIRECTORY  ${dir}
    )
    add_test(
            NAME free_index_comp
            COMMAND ${CMAKE_COMMAND} -E compare_files new_result.json canon.json
            WORKING_DIRECTORY  ${dir}
    )

    add_test(
            NAME free_index_mapped
            COMMAND ddc_index m_mapped.con # we can just copy them from m._*
            WORKING_DIRECTORY  ${dir}
    )
    add_test(
            NAME free_index_query_mapped
            COMMAND ddc_simple -pretty m_mapped.con $l=MUTTER new_result_mapped.json
            WORKING_DIRECTORY  ${dir}
    )
    add_test(
            NAME free_index_comp_mapped
            COMMAND ${CMAKE_COMMAND} -E compare_files new_result_mapped.json canon.json
            WORKING_DIRECTORY  ${dir}
    )

endmacro()

free_index ()
