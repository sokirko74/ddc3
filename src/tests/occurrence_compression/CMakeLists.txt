# the compressions of the occurrences: the codecs, and a corpus indexed as normal, archive (VByte) and svbyte
# (Stream VByte) must give the same results; "Мама" (4500 occurrences) is divided into search periods,
# "кот" (645), "пёс" (45) and "лиса" (1) are short lists
add_executable(test_occurrence_codecs test_codecs.cpp)
target_link_libraries(test_occurrence_codecs ConcordLib)
add_test(NAME occurrence_codecs COMMAND test_occurrence_codecs)

set (dir ${CMAKE_BINARY_DIR}/tests/occurrence_compression)
add_test(
        NAME occurrence_compression_copy
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/occurrence_compression  ${dir}
)
foreach (project normal archive svbyte)
    add_test(
            NAME occurrence_compression_index_${project}
            COMMAND ddc_index ${project}.con
            WORKING_DIRECTORY  ${dir}
    )
    set (n 0)
    foreach (test "Мама|4500" "кот|645" "пёс|45" "лиса|1" "\"мыла раму\"|4500" "кот && пёс|9")
        string(REPLACE "|" ";" test "${test}")
        list(GET test 0 query)
        list(GET test 1 count)
        math(EXPR n "${n}+1")
        add_test(
                NAME occurrence_compression_query_${project}${n}
                COMMAND ddc_simple ${project}.con ${query}
                WORKING_DIRECTORY  ${dir}
        )
        set_tests_properties(occurrence_compression_query_${project}${n} PROPERTIES PASS_REGULAR_EXPRESSION "HitsCount = ${count}\n")
    endforeach ()
endforeach ()
