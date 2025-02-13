#ifndef COLOR_H
#define COLOR_H

#include "stdint.h"

namespace io {
    constexpr uint32_t WHITE = 0x00ffffff; //白色
    constexpr uint32_t BLACK = 0x00000000; //黑色
    constexpr uint32_t RED = 0x00ff0000; //红色
    constexpr uint32_t ORANGE = 0x00ff8000l; //橙色
    constexpr uint32_t YELLOW = 0x00ffff00; //黄色
    constexpr uint32_t GREEN = 0x0000ff00; //绿色
    constexpr uint32_t BLUE = 0x000000ff; //蓝色
    constexpr uint32_t INDIGO = 0x0000ffff; //靛色
    constexpr uint32_t PURPLE = 0x008000ff; //紫色
}
#endif //COLOR_H
