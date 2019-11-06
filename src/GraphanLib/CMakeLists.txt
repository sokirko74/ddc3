cmake_minimum_required(VERSION 3.5)

project(GraphanLib)

add_library(GraphanLib
C_desc.cpp
Consent.cpp
Cs_hiera.cpp
GraphanDicts.cpp
GraphmatFile.cpp
HtmlConv.cpp
Nc_desc.cpp
Oborots.cpp
Sentences.cpp
StdAfx.cpp
UnitHolder.cpp
Writegra.cpp
abbrev.cpp
graline.cpp
gra_descr.cpp
)

target_link_libraries(GraphanLib
    StructDictLib
)

