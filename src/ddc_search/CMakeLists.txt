project(ddc_search)

add_executable (ddc_search
        ddc_search.cpp
        cgic.cpp
        )

target_link_libraries(ddc_search
    ConcordLib
)
