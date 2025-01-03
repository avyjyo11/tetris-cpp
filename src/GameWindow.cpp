#include "../include/GameWindow.h"
#include <iostream>
#include <cstring>
#include <QRect>
#include <QTimer>
#include <QPainter>
#include <QKeyEvent>

GameWindow::GameWindow(QWidget *parent): QWidget(parent), blockSpeed(5) {
    setMinimumSize(cellSize * COLS, cellSize * ROWS);
    setFocusPolicy(Qt::StrongFocus);

    qDebug() << "GameWindow has focus:" << hasFocus();
    // Initialize grid to all 0s
    memset(grid, 0, sizeof(grid));

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameWindow::updateAnimation);
    timer->start(100); // Update every 100 ms
}

GameWindow::~GameWindow() {
    delete timer;
}

void GameWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    painter.fillRect(rect(), Qt::black);
    // Placeholder for drawing blocks (later replaced by actual Tetris logic)
    drawGrid(painter);

    painter.setBrush(Qt::blue);
    painter.drawRect(block.getRect()); // Draw a block as a simple example
}

void GameWindow::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Left:
        if (canMoveBlock(-1, 0)) {
            block.moveLeft();
        }
        break;
    case Qt::Key_Right:
        if (canMoveBlock(1, 0)) {
            block.moveRight();
        }
        break;
    }
    update();
}

void GameWindow::startAnimation() {
    // Reset block position and start timer
    printf("startAnimation");
    // timer->start(30); // 30ms interval for smooth animation
}

void GameWindow::stopAnimation() {
    timer->stop();
}

void GameWindow::drawGrid(QPainter &painter) {
    painter.setPen(Qt::gray);

    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            QRect cell(col * cellSize, row * cellSize, cellSize, cellSize);

            // Draw filled cells
            if (grid[row][col] == 1) {
                painter.setBrush(Qt::green);
                painter.drawRect(cell);
            }

            // Draw grid lines
            painter.setBrush(Qt::NoBrush);
            painter.drawRect(cell);
        }
    }
}

void GameWindow::updateAnimation() {
    if (canMoveBlock(0, 1)) {
        block.moveDown();
    } else {
        plotBlock();
        block.reset(0, 0);
    }
    update();
}

void GameWindow::plotBlock() {
    QRect rect = block.getRect();
    int row = rect.top() / cellSize;
    int col = rect.left() / cellSize;

    grid[row][col] = 1;
}

bool GameWindow::canMoveBlock(int dx, int dy) {
    QRect rect = block.getRect();
    int newRow = rect.top() / cellSize + dy;
    int newCol = rect.left() / cellSize + dx;

    if (newRow < 0 || newRow >= ROWS || newCol < 0 || newCol >= COLS) {
        return false;
    }
    // Check if the new position is already filled
    return grid[newRow][newCol] == 0;
}
