# Minimum version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(Tetris VERSION 1.0)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# Add source and header files
include_directories(include)
add_subdirectory(src)

# Create the executable target
add_executable(Tetris src/main.cpp)

# Link the library from src/ to the executable
target_link_libraries(Tetris PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets TetrisCore)

set_target_properties(Tetris PROPERTIES AUTOUIC ON AUTORCC ON)