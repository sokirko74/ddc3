macro (splitjoin)
    set (dir ${CMAKE_BINARY_DIR}/tests/splitjoin)
    add_test(
            NAME splitjoin_copy
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/splitjoin  ${dir}
    )
    add_test(
            NAME splitjoin_index
            COMMAND ddc_index m.con
            WORKING_DIRECTORY  ${dir}
    )
    add_test(
            NAME splitjoin_dump
            COMMAND ddc_dump --tabs-stream -o new_dump.txt -f m.con
            WORKING_DIRECTORY  ${dir}
    )
        #copy opts to maintain break orders
    add_test(
            NAME splitjoin_split
            COMMAND ddc_split --options m.opt -n 2 m.con
            WORKING_DIRECTORY  ${dir}
    )
        # take opts from the first split, the second is the same
    add_test(
            NAME splitjoin_join
            COMMAND ddc_union --options split00/split00.opt split00/split00.con split01/split01.con -o m_united.con
            WORKING_DIRECTORY  ${dir}
    )
    add_test(
            NAME splitjoin_dump_united
            COMMAND ddc_dump --tabs-stream -o new_dump_united.txt -f m_united.con
            WORKING_DIRECTORY  ${dir}
    )
    add_test(
            NAME splitjoin_comp
            COMMAND ${CMAKE_COMMAND} -E compare_files new_dump.txt new_dump_united.txt
            WORKING_DIRECTORY  ${dir}
    )

endmacro()

splitjoin ()
