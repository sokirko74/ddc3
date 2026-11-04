cmake_minimum_required(VERSION 3.5)

add_library(CommonLib
CHost.cpp
ddcLocale.cpp
ddcLog.cpp
ddcMMap.cpp
ddcString.cpp
ddcThread.cpp
ddcTime.cpp
ddcVersion.cpp
string_socket.cpp
utf8xx.cpp
ddcExpc.cpp
ddcFile.cpp
ddcProcess.cpp
)



target_link_libraries(CommonLib
    morphology_common
)
