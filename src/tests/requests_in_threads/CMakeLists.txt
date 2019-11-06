macro (requests_in_threads)
    set (dir ${CMAKE_BINARY_DIR}/tests/requests_in_threads)
    add_test(
            NAME requests_in_threads_copy
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/requests_in_threads  ${dir}
    )
    add_test(
            NAME requests_in_threads_index
            COMMAND ddc_index m.con
            WORKING_DIRECTORY  ${dir}
    )
    add_test(
            NAME requests_in_threads_start_server
            COMMAND ddc_daemon restart -l ddc_local_corpora.cfg  -s ddc_server.cfg -v trace
            WORKING_DIRECTORY  ${dir}
    )
    add_test(
            NAME requests_in_threads_sleep
            COMMAND ${CMAKE_COMMAND} -E sleep 3
            WORKING_DIRECTORY  ${dir}
    )

    add_test(
            NAME requests_in_threads_query_single_threaded
            COMMAND ddc_xml --server ddc_xml_root.cfg  -text -f query.txt --output new_result_single_threaded.txt
            WORKING_DIRECTORY  ${dir}
    )
    add_test(
            NAME requests_in_threads_comp_single
            COMMAND ${CMAKE_COMMAND} -E compare_files new_result_single_threaded.txt canon.txt
            WORKING_DIRECTORY  ${dir}
    )
    add_test(
            NAME requests_in_threads_query_multi_threaded
            COMMAND ddc_xml --server ddc_xml_root.cfg  -threads 2 -text -f query.txt --output new_result_multi_threaded.txt
            WORKING_DIRECTORY  ${dir}
    )
    add_test(
            NAME requests_in_threads_comp_multi
            COMMAND ${CMAKE_COMMAND} -E compare_files new_result_multi_threaded.txt canon.txt
            WORKING_DIRECTORY  ${dir}
    )

endmacro()

requests_in_threads ()
