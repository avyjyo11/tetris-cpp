#include "../include/Block.h"
#include <QRect>

Block::Block(int x, int y)
    : rect(x, y, CELL_SIZE, CELL_SIZE) {}

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

void Block::reset() {
    rect.moveTo(0, rect.left());
}