cmake_minimum_required(VERSION 3.14)
project(ComponentProtection LANGUAGES CXX)

# Google Style: Standardize on C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Define the library
# Including headers in add_library helps IDEs (like VS Code) show them in the tree
add_library(ComponentProtection 
    src/monitor.cpp
    src/component_protection.cpp
    inc/monitor.h
    inc/cp_parameter.h
    inc/component_protection.h
    inc/clock.h
)

# 2. Proper Include Management
# PUBLIC means: "I need these paths to build, and you need them to use me."
target_include_directories(ComponentProtection PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
    $<INSTALL_INTERFACE:include>
)

# 3. Compiler Alarms (Google Style compliance)
if(MSVC)
    target_compile_options(ComponentProtection PRIVATE /W4 /WX)
else()
    target_compile_options(ComponentProtection PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

# 4. Logic to fetch GTest and enable tests
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
# For Windows compatibility: prevents GTest from overriding your compiler settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()
add_subdirectory(test)