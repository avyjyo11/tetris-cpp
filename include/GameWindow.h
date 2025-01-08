#ifndef GameWINDOW_H
#define GameWINDOW_H

#include "../include/Block.h"
#include "../include/Tetromino.h"

#include <QWidget>
#include <QTimer>
#include <QRect>
#include <QKeyEvent>
#include <map>
#include <vector>
#include <optional>

#define ROWS 20
#define COLS 10

enum class Colors : uint8_t {
    Salmon,
    Orange,
    Yellow,
    Green,
    Cyan,
    Purple,
    Red,
};
class GameWindow : public QWidget {
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
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
    Block* block;

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