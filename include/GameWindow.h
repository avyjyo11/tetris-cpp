#ifndef GameWINDOW_H
#define GameWINDOW_H

#include "Block.h"
#include "NextWindow.h"

#include <QWidget>
#include <QTimer>
#include <QRect>
#include <QKeyEvent>
#include <map>
#include <vector>
#include <memory>
#include <optional>

#define ROWS 20
#define COLS 10

class GameWindow : public QWidget {
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr, NextWindow *next = nullptr);
    ~GameWindow();

    void startGame();
    void pauseGame();
    void restartGame();
    bool isRunning() const;
    unsigned int getScore() const;

protected:
    void paintEvent(QPaintEvent *event) override; 
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

signals:
    void scoreUpdated(unsigned int newScore); 
    
private slots:
    void updateAnimation();

private:
    int blockSpeed;
    QTimer *timer;
    NextWindow *nextWindow;
    std::shared_ptr<Block> block;

    bool running = false; 
    bool isMovingDown = false;

    // uint8_t grid[ROWS][COLS];
    std::vector<std::vector<std::optional<RGB>>> grid;
    
    const int cellSize = CELL_SIZE;
    unsigned int score;

    void plotBlock();         
    void drawGrid(QPainter &painter);
    bool canMoveBlock(int dx, int dy);
    void clearLines();
    void updateScore(unsigned int points);
};

#endif // GAMEWINDOW_H