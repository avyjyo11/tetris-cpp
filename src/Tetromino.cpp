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

Tetromino::Tetromino(TetrominoType type): Block(), type(type) {
    grid = tetrominoGrids[type];

    Color randColor = static_cast<Color>(rand() % 7);
    color = Colors::Mapper.at(randColor);
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

void Tetromino::draw(QPainter &painter) const {
    for (size_t i = 0 ; i < grid.size(); i++) {
        for (size_t j = 0; j < grid.size(); j++) {
            if (grid[i][j] == 1) {
                QColor qcolor(color.r, color.g, color.b);
                painter.setBrush(qcolor);
                painter.drawRect((x + j) * CELL_SIZE, (y + i) * CELL_SIZE, CELL_SIZE, CELL_SIZE);
            }
        }
    }
}

void Tetromino::activate(std::vector<std::vector<std::optional<RGB>>>& gameGrid) {
    for (size_t i = 0; i < grid.size(); i++) {
        for (size_t j = 0; j < grid.size(); j++) {
            if (grid[i][j] == 1) {
                int row = y + i;
                int col = x + j;
                gameGrid[row][col] = color;
            }
        }
    }
}