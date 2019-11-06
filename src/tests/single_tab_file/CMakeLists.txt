macro (single_tab_file)
    set (dir ${CMAKE_BINARY_DIR}/tests/single_tab_file)
    add_test(
            NAME single_tab_file_copy
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/single_tab_file  ${dir}
    )
    add_test(
            NAME single_tab_file_index
            COMMAND ddc_index m.con
            WORKING_DIRECTORY  ${dir}
    )
    add_test(
            NAME single_tab_file_dump
            COMMAND ddc_dump --tab-single-file -o new_dump.txt -f m.con
            WORKING_DIRECTORY  ${dir}
    )
    add_test(
            NAME single_tab_file_comp
            COMMAND ${CMAKE_COMMAND} -E compare_files new_dump.txt canon.txt
            WORKING_DIRECTORY  ${dir}
    )

endmacro()

single_tab_file ()
