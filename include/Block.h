#ifndef BLOCK_H
#define BLOCK_H

#include <QRect>

#define CELL_SIZE 32

class Block {
public:
    explicit Block(int x = 0, int y = 0);

    QRect getRect() const; 

    void moveLeft();   
    void moveRight();   
    void moveDown();   
    void reset();

private:
    QRect rect;
    int cellSize = CELL_SIZE; 
    int blockSpeed = CELL_SIZE;
};

#endif // BLOCK_H