macro (input_tab_format)
    set (dir ${CMAKE_BINARY_DIR}/tests/input_tab_format)
    add_test(
            NAME input_tab_format_copy
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/input_tab_format  ${dir}
    )
    add_test(
            NAME input_tab_format_index
            COMMAND ddc_index m.con
            WORKING_DIRECTORY  ${dir}
    )
    add_test(
            NAME input_tab_format_dump
            COMMAND ddc_dump -t -o . -f m.con
            WORKING_DIRECTORY  ${dir}
    )
    add_test(
            NAME input_tab_format_comp
            COMMAND ${CMAKE_COMMAND} -E compare_files 0.tabs canon.txt
            WORKING_DIRECTORY  ${dir}
    )

endmacro()

input_tab_format ()
