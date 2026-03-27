# ComponentProtection/test/CMakeLists.txt
project(ComponentProtectionTests LANGUAGES CXX)

# 1. Define the test executable
# It's usually better to have one runner for all your unit tests
add_executable(cp_unit_tests
    src/monitor_test.cpp
    src/component_protection_test.cpp
    src/clock_test.cpp
)

# 2. Link against the library and GTest
# Linking to 'ComponentProtection' automatically adds its 'inc/' folder to our path
target_link_libraries(cp_unit_tests PRIVATE
    ComponentProtection
    GTest::gtest_main
)

# 3. Local Include Directories
# This is ONLY for mock_monitor.h
target_include_directories(cp_unit_tests PRIVATE inc)

# 4. Discover and register tests
include(GoogleTest)
gtest_discover_tests(cp_unit_tests)