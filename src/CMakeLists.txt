add_library(fsx SHARED
        fsx.hpp
        block.cpp
        disk.cpp
        directory.cpp
        file.cpp)

target_include_directories(fsx PUBLIC ${PROJECT_SOURCE_DIR}/src)