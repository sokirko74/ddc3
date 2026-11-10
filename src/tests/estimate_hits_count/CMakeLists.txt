# EstimateHitsCount: 4 documents of the same size, each one is a search period (UserMaxTokenCountInOnePeriod 2).
# "мяу" is in 5 sentences of a.xml and in 1 sentence of b, c, d (8 hits); "гав" is in 4 sentences of b, c, d (12).
# With "EstimateHitsCount 5" the search stops as soon as 5 hits are found:
#   мяу: 5 hits in 1/4 of the tokens -> 20;  гав: 8 hits in 3/4 -> 11;  Кот: 5 in 1/4 -> 20 (exact 20);
#   a sorted query (#less_by_size) is counted exactly: 8.
set (dir ${CMAKE_BINARY_DIR}/tests/estimate_hits_count)
add_test(
        NAME estimate_hits_count_copy
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/estimate_hits_count  ${dir}
)
foreach (project exact estimate)
    add_test(
            NAME estimate_hits_count_index_${project}
            COMMAND ddc_index ${project}.con
            WORKING_DIRECTORY  ${dir}
    )
endforeach ()
set (n 0)
foreach (test "exact|мяу|8" "estimate|мяу|20" "estimate|гав|11" "estimate|мяу #less_by_size|8" "estimate|Кот|20")
    string(REPLACE "|" ";" test "${test}")
    list(GET test 0 project)
    list(GET test 1 query)
    list(GET test 2 count)
    math(EXPR n "${n}+1")
    set (name ${project}${n})
    add_test(
            NAME estimate_hits_count_query_${name}
            COMMAND ddc_simple --limit 2 ${project}.con ${query}
            WORKING_DIRECTORY  ${dir}
    )
    set_tests_properties(estimate_hits_count_query_${name} PROPERTIES PASS_REGULAR_EXPRESSION "HitsCount = ${count}\n")
endforeach ()
