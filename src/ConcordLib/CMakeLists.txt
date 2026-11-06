
project(ConcordLib)

add_library(ConcordLib
    NavHint.cpp
    UrlFetch.cpp
    TermExpander.cpp
    BiblExpander.cpp
    Query.cpp
    QCount.cpp
    QueryOptions.cpp
    QueryFilter.cpp
    QueryNode.cpp
    QueryCompiler.cpp
    QueryResult.cpp
    ConcSessionContext.cpp
    ConcSession.cpp
    ConcordAlgorithm.cpp
    Bibliography.cpp
    ConcXml.cpp
    ConcordUnion.cpp
    ConcordSplit.cpp
    HitBorder.cpp
    ConcordBibl.cpp
    IndexMorphXml.cpp
    IndexSet.cpp
    StringIndexator.cpp
    ConcIndexator.cpp
    ConcordOptions.cpp
    IndexSetForLoadingStage.cpp
    IndexSetForQueryingStage.cpp
    ConvertFromLoadIndexToWorking.cpp
    LoadingBinaries.cpp
    DwdsThesaurus.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/yyQParser.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/yyQLexer.cpp
    InitDicts.cpp
    CreateMorphIndex.cpp
    ConcIndexatorInvoker.cpp
    Concordance.cpp TabFormatIndexator.cpp TabFormatIndexator.h DocumentIterator.cpp DocumentIterator.h
        Bibliography.cpp Bibliography.h
        FreeBiblIndex.cpp FreeBiblIndex.h
        BiblIndex.cpp BiblIndex.h)

target_link_libraries(ConcordLib
    pugixml::pugixml
    PCRE
    GraphanLib
    lemmatizer_base_lib
    RmlTar
    ZLIB::ZLIB
)
# the generated code (yyQParser.cpp/.h, yyQLexer.cpp/.h, yyQParser.output) is in the build directory
# (it is not kept in git); yyQParser.h is included by QueryCompiler.h, so the directory is PUBLIC
target_include_directories(ConcordLib PRIVATE ${PROJECT_SOURCE_DIR} PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

# bison and flex run in the build directory: the output names in yyQParser.y (%output, %header)
# and yyQLexer.l (outfile, header-file) are relative to it
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/yyQParser.cpp ${CMAKE_CURRENT_BINARY_DIR}/yyQParser.h
    DEPENDS ${PROJECT_SOURCE_DIR}/yyQParser.y
    COMMAND ${BISON_TOOL} -v ${PROJECT_SOURCE_DIR}/yyQParser.y
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    VERBATIM
)
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/yyQLexer.cpp ${CMAKE_CURRENT_BINARY_DIR}/yyQLexer.h
    DEPENDS ${PROJECT_SOURCE_DIR}/yyQLexer.l ${CMAKE_CURRENT_BINARY_DIR}/yyQParser.h
    COMMAND ${FLEX_TOOL} ${PROJECT_SOURCE_DIR}/yyQLexer.l
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    VERBATIM
)
