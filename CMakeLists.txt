cmake_minimum_required(VERSION 3.1)
project(FileSystem)

set(FSS_BUILD_ROOT ${CMAKE_BINARY_DIR}/output)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${FSS_BUILD_ROOT}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${FSS_BUILD_ROOT}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${FSS_BUILD_ROOT}/bin)

add_subdirectory(src)

add_executable(FileSystemSimulator main.cpp)
target_link_libraries(FileSystemSimulator fsx)