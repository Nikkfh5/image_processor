#include "color.h"

Color::Color(uint8_t blue, uint8_t green, uint8_t red) : red(red), green(green), blue(blue) {
}

void Color::Set(uint8_t in_blue, uint8_t in_green, uint8_t in_red) {
    blue = in_blue;
    green = in_green;
    red = in_red;
}
