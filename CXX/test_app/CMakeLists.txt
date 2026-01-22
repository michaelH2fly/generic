# Test application CMakeLists.txt
project(ComponentProtectionTestApp)

# Define executable name
set(EXECUTABLE_NAME ComponentProtectionTest)

# Source files
set(SOURCES
    main.cc
)

# Create executable
add_executable(${EXECUTABLE_NAME} ${SOURCES})

# Link against ComponentProtection library
target_link_libraries(${EXECUTABLE_NAME} PRIVATE ComponentProtection)

# Specify include directories (CMake will handle this through ComponentProtection target)
target_include_directories(${EXECUTABLE_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../ComponentProtection/inc
)
