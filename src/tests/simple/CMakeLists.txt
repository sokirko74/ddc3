macro (ddc_index_simple_test lang)
    set (dir ${CMAKE_BINARY_DIR}/tests/simple/${lang})
    add_test(
            NAME ${lang}_copy_index_simple
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/simple/${lang}  ${dir}
    )
    add_test(
            NAME ${lang}_ddc_index_simple
            COMMAND ddc_index corpus.con
            WORKING_DIRECTORY  ${dir}
    )
    add_test(
            NAME ${lang}_ddc_query_simple_test
            COMMAND ddc_simple corpus.con query.txt -ResultFormat html new_result.html
            WORKING_DIRECTORY  ${dir}
    )
    add_test(
            NAME ${lang}_ddc_diff_simple_test
            COMMAND ${CMAKE_COMMAND} -E compare_files new_result.html canon.html
            WORKING_DIRECTORY  ${dir}
    )

endmacro(ddc_index_simple_test)

ddc_index_simple_test (Russian)
ddc_index_simple_test (English)
ddc_index_simple_test (German)
