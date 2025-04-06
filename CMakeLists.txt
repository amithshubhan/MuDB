cmake_minimum_required(VERSION 3.16)
project(lsm_storage_engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Sources
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(lsm_engine ${SOURCES})
