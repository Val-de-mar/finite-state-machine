cmake_minimum_required(VERSION 3.16)
project(machine)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "--coverage")
set(CMAKE_C_FLAGS "--coverage")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


add_library(machine SHARED ${PROJECT_SOURCE_DIR}/src/machine.cpp ${PROJECT_SOURCE_DIR}/src/DetMachine.cpp )
target_include_directories(machine PUBLIC "${PROJECT_SOURCE_DIR}/include")


