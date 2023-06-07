
cmake_minimum_required (VERSION 3.8)

project ("ModelDll")

set(SOURCE_LIB Model.cc)

set(LIBRARY_OUTPUT_PATH  "${CMAKE_CURRENT_SOURCE_DIR}/build/")

add_library(ModelDll SHARED ${SOURCE_LIB})

set_target_properties(
    ModelDll 
    PROPERTIES 
        PREFIX ""
        OUTPUT_NAME "ModelDll"
        SUFFIX ".dll"
        CXX_STANDARD 17
)