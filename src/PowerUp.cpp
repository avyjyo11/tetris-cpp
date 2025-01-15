#include "../include/GameWindow.h"
#include "../include/PowerUp.h"
#include "../include/Colors.h"

#include <QFile>
#include <QPainter>

std::map<PowerUpType, std::string> PowerImages = {
    {PowerUpType::Clear, ":/images/clear.png"},
    {PowerUpType::Bomb, ":/images/bomb.png"},
    {PowerUpType::Color, ":/images/color.png"},
};

PowerUp::PowerUp(PowerUpType type) : Block(), type(type) {
    grid = {{1}};

    Color randColor = static_cast<Color>(rand() % 7);
    color = Colors::Mapper.at(randColor);
    
    image.load(PowerImages.at(type).c_str());
}

PowerUp::~PowerUp() {
    // No dynamic allocation in this class, so no need to delete anything here
}

void PowerUp::draw(QPainter &painter) const {
    QColor qcolor(color.r, color.g, color.b);
    painter.setBrush(qcolor);
    painter.drawRect(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE);
    painter.drawImage(QRect(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE), image);
}

void PowerUp::rotate() { }

void PowerUp::activate(std::vector<std::vector<std::optional<RGB>>>& grid) {
    switch (type) {
        case PowerUpType::Clear:
            for (int col = 0; col < grid[0].size(); ++col) {
                grid[y][col] = std::nullopt; // Clear the row
            }
            for (int row = 0; row < grid.size(); ++row) {
                grid[row][x] = std::nullopt; // Clear the column
            }
            for (int r = y; r > 0; --r) {
                grid[r] = grid[r - 1];
            }
            grid[0] = std::vector<std::optional<RGB>>(COLS, std::nullopt);
            break;
        case PowerUpType::Bomb:
            // Logic to clear surrounding blocks (bomb effect)
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    int targetRow = y + i;
                    int targetCol = x + j;
                    if (targetRow >= 0 && targetRow < grid.size() && targetCol >= 0 && targetCol < grid[0].size()) {
                        grid[targetRow][targetCol] = std::nullopt; // Clear the block
                    }
                }
            }
            break;
        case PowerUpType::Color:
            // Logic to change color of blocks or tetrominoes
            // This could be implemented based on your game design.
            break;
    }
}
