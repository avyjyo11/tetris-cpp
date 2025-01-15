#ifndef BLOCK_H
#define BLOCK_H

#include "Colors.h"
#include <vector>
#include <QPainter>

#define CELL_SIZE 32

class Block {
public:
    Block();
    virtual ~Block() = default;
    
    virtual void rotate();
    virtual void draw(QPainter &painter) const = 0;
    virtual void activate(std::vector<std::vector<std::optional<RGB>>>& grid) = 0;

    void moveLeft();
    void moveRight();
    void moveDown();
    void setPos(int x, int y);
    
    std::vector<std::vector<uint8_t>>* getGrid();
    int getX() const;
    int getY() const;
    RGB getColor() const;


protected:
    std::vector<std::vector<uint8_t>> grid;
    RGB color;
    int x, y;
};

#endif // BLOCK_H