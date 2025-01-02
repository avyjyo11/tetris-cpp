# List of source files for the library
set(SOURCES
    game.cpp
)

# Create a library target
add_library(TetrisCore ${SOURCES})

# Include the headers for the library
target_include_directories(TetrisCore PUBLIC ${CMAKE_SOURCE_DIR}/include)