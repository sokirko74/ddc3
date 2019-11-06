project(ddc_daemon)

add_executable (ddc_daemon ddc_daemon.cpp)

target_link_libraries(ddc_daemon 
    ConcordLib
    ConcordDmnLib
)
