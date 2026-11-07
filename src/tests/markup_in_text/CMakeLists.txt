# a text with "<textarea>", "</p>" and a control character (a book about HTML) must not be taken for
# the markup that DDC inserts into the text for the graphematics; a broken document (b.xml, no body)
# is skipped (ResumeOnIndexErrors) and the next one is indexed
set (dir ${CMAKE_BINARY_DIR}/tests/markup_in_text)
add_test(
        NAME markup_in_text_copy
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/markup_in_text  ${dir}
)
add_test(
        NAME markup_in_text_index
        COMMAND ddc_index m.con
        WORKING_DIRECTORY  ${dir}
)
foreach (query textarea посередине Последний)
    add_test(
            NAME markup_in_text_query_${query}
            COMMAND ddc_simple m.con ${query}
            WORKING_DIRECTORY  ${dir}
    )
    set_tests_properties(markup_in_text_query_${query} PROPERTIES PASS_REGULAR_EXPRESSION "HitsCount = 1\n")
endforeach ()
add_test(
        NAME markup_in_text_skipped
        COMMAND ${CMAKE_COMMAND} -E cat m._error_log
        WORKING_DIRECTORY  ${dir}
)
set_tests_properties(markup_in_text_skipped PROPERTIES PASS_REGULAR_EXPRESSION "failed for file ./b.xml")
