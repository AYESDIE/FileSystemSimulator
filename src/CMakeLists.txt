add_library(fss SHARED
        fss.hpp
        fss/fs.cpp)

target_include_directories(fss PUBLIC
        ${PROJECT_SOURCE_DIR}/src)

target_include_directories(fss PUBLIC ${REM_BUILD_ROOT}/include)

add_subdirectory(fss)