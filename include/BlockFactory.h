#ifndef BLOCKFACTORY_H
#define BLOCKFACTORY_H

#include "Block.h"
#include <memory>

class BlockFactory {
    public:
    static std::shared_ptr<Block> createBlock();
};

#endif // BLOCKFACTORY_H