
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
    ${PROJECT_SOURCE_DIR}/yyQParser.cpp
    ${PROJECT_SOURCE_DIR}/yyQLexer.cpp
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
)
# the generated lexer must pick up our patched FlexLexer.h, not the system one
target_include_directories(ConcordLib PRIVATE ${PROJECT_SOURCE_DIR})


message ("bison_tool = " ${BISON_TOOL})
  add_custom_command(OUTPUT ${PROJECT_SOURCE_DIR}/yyQParser.cpp ${PROJECT_SOURCE_DIR}/yyQParser.h
    DEPENDS yyQParser.y
	COMMAND ${BISON_TOOL} -d -v yyQParser.y
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    VERBATIM
 )

 add_custom_command( OUTPUT ${PROJECT_SOURCE_DIR}/yyQLexer.cpp ${PROJECT_SOURCE_DIR}/yyQLexer.h
     DEPENDS yyQLexer.l yyQParser.h
  	 COMMAND ${FLEX_TOOL} yyQLexer.l
     WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
     VERBATIM
)
