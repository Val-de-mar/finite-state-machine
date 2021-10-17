cmake_minimum_required(VERSION 3.16)
project(RegexTraits)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "--coverage")
set(CMAKE_C_FLAGS "--coverage")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

add_library(RegexTraits SHARED ${PROJECT_SOURCE_DIR}/src/RegexTraits.cpp ${PROJECT_SOURCE_DIR}/src/RegexLetter.cpp  ${PROJECT_SOURCE_DIR}/src/RegexBinaryOperation.cpp  ${PROJECT_SOURCE_DIR}/src/RegexUnaryOperation.cpp)
target_include_directories(RegexTraits PUBLIC "${PROJECT_SOURCE_DIR}/include")
set_target_properties(RegexTraits PROPERTIES PUBLIC_HEADER RegexTraits.h)
