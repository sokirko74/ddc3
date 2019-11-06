macro (ddc_unix_domain_socket_test)
    set (dir ${CMAKE_BINARY_DIR}/tests/unix_domain_sockets)
    add_test(
            NAME copy_uds
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/unix_domain_sockets  ${dir}
    )
    add_test(
            NAME index_uds
            COMMAND ddc_index corpus.con
            WORKING_DIRECTORY  ${dir}
    )
    add_test(
            NAME start_server_uds
            COMMAND ddc_daemon restart -l ddc_local_corpora.cfg  -s ddc_server.cfg -v trace
            WORKING_DIRECTORY  ${dir}
    )
    add_test(
            NAME sleep_uds
            COMMAND ${CMAKE_COMMAND} -E sleep 3
            WORKING_DIRECTORY  ${dir}
    )

    add_test(
            NAME query_leaf_uds
            COMMAND ddc_xml --server ddc_xml_leaf.cfg  -text -f query.txt --output new_result_leaf.txt
            WORKING_DIRECTORY  ${dir}
    )
    add_test(
            NAME query_root_uds
            COMMAND ddc_xml --server ddc_xml_root.cfg  -text -f query.txt --output new_result_root.txt
            WORKING_DIRECTORY  ${dir}
    )
    add_test(
            NAME stop_server_uds
            COMMAND ddc_daemon stop -l ddc_local_corpora.cfg
            WORKING_DIRECTORY  ${dir}
    )
    add_test(
            NAME diff_leaf_uds
            COMMAND ${CMAKE_COMMAND} -E compare_files new_result_leaf.txt canon.leaf.txt
            WORKING_DIRECTORY  ${dir}
    )
    add_test(
            NAME diff_root_uds
            COMMAND ${CMAKE_COMMAND} -E compare_files new_result_root.txt canon.root.txt
            WORKING_DIRECTORY  ${dir}
    )

endmacro(ddc_unix_domain_socket_test)

ddc_unix_domain_socket_test ()
