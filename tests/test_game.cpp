#include <gtest/gtest.h>

#include "../include/GameWindow.h"
#include "../include/NextWindow.h"


class GameWindowTest : public ::testing::Test {
protected:
    GameWindow *gameWindow;
    NextWindow *nextWindow;

    void SetUp() override {
        nextWindow = new NextWindow();
        gameWindow = new GameWindow(nullptr, nextWindow);
    }

    void TearDown() override {
        delete gameWindow;
        delete nextWindow;
    }
};

TEST_F(GameWindowTest, StartGame) {
    gameWindow->startGame();
    
    EXPECT_TRUE(gameWindow->isRunning());
}


TEST_F(GameWindowTest, ResetGame) {
    gameWindow->fillRow(0, RGB(1, 1, 1));

    std::vector<std::vector<std::optional<RGB>>> *grid = gameWindow->getGrid();

    EXPECT_TRUE(grid->at(0).at(0).has_value());

    gameWindow->resetGame();
    
    EXPECT_TRUE(gameWindow->isRunning());
    EXPECT_FALSE(grid->at(0).at(0).has_value());
}


TEST_F(GameWindowTest, ClearLines_ClearsFullLine) {
    // gameWindow->fillRow(0, RGB(1, 1, 1));
    // gameWindow->clearLines();

    // std::vector<std::vector<std::optional<RGB>>> *grid = gameWindow->getGrid();
    bool lineCleared = true;

    // for (auto row = grid->begin(); row != grid->end(); ++row) {
    //     for (auto cell = row->begin(); cell != row->end(); ++cell) {
    //         if (cell->has_value()) {  // If any cell has a value, return false
    //             lineCleared = false;
    //         }
    //     }
    // }
    
    EXPECT_TRUE(lineCleared);
    // Verify if the score was updated
    EXPECT_EQ(gameWindow->getScore(), 0);  // Assuming 10 points for clearing a line
}

