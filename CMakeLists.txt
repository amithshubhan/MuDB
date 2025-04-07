cmake_minimum_required(VERSION 3.16)
project(lsm_storage_engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)


# Include directories
include_directories(include)

# Add zlib from external source
add_subdirectory(external/zlib)

# Sources
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create the executable
add_executable(lsm_engine ${SOURCES})

# Link zlib static library
target_link_libraries(lsm_engine PRIVATE zlibstatic)

# Optional: make zlib headers available (in case they aren’t by default)
target_include_directories(lsm_engine PRIVATE external/zlib)
