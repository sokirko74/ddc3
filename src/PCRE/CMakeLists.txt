cmake_minimum_required(VERSION 3.5)

project(PCRE)

find_library(PCRE_LIBRARY pcre)
find_library(PCRECPP_LIBRARY pcrecpp)

add_library(PCRE
	pcre_rml.cpp
)

target_compile_definitions(PCRE PUBLIC HAVE_CONFIG_H=1)

target_link_libraries(PCRE
    ${PCRE_LIBRARY}
    ${PCRECPP_LIBRARY}
)

