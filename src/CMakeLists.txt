add_library(fs SHARED
            fs.cpp)

target_include_directories(fs PUBLIC
        ${PROJECT_SOURCE_DIR}/src)

target_include_directories(fs PUBLIC ${REM_BUILD_ROOT}/include)
