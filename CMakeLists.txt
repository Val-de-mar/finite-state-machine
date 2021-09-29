cmake_minimum_required(VERSION 3.16)
project(machine)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "--coverage")
set(CMAKE_C_FLAGS "--coverage")


include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(machine STATIC ${CMAKE_SOURCE_DIR}/src/machine.cpp)
target_include_directories(machine PUBLIC "${CMAKE_SOURCE_DIR}/include")

add_executable(program main.cpp)
target_include_directories(program PUBLIC "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(program machine)

add_executable(machine_test tests.cpp)
target_link_libraries(machine_test gtest_main)
target_link_libraries(machine_test machine)
target_include_directories(machine_test PUBLIC "${CMAKE_SOURCE_DIR}/include")
add_test(NAME example_test COMMAND machine_test)


add_custom_target(testrun 
    DEPENDS machine_test
    WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
    COMMAND ./machine_test
    COMMAND mkdir coverage && true
    )

add_custom_target(coverage_machine_gen
    DEPENDS testrun
    WORKING_DIRECTORY "CMakeFiles/machine.dir/src"
    COMMAND gcov -c -b machine.cpp.
    COMMAND cp ./machine*.gcov ../../../coverage
    )

add_custom_target(coverage_polish_gen
    DEPENDS testrun
    WORKING_DIRECTORY "CMakeFiles/machine_test.dir"
    COMMAND gcov -c -b tests.cpp.
    COMMAND cp ./poland*.gcov ../../coverage
    )

add_custom_target(converage ALL
    DEPENDS coverage_polish_gen coverage_machine_gen
    )
