#include "../include/NextWindow.h"
#include "../include/BlockFactory.h"
#include <QPainter>

NextWindow::NextWindow(QWidget *parent) : QWidget(parent) {
    setFixedSize(160, 300);
    updateNextBlocks();
}

std::shared_ptr<Block> NextWindow::getNextBlock() {
    if (nextBlocks.empty()) {
        return nullptr;
    }
    
    std::shared_ptr<Block> block = nextBlocks.front();
    block->setPos(3,-1);

    nextBlocks.pop_front();
    if (nextBlocks.size() < 2) {
        updateNextBlocks();
    }
    return block;
}

void NextWindow::updateNextBlocks() {
    while (nextBlocks.size() < 2) {
        nextBlocks.push_back(BlockFactory::createBlock());
    }
    update();
}

void NextWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.fillRect(rect(), Qt::black);

    for (size_t i = 0; i < nextBlocks.size(); ++i) {
        if (nextBlocks[i]) {
            nextBlocks[i]->draw(painter);
            // Offset the position for the next block displayx
            painter.translate(0, (i + 1) * 140);
        }
    }
}
