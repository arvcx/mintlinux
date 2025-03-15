cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(CrossMint VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-w -O2)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# Add include directories
include_directories(${PROJECT_SOURCE_DIR}/enet)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/handler)

add_executable(CrossMint Mint.cpp)

set_target_properties(CrossMint PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Release
)
