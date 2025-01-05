#ifndef GameWINDOW_H
#define GameWINDOW_H

#include "../include/Block.h"
#include "../include/Tetromino.h"

#include <QWidget>
#include <QTimer>
#include <QRect>
#include <QKeyEvent>

#define ROWS 20
#define COLS 10

class GameWindow : public QWidget {
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

    void startAnimation();
    void stopAnimation();

protected:
    void paintEvent(QPaintEvent *event) override; 
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void updateAnimation();

private:
    QTimer *timer;  
    int blockSpeed;
    Block block;
    Tetromino tetromino;
    bool isMovingDown = false;

    uint8_t grid[ROWS][COLS]; 
    const int cellSize = CELL_SIZE;

    void plotBlock();         
    void drawGrid(QPainter &painter);
    bool canMoveBlock(int dx, int dy);
    void clearLines();
};

#endif // GAMEWINDOW_H