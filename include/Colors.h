#ifndef COLORS_H
#define COLORS_H

#include <map>

struct RGB {
    uint8_t r, g, b;
};

enum class Color {
    Salmon,
    Orange,
    Yellow,
    Green,
    Cyan,
    Purple,
    Red
};

namespace Colors {
    extern const std::map<Color, RGB> Mapper;
}

#endif // COLORS_H