cmake_minimum_required(VERSION 3.16)
project(FormalLanguageTasks)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "--coverage")
set(CMAKE_C_FLAGS "--coverage")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(COVERAGE_DIR ${CMAKE_SOURCE_DIR}/coverage)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_subdirectory(Machine)
add_subdirectory(RegexTraits)


add_library(suffixMethods SHARED src/suffix.cpp)
target_link_libraries(suffixMethods machine RegexTraits)
target_include_directories(suffixMethods PUBLIC "${CMAKE_SOURCE_DIR}/include" "${RegexTraits_SOURCE_DIR}/include" "${machine_SOURCE_DIR}/include")


add_executable(program main.cpp)
target_include_directories(program PUBLIC "${CMAKE_SOURCE_DIR}/include" "${machine_SOURCE_DIR}/include")
target_link_libraries(program machine)


add_executable(machineTest machineTest.cpp)
target_link_libraries(machineTest gtest_main)
target_link_libraries(machineTest machine)
target_include_directories(machineTest PUBLIC "${CMAKE_SOURCE_DIR}/include" "${machine_SOURCE_DIR}/include")
add_test(NAME machine_test COMMAND machineTest)

add_executable(RegexTraitsTest RegexTraitsTest.cpp)
target_link_libraries(RegexTraitsTest gtest_main)
target_link_libraries(RegexTraitsTest machine RegexTraits)
target_include_directories(RegexTraitsTest PUBLIC "${CMAKE_SOURCE_DIR}/include" "${RegexTraits_SOURCE_DIR}/include")
add_test(NAME regex_traits_test COMMAND RegexTraitsTest)


add_executable(longestSuffix LongestPart.cpp)
target_include_directories(longestSuffix PUBLIC "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(longestSuffix machine suffixMethods RegexTraits)

add_executable(LongestPartTest LongestPartTest.cpp)
target_link_libraries(LongestPartTest gtest_main)
target_link_libraries(LongestPartTest suffixMethods)
target_include_directories(LongestPartTest PUBLIC "${CMAKE_SOURCE_DIR}/include")
add_test(NAME longest_part_test COMMAND LongestPartTest)

add_custom_target(coverage_dir
        COMMAND mkdir -p ${CMAKE_SOURCE_DIR}/coverage
        )

add_custom_target(testMachineRun
        DEPENDS machineTest
        WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
        COMMAND ./machineTest
        )

add_custom_target(coverage_machine_gen
        DEPENDS testMachineRun coverage_dir
        WORKING_DIRECTORY "Machine/CMakeFiles/machine.dir/src"
        COMMAND gcov -c -b machine.cpp.
        COMMAND cp ./machine*.gcov ${COVERAGE_DIR}/
        )

add_custom_target(coverage_det_machine_gen
        DEPENDS testMachineRun coverage_dir
        WORKING_DIRECTORY "Machine/CMakeFiles/machine.dir/src"
        COMMAND gcov -c -b DetMachine.cpp.
        COMMAND cp ./DetMachine*.gcov ${COVERAGE_DIR}/
        )

add_custom_target(coverage_polish_gen
        DEPENDS testMachineRun coverage_dir
        WORKING_DIRECTORY "CMakeFiles/machineTest.dir"
        COMMAND gcov -c -b machineTest.cpp.
        COMMAND cp ./poland*.gcov ${COVERAGE_DIR}/
        )


add_custom_target(testRegexTraitsRun
        DEPENDS RegexTraitsTest
        WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
        COMMAND ./RegexTraitsTest
        )

add_custom_target(coverage_traits_gen
        DEPENDS testRegexTraitsRun coverage_dir
        WORKING_DIRECTORY "RegexTraits/CMakeFiles/RegexTraits.dir/src"
        COMMAND gcov -c -b RegexUnaryOperation.cpp. RegexBinaryOperation.cpp. RegexLetter.cpp. RegexTraits.cpp.
        COMMAND cp ./Regex*.gcov ${COVERAGE_DIR}/
        )

add_custom_target(testLongestPartRun
        DEPENDS LongestPartTest
        WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
        COMMAND ./LongestPartTest
        )

add_custom_target(coverage_longest_part_gen
        DEPENDS testLongestPartRun coverage_dir
        WORKING_DIRECTORY "CMakeFiles/suffixMethods.dir/src"
        COMMAND gcov -c -b suffix.cpp.
        COMMAND cp ./suffix.cpp.gcov ${COVERAGE_DIR}/
        )


add_custom_target(coverage ALL
        DEPENDS coverage_polish_gen coverage_machine_gen coverage_det_machine_gen coverage_traits_gen coverage_longest_part_gen
        )
