#ifndef POWERUP_H
#define POWERUP_H

#include "Block.h"

#include <map>
#include <QImage>
#include <QPainter>

enum class PowerUpType : uint8_t {
    Clear,
    Bomb,
    Color
};

class PowerUp : public Block {
public:
    explicit PowerUp(PowerUpType type);
    ~PowerUp();

    void rotate() override;
    void draw(QPainter &painter) const override;

    void activate(std::vector<std::vector<std::optional<RGB>>>& grid) override;

private:
    PowerUpType type;
    QImage image;
};

#endif // POWERUP_H