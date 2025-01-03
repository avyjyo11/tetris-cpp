#ifndef GameWINDOW_H
#define GameWINDOW_H

#include "../include/Block.h"
#include <QWidget>
#include <QTimer>
#include <QRect>
#include <QKeyEvent>

#define ROWS 15
#define COLS 9
#define CELL_SIZE 40

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

private slots:
    void updateAnimation();

private:
    QTimer *timer;  
    Block block;
    int blockSpeed;

    int grid[ROWS][COLS]; 
    const int cellSize = CELL_SIZE;

    void plotBlock();         
    void drawGrid(QPainter &painter);
    bool canMoveBlock(int dx, int dy);
};

#endif // GAMEWINDOW_H