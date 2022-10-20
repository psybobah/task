cmake_minimum_required(VERSION 3.14)
project(task)

# Structured binding declaration requires at least C++17
set(CMAKE_CXX_STANDARD 17)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

enable_testing()

add_executable(
  testing
  test.cpp
)
target_link_libraries(
  testing
  GTest::gtest
)

add_executable(
  task
  task.cpp
)

include(GoogleTest)
gtest_discover_tests(testing)
