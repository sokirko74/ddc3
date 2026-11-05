cmake_minimum_required(VERSION 3.5)

project(ConcordDmnLib)

add_library(ConcordDmnLib
	BranchServer.cpp
	Corpora.cpp
	LeafServer.cpp
	Morphan.cpp
	Server.cpp
	ServerOptions.cpp
	ServerStats.cpp
	ServerThread.cpp
)

target_link_libraries(ConcordDmnLib
    ConcordLib
)


