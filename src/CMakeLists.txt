add_library(fss SHARED
        fss.hpp
        block.cpp
        disk.cpp
        directory.cpp
        file.cpp)

target_include_directories(fss PUBLIC
        ${PROJECT_SOURCE_DIR}/src)

target_include_directories(fss PUBLIC ${REM_BUILD_ROOT}/include)

add_subdirectory(fss)