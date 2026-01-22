# Google Test CMakeLists.txt
project(ComponentProtectionTests)

# Test executable name
set(TEST_EXECUTABLE ComponentProtectionTest)

# Test source files
set(TEST_SOURCES
    monitor_test.cc
    component_protection_test.cc
)

# Create test executable
add_executable(${TEST_EXECUTABLE} ${TEST_SOURCES})

# Link against ComponentProtection library and Google Test
target_link_libraries(${TEST_EXECUTABLE} PRIVATE
    ComponentProtection
    GTest::gtest
    GTest::gtest_main
)

# Include directories
target_include_directories(${TEST_EXECUTABLE} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../inc
)

# Register tests with CTest
gtest_discover_tests(${TEST_EXECUTABLE})
