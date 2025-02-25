cmake_minimum_required(VERSION 3.14)

project(Tetris VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)  
set(CMAKE_AUTORCC ON)

link_directories("/opt/homebrew/Cellar/qt/6.8.2/lib")
link_directories("/opt/homebrew/Cellar/fftw/3.3.10_2/lib")
link_directories("/opt/homebrew/Cellar/libsndfile/1.2.2_1/lib")

find_package(FFTW3 REQUIRED)
find_package(SndFile REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Multimedia)

find_package(GTest REQUIRED)
enable_testing()

file(GLOB_RECURSE SOURCES src/*.cpp)
# all .cpp files except main.cpp
list(FILTER SOURCES EXCLUDE REGEX "src/main.cpp")

file(GLOB_RECURSE HEADERS include/*.h)

add_executable(Tetris ${SOURCES} ${HEADERS} src/main.cpp)
target_link_libraries(Tetris PUBLIC Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Multimedia sndfile fftw3)

qt_add_resources(Tetris "app_images"
    FILES
        images/bomb.png
        images/clear.png
        images/color.png
)

# Test executable
file(GLOB_RECURSE TEST_SOURCES tests/*.cpp) 

add_executable(TetrisTests ${TEST_SOURCES} ${SOURCES} ${HEADERS})
target_link_libraries(TetrisTests PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Multimedia sndfile fftw3 GTest::GTest GTest::Main)

add_test(NAME RunTests COMMAND TetrisTests)