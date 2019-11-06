macro (tar_and_stats)
    set (dir ${CMAKE_BINARY_DIR}/tests/tar_and_stats)
    add_test(
            NAME tar_and_stats_copy
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/tar_and_stats  ${dir}
    )
    add_test(
            NAME tar_and_stats
            COMMAND ddc_index m.con
            WORKING_DIRECTORY  ${dir}
    )
    add_test(
            NAME tar_and_stats_stats
            COMMAND ddc_stats m.con German Token dump-freq --output new_result.txt
            WORKING_DIRECTORY  ${dir}
    )
    add_test(
            NAME tar_and_stats_comp
            COMMAND ${CMAKE_COMMAND} -E compare_files new_result.txt canon.txt
            WORKING_DIRECTORY  ${dir}
    )

endmacro()

tar_and_stats ()
