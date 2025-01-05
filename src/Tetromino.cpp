#include "../include/Block.h"
#include "../include/Tetromino.h"
#include "../include/GameWindow.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

std::map<TetrominoType, std::vector<std::vector<uint8_t>>> tetrominoGrids = {
    {TetrominoType::I, {
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }},
    {TetrominoType::J, {
        {1, 0, 0},
        {1, 1, 1},
        {0, 0, 0}
    }},
    {TetrominoType::L, {
        {0, 0, 1},
        {1, 1, 1},
        {0, 0, 0}
    }},
    {TetrominoType::O, {
        {1, 1},
        {1, 1}
    }},
    {TetrominoType::S, {
        {0, 1, 1},
        {1, 1, 0},
        {0, 0, 0}
    }},
    {TetrominoType::T, {
        {0, 1, 0},
        {1, 1, 1},
        {0, 0, 0}
    }},
    {TetrominoType::Z, {
        {1, 1, 0},
        {0, 1, 1},
        {0, 0, 0}
    }}
};

Tetromino::Tetromino(TetrominoType type) {
    grid = tetrominoGrids[type];
    x = 3;
    y = 0;
}

std::vector<std::vector<uint8_t>>* Tetromino::getGrid() {
    return &grid;
}

int Tetromino::getX() {
    return x;
}

int Tetromino::getY() {
    return y;
}

void Tetromino::rotate() {
    std::vector<std::vector<uint8_t>> newGrid(grid.size(), std::vector<uint8_t>(grid.size()));
    for (size_t i = 0; i < grid.size(); i++) {
        for (size_t j = 0; j < grid.size(); j++) {
            newGrid[j][grid.size() - i - 1] = grid[i][j];
        }
    }
    grid = newGrid;
}

void Tetromino::moveLeft() {
    x = x - 1;
}

void Tetromino::moveRight() {
    x = x + 1;
}

void Tetromino::moveDown() {
    y = y + 1;
}

void Tetromino::reset() {
    TetrominoType randType = static_cast<TetrominoType>(rand() % 7);
    grid = tetrominoGrids[randType];
    x = 3;
    y = 0;
}

void Tetromino::draw(QPainter &painter) const {
    for (size_t i = 0 ; i < grid.size(); i++) {
        for (size_t j = 0; j < grid.size(); j++) {
            if (grid[i][j] == 1) {
                painter.setBrush(Qt::blue);
                painter.drawRect((x + j) * CELL_SIZE, (y + i) * CELL_SIZE, CELL_SIZE, CELL_SIZE);
            }
        }
    }
}