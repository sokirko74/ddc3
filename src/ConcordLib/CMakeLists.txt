cmake_minimum_required(VERSION 3.5)

project(ConcordLib)

find_library(CURL_LIBRARY curl)

add_library(ConcordLib
    NavHint.cpp
    CCurl.cpp
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
    tinyxml
    AgramtabLib
    PCRE
    GraphanLib
    MorphWizardLib
    LemmatizerLib
    ${CURL_LIBRARY}
    RmlTar
)


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
