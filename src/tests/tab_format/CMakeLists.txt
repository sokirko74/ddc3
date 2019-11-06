macro (tab_format)
    set (dir ${CMAKE_BINARY_DIR}/tests/tab_format)
    add_test(
            NAME tab_format_copy
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/tab_format  ${dir}
    )
    add_test(
            NAME tab_format_index
            COMMAND ddc_index m.con
            WORKING_DIRECTORY  ${dir}
    )
    add_test(
            NAME tab_format_dump
            COMMAND ddc_dump -t -o . -f m.con
            WORKING_DIRECTORY  ${dir}
    )
    add_test(
            NAME tab_format_comp0
            COMMAND ${CMAKE_COMMAND} -E compare_files 0.tabs canon.0.txt
            WORKING_DIRECTORY  ${dir}
    )
    add_test(
            NAME tab_format_comp1
            COMMAND ${CMAKE_COMMAND} -E compare_files 1.tabs canon.1.txt
            WORKING_DIRECTORY  ${dir}
    )

endmacro()

tab_format ()
