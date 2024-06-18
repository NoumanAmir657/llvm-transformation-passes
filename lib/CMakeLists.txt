add_library(Passes MODULE
    AddConstAnalysis.cpp
    AddConstPass.cpp
    AddMetadataAnalysis.cpp
    AddMetadataPass.cpp
    AddToSubAnalysis.cpp
    AddToSubPass.cpp
    MulToShiftAnalysis.cpp
    MulToShiftPass.cpp
    AddCallAnalysis.cpp
    AddCallPass.cpp
    AddConstPlugin.cpp)

target_include_directories(Passes PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/../include")