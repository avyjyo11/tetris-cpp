#include "../include/Block.h"
#include "../include/GameWindow.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

Block::Block() : x(1), y(1) {
}

void Block::rotate() {}

void Block::setPos(int _x, int _y) {
    x = _x;
    y = _y;
}

void Block::moveLeft() {
    x -= 1;
}

void Block::moveRight() {
    x += 1;
}

void Block::moveDown() {
    y += 1;
}

std::vector<std::vector<uint8_t>>* Block::getGrid() {
    return &grid;
}

int Block::getX() const {
    return x;
}

int Block::getY() const {
    return y;
}

RGB Block::getColor() const {
    return color;
}