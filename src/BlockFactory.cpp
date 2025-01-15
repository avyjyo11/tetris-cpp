#include "../include/BlockFactory.h"
#include "../include/Tetromino.h"
#include "../include/PowerUp.h"
#include <memory>

std::shared_ptr<Block> BlockFactory::createBlock() {
    // if (rand() % 10 == 0) {
    if (rand() % 4 == 0) {
        PowerUpType type = static_cast<PowerUpType>(rand() % 3); // Randomly choose a power-up type
        return std::make_shared<PowerUp>(type);
    } else {
        TetrominoType type = static_cast<TetrominoType>(rand() % 7); // Randomly choose a tetromino type
        return std::make_shared<Tetromino>(type);
    }
}