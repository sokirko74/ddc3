cmake_minimum_required(VERSION 3.5)

project(LemmatizerLib)

add_library(LemmatizerLib
CreatePredictionBase.cpp
Lemmatizers.cpp
MorphAutomBuilder.cpp
MorphAutomat.cpp
MorphDict.cpp
MorphDictBuilder.cpp
Paradigm.cpp
Predict.cpp
Statistic.cpp
StdMorph.cpp
)

target_link_libraries(LemmatizerLib
    AgramtabLib
    PCRE
    GraphanLib
    MorphWizardLib
)

