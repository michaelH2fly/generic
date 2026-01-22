# ComponentProtection library CMakeLists.txt
project(ComponentProtection)

# Define library name
set(TARGET_NAME ComponentProtection)

# Source files
set(SOURCES
    src/monitor.cc
    src/component_protection.cc
)

# Header files
set(HEADERS
    inc/monitor.h
    inc/cp_parameter.h
    inc/component_protection.h
)

# Create library
add_library(${TARGET_NAME} ${SOURCES} ${HEADERS})

# Specify include directories
target_include_directories(${TARGET_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
    $<INSTALL_INTERFACE:include>
)

# Set compiler options for Google C++ style compliance
if(MSVC)
    target_compile_options(${TARGET_NAME} PRIVATE /W4 /WX)
else()
    target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

# Enable testing
enable_testing()

# Add tests subdirectory only if GTest is found
if(BUILD_TESTS)
    add_subdirectory(test)
else()
    message(STATUS "Skipping ComponentProtection tests (Google Test not available)")
endif()
