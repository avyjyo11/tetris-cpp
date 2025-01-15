#ifndef TETRIMINO_H
#define TETRIMINO_H

#include "Block.h"

#include <map>
#include <QRect>
#include <QPainter>

enum class TetrominoType : uint8_t {
    I = 0, J, L, O, S, T, Z
};

class Tetromino: public Block {
public:
    explicit Tetromino(TetrominoType type);

    void rotate() override;
    void draw(QPainter &painter) const override;
    void activate(std::vector<std::vector<std::optional<RGB>>>& grid) override;

    std::vector<std::vector<uint8_t>>* getGrid();
    int getX();
    int getY();
    RGB getColor();

private:
    TetrominoType type;
};

#endif // TETRIMINO_H