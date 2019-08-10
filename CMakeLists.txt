PROJECT(Example)

cmake_minimum_required(VERSION 2.8)

set(SuiteSparse_DIR "C:/suitesparse-metis-for-windows/build/SuiteSparse")
find_package(SuiteSparse CONFIG REQUIRED)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -openmp -Ox")

add_library(example SHARED example.cpp)

# Alternative:
# add_executable(example SHARED example.cpp)
# Run: Open "Command Prompt" and call "C:/SuiteSparsePythonWindows/build/Release/example.exe"

include_directories("C:/suitesparse-metis-for-windows/build/install/include/suitesparse")
target_link_libraries(example ${SuiteSparse_LIBRARIES})