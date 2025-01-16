cmake_minimum_required(VERSION 3.10)

project(Tetris VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "/usr/local/Cellar/qt/6.7.3/lib/cmake")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)  
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Multimedia)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.h)

add_executable(Tetris ${SOURCES} ${HEADERS})

target_link_libraries(Tetris PUBLIC Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Multimedia)

qt_add_resources(Tetris "app_images"
    FILES
        images/bomb.png
        images/clear.png
        images/color.png
)