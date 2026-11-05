macro (index_morph_pattern)
    set (dir ${CMAKE_BINARY_DIR}/tests/index_morph_pattern)
    add_test(
            NAME copy_index_morph_pattern
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/index_morph_pattern  ${dir}
    )
    add_test(
            NAME ddc_index_index_morph_pattern
            COMMAND ddc_index m.con
            WORKING_DIRECTORY  ${dir}
    )
    add_test(
            NAME ddc_query_index_morph_pattern
            COMMAND ddc_simple -o new_result.txt m.con [NOUN]
            WORKING_DIRECTORY  ${dir}
    )
    add_test(
            NAME ddc_diff_index_morph_pattern
            COMMAND ${CMAKE_COMMAND} -E compare_files new_result.txt canon.txt
            WORKING_DIRECTORY  ${dir}
    )

endmacro()

index_morph_pattern ()
