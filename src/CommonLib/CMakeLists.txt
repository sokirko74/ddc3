
add_library(CommonLib
CHost.cpp
ddcLocale.cpp
ddcLog.cpp
ddcMMap.cpp
ddcString.cpp
ddcThread.cpp
ddcTime.cpp
ddcVersion.cpp
Network.cpp
utf8xx.cpp
ddcExpc.cpp
ddcFile.cpp
ddcProcess.cpp
)



target_link_libraries(CommonLib
    morphology_common
)
