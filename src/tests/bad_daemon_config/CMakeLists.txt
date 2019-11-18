macro (bad_daemon_config)
    set (dir ${CMAKE_BINARY_DIR}/tests/bad_daemon_config)
    add_test(
            NAME bad_daemon_config_copy
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/bad_daemon_config  ${dir}
    )
    add_test(
            NAME bad_daemon_config_index
            COMMAND ddc_index corpus.con
            WORKING_DIRECTORY  ${dir}
    )
    add_test(
            NAME bad_daemon_config_start_server
            COMMAND ddc_daemon restart -l ddc_local_corpora.cfg  -s ddc_server.cfg -v trace
            WORKING_DIRECTORY  ${dir}
    )
    add_test(
            NAME bad_daemon_config_start_server_sleep1
            COMMAND ${CMAKE_COMMAND} -E sleep 4
            WORKING_DIRECTORY  ${dir}
    )

    add_test(
            NAME bad_daemon_config_status_server
            COMMAND ddc_daemon status -l ddc_local_corpora.cfg  -s ddc_server.cfg -v trace
            WORKING_DIRECTORY  ${dir}
    )
    set_tests_properties(bad_daemon_config_status_server PROPERTIES WILL_FAIL true)

endmacro(bad_daemon_config)

bad_daemon_config ()
