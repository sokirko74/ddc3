project(ddc_stats)

add_executable (ddc_stats ddc_stats.cpp)

target_link_libraries(ddc_stats 
    ConcordLib
)
