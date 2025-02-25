#include <gtest/gtest.h>

#include "../include/Block.h"
#include "../include/BlockFactory.h"
#include <memory>

TEST(BlockTest, MoveLeft) {
  std::shared_ptr<Block> block = BlockFactory::createBlock();
  int currentXPos = block->getX();

  block->moveLeft();
  ASSERT_EQ(block->getX(), currentXPos - 1);
}

TEST(BlockTest, MoveRight) {
  std::shared_ptr<Block> block = BlockFactory::createBlock();
  int currentXPos = block->getX();

  block->moveRight();
  ASSERT_EQ(block->getX(), currentXPos + 1);
}

TEST(BlockTest, MoveDown) {
  std::shared_ptr<Block> block = BlockFactory::createBlock();
  int currentYPos = block->getY();

  block->moveDown();
  ASSERT_EQ(block->getY(), currentYPos + 1);
}

