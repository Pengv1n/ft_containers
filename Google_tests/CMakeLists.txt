# 'Google_test' is the subproject name
project(Google_tests)
set(CMAKE_CXX_STANDARD 98)
# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'Google_Tests_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests
add_executable(TestsVector TestVector.cpp)
include_directories(TestsVector ../vector)
target_link_libraries(TestsVector gtest gtest_main)

add_executable(TestsStack TestStack.cpp)
include_directories(TestsStack ../stack)
target_link_libraries(TestsStack gtest gtest_main)

add_executable(TestSet TestSet.cpp)
include_directories(TestSet ../set)
target_link_libraries(TestSet gtest gtest_main)