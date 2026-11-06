# gzip-compressed corpus files: a.xml.gz is indexed exactly as a.xml (same frequencies);
# compressed tar files are rejected
set (dir ${CMAKE_BINARY_DIR}/tests/gzip)
add_test(
        NAME gzip_copy
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/gzip  ${dir}
)
foreach (kind plain gz)
    add_test(
            NAME gzip_${kind}_index
            COMMAND ddc_index m.con
            WORKING_DIRECTORY  ${dir}/${kind}
    )
    add_test(
            NAME gzip_${kind}_stats
            COMMAND ddc_stats m.con German Token dump-freq --output ../${kind}_freq.txt
            WORKING_DIRECTORY  ${dir}/${kind}
    )
endforeach ()
add_test(
        NAME gzip_comp
        COMMAND ${CMAKE_COMMAND} -E compare_files plain_freq.txt gz_freq.txt
        WORKING_DIRECTORY  ${dir}
)
add_test(
        NAME gzip_reject_tar_gz
        COMMAND ddc_index m.con
        WORKING_DIRECTORY  ${dir}/targz
)
set_tests_properties(gzip_reject_tar_gz PROPERTIES WILL_FAIL TRUE)
