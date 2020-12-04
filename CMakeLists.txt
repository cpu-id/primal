cmake_minimum_required(VERSION 3.16.5)

#From scratch to sky.
project(primal_loader_v2)
set(CMAKE_CXX_STANDARD 14)

#Place here new source files.
set(SOURCE_FILES

    src/segment/internal/SegmentNativeData.cpp
    src/runtime/reconstructor/Reconstructor.hpp
    src/runtime/reconstructor/reconstructors/IATReconstructor.cpp
    src/runtime/reconstructor/reconstructors/RelocReconstructor.cpp
    src/runtime/RuntimeEngine.cpp
    src/util/stuff/RuntimeDefinitions.cpp
    src/util/CommonUtil.cpp
    src/util/PanicUtil.cpp

)

#Build.
add_library(primal_loader_v2 SHARED ${SOURCE_FILES})