#ifndef BLOCK_H
#define BLOCK_H

#include <QRect>

class Block {
public:
    explicit Block(int cellSize = 40, int blockSpeed = 5); 

    QRect getRect() const; 

    void moveLeft();   
    void moveRight();   
    void moveDown();   
    void reset(int startX, int startY);

private:
    QRect rect;  
    int cellSize; 
    int blockSpeed; 
};

#endif // BLOCK_H