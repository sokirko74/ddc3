macro (good_daemon_config)
    set (dir ${CMAKE_BINARY_DIR}/tests/good_daemon_config)
    add_test(
            NAME good_daemon_config_copy
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/good_daemon_config  ${dir}
    )
    add_test(
            NAME good_daemon_config_index
            COMMAND ddc_index corpus.con
            WORKING_DIRECTORY  ${dir}
    )
    add_test(
            NAME good_daemon_config_start_server
            COMMAND ddc_daemon restart -l ddc_local_corpora.cfg  -s ddc_server.cfg -v trace --options options.rc
            WORKING_DIRECTORY  ${dir}
    )
    add_test(
            NAME good_daemon_config_start_server_sleep1
            COMMAND ${CMAKE_COMMAND} -E sleep 4
            WORKING_DIRECTORY  ${dir}
    )

    add_test(
            NAME good_daemon_config_status_server1
            COMMAND ddc_daemon status -l ddc_local_corpora.cfg  -s ddc_server.cfg -v trace
            WORKING_DIRECTORY  ${dir}
    )
    add_test(
            NAME good_daemon_config_start_server_sleep2
            COMMAND ${CMAKE_COMMAND} -E sleep 4
            WORKING_DIRECTORY  ${dir}
    )
    add_test(
            NAME good_daemon_config_stop_server
            COMMAND ddc_daemon stop -l ddc_local_corpora.cfg  -s ddc_server.cfg -v trace
            WORKING_DIRECTORY  ${dir}
    )
    add_test(
            NAME good_daemon_config_status_server2
            COMMAND ddc_daemon status -l ddc_local_corpora.cfg  -s ddc_server.cfg -v trace
            WORKING_DIRECTORY  ${dir}
    )
    set_tests_properties(good_daemon_config_status_server2 PROPERTIES WILL_FAIL true)

endmacro(good_daemon_config)

good_daemon_config ()
