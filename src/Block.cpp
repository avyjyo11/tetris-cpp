#include "../include/Block.h"
#include <QRect>

Block::Block(int cellSize, int blockSpeed)
    : cellSize(cellSize), blockSpeed(blockSpeed), rect(0, 0, cellSize, cellSize) {}

QRect Block::getRect() const {
    return rect;
}

void Block::moveLeft() {
    rect.moveLeft(rect.left() - cellSize);
}

void Block::moveRight() {
    rect.moveRight(rect.right() + cellSize);
}

void Block::moveDown() {
    rect.moveTop(rect.top() + blockSpeed);
}

void Block::reset(int startX, int startY) {
    rect.moveTo(startX, startY);
}