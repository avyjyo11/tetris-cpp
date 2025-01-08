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

std::map<Colors, RGB> ColorsMap = {
    {Colors::Salmon, {250, 128, 114}},
    {Colors::Orange, {255, 200, 46}},
    {Colors::Yellow, {254, 251, 52}},
    {Colors::Green, {83, 218, 63}},
    {Colors::Cyan, {1, 237, 250}},
    {Colors::Purple, {221, 10, 178}},
    {Colors::Red, {234, 20, 28}},
};

Tetromino::Tetromino() {
    reset();
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

void Tetromino::reset() {
    TetrominoType randType = static_cast<TetrominoType>(rand() % 7);
    grid = tetrominoGrids[randType];

    Colors randColor = static_cast<Colors>(rand() % 7);
    color = ColorsMap[randColor];

    x = 3;
    y = -1;
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