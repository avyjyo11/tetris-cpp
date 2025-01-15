#include "../include/GameWindow.h"

#include <iostream>
#include <cstring>
#include <QRect>
#include <QTimer>
#include <QPainter>
#include <QKeyEvent>

GameWindow::GameWindow(QWidget *parent, NextWindow *next)
    : QWidget(parent), nextWindow(next), blockSpeed(CELL_SIZE), grid(ROWS, std::vector<std::optional<RGB>>(COLS, std::nullopt)) {
    setMinimumSize(cellSize * COLS, cellSize * ROWS);
    setFocusPolicy(Qt::StrongFocus);

    block = next->getNextBlock();
    timer = new QTimer(this);
    
    connect(timer, &QTimer::timeout, this, &GameWindow::updateAnimation);
    timer->stop(); // Update every 100 ms
}

GameWindow::~GameWindow() {
}

void GameWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    painter.fillRect(rect(), Qt::black);
    // Placeholder for drawing blocks (later replaced by actual Tetris logic)
    drawGrid(painter);
    block->draw(painter);
}

void GameWindow::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Left:
        if (canMoveBlock(-1, 0)) {
            block->moveLeft();
        }
        break;
    case Qt::Key_Right:
        if (canMoveBlock(1, 0)) {
            block->moveRight();
        }
        break;
    case Qt::Key_Up:
        block->rotate();
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

    for (auto& row : grid) {
        std::fill(row.begin(), row.end(), std::nullopt);
    }
    
    block = nextWindow->getNextBlock();

    timer->start(1000);
    running = true;
}

void GameWindow::updateScore(unsigned int points) {
    score += points;
    emit scoreUpdated(score); 
}

void GameWindow::drawGrid(QPainter &painter) {
    QColor customGray(64, 64, 64);
    painter.setPen(customGray);

    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            QRect cell(col * cellSize, row * cellSize, cellSize, cellSize);
            // Draw filled cells
            if (grid[row][col].has_value()) {
                RGB rgb = grid[row][col].value();
                QColor color(rgb.r, rgb.g, rgb.b);
                painter.setBrush(color);
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
        block->moveDown();
        updateScore(1);
    } else {
        block->activate(grid);
        clearLines();
        block = nextWindow->getNextBlock();
    }
    update();
}


bool GameWindow::canMoveBlock(int dx, int dy) {
    auto tGrid = block->getGrid();

    if (block->getY() < 0) {
        return true;
    }

    for (size_t i = 0; i < tGrid->size(); i++) {
        for (size_t j = 0; j < tGrid->size(); j++) {
            if ((*tGrid)[i][j] == 1) {
                int newRow = block->getY() + i + dy;
                int newCol = block->getX() + j + dx;
                if (newRow >= ROWS || newCol < 0 || newCol >= COLS || grid[newRow][newCol].has_value()) {
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
            if (grid[row][col] == std::nullopt) {
                fullLine = false;
                break;
            }
        }
        if (fullLine) {
            for (int r = row; r > 0; --r) {
                grid[r] = grid[r - 1];
            }
            grid[0] = std::vector<std::optional<RGB>>(COLS, std::nullopt);
            row++;
            updateScore(10);
        }
    }
}
