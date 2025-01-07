#include "../include/Block.h"
#include "../include/GameWindow.h"

#include <iostream>
#include <cstring>
#include <QRect>
#include <QTimer>
#include <QPainter>
#include <QKeyEvent>

GameWindow::GameWindow(QWidget *parent): QWidget(parent), blockSpeed(CELL_SIZE) {
    setMinimumSize(cellSize * COLS, cellSize * ROWS);
    setFocusPolicy(Qt::StrongFocus);
    // Initialize grid to all 0s
    memset(grid, 0, sizeof(grid));

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameWindow::updateAnimation);
    timer->stop(); // Update every 100 ms
}

GameWindow::~GameWindow() {
    delete timer;
}

void GameWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    painter.fillRect(rect(), Qt::black);
    // Placeholder for drawing blocks (later replaced by actual Tetris logic)
    drawGrid(painter);
    tetromino.draw(painter);
}

void GameWindow::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Left:
        if (canMoveBlock(-1, 0)) {
            tetromino.moveLeft();
        }
        break;
    case Qt::Key_Right:
        if (canMoveBlock(1, 0)) {
            tetromino.moveRight();
        }
        break;
    case Qt::Key_Up:
        tetromino.rotate();
        break;
    case Qt::Key_Down:
        if (!isMovingDown) { 
            isMovingDown = true;
            timer->start(60);
        }
        break;
    }
    update();
}

void GameWindow::keyReleaseEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Down) {
        isMovingDown = false;
        timer->start(1000);
    }
}

void GameWindow::startGame() {
    if (!running) {
        timer->start(1000);
        running = true;
    }
}

void GameWindow::pauseGame() {
    if (running) {
        timer->stop();
        running = false;
    }
}

bool GameWindow::isRunning() const {
    return running;
}

unsigned int GameWindow::getScore() const {
    return score;
}

void GameWindow::restartGame() {
    timer->stop();

    memset(grid, 0, sizeof(grid));
    tetromino.reset();
    
    timer->start(1000);
    running = true;
}

void GameWindow::updateScore(unsigned int points) {
    score += points;
}

void GameWindow::drawGrid(QPainter &painter) {
    QColor customGray(64, 64, 64);
    painter.setPen(customGray);

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
        tetromino.moveDown();
        updateScore(1);
    } else {
        plotBlock();
        clearLines();
        tetromino.reset();
    }
    update();
}

void GameWindow::plotBlock() {
    auto tGrid = tetromino.getGrid();
    for (size_t i = 0; i < tGrid->size(); i++) {
        for (size_t j = 0; j < tGrid->size(); j++) {
            if ((*tGrid)[i][j] == 1) {
                int row = tetromino.getY() + i;
                int col = tetromino.getX() + j;
                grid[row][col] = 1;
            }
        }
    }
}

bool GameWindow::canMoveBlock(int dx, int dy) {
    auto tGrid = tetromino.getGrid();

    if (tetromino.getY() < 0) {
        return true;
    }

    for (size_t i = 0; i < tGrid->size(); i++) {
        for (size_t j = 0; j < tGrid->size(); j++) {
            if ((*tGrid)[i][j] == 1) {
                int newRow = tetromino.getY() + i + dy;
                int newCol = tetromino.getX() + j + dx;
                if (newRow >= ROWS || newCol < 0 || newCol >= COLS || grid[newRow][newCol] == 1) {
                    return false;
                }
            }
        }
    }
    
    return true;
}

void GameWindow::clearLines() {
    for (int row = ROWS - 1; row >= 0; --row) {
        bool fullLine = true;
        for (int col = 0; col < COLS; ++col) {
            if (grid[row][col] == 0) {
                fullLine = false;
                break;
            }
        }
        if (fullLine) {
            for (int r = row; r > 0; --r) {
                memcpy(grid[r], grid[r - 1], sizeof(uint8_t) * COLS);
            }
            memset(grid[0], 0, sizeof(uint8_t) * COLS);
            row++;
            updateScore(10);
        }
    }
}
