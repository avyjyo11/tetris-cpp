#ifndef TETRIMINO_H
#define TETRIMINO_H

#include <map>

#include <QRect>
#include <QPainter>

enum TetrominoType : uint8_t {
    I, J, L, O, S, T, Z
};

class Tetromino {
public:
    explicit Tetromino(TetrominoType type = TetrominoType::L);

    void rotate();
    void moveLeft();
    void moveRight();
    void moveDown();
    void reset();
    void draw(QPainter &painter) const;

    std::vector<std::vector<uint8_t>>* getGrid();
    int getX();
    int getY();

private:
    std::vector<std::vector<uint8_t>> grid;
    int x, y;
};

#endif // TETRIMINO_H