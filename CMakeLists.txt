cmake_minimum_required(VERSION 3.10)
project(ComponentProtectionProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable testing
enable_testing()

# Try to find Google Test - optional
find_package(GTest QUIET)
if(NOT GTest_FOUND)
  message(STATUS "Google Test not found - tests will be skipped")
  set(BUILD_TESTS OFF)
else()
  set(BUILD_TESTS ON)
endif()

# Add CXX subdirectory
add_subdirectory(CXX)
