#ifndef NEXTWINDOW_H
#define NEXTWINDOW_H

#include "Block.h"

#include <QWidget>
#include <deque>
#include <queue>
#include <memory>

class NextWindow : public QWidget {
    Q_OBJECT

public:
    explicit NextWindow(QWidget *parent = nullptr);

    void updateNextBlocks();
    std::shared_ptr<Block> getNextBlock();
    
protected:
    void paintEvent(QPaintEvent *event) override;

private:
    std::deque<std::shared_ptr<Block>> nextBlocks;
};

#endif // NEXTWINDOW_H
