#include "sharp.h"
#include <algorithm>
#include <cmath>

inline uint8_t Clamp(int value) {
    return static_cast<uint8_t>(std::clamp(value, 0, static_cast<int>(image::utils::MAX_COLOR_VALUE)));
}

Image filter::Sharpening::Apply(Image& image) {
    const std::vector<std::vector<int>> kernel = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};

    std::vector<std::vector<Color>> new_data = image.GetData();
    size_t height = image.GetHeight();
    size_t width = image.GetWidth();

    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            int red = 0;
            int green = 0;
            int blue = 0;
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    int nx = std::clamp<int>(static_cast<int>(x) + dx, 0, static_cast<int>(width) - 1);
                    int ny = std::clamp<int>(static_cast<int>(y) + dy, 0, static_cast<int>(height) - 1);
                    const Color& c = image.GetColor(nx, ny);
                    int weight = kernel[dy + 1][dx + 1];

                    red += weight * c.red;
                    green += weight * c.green;
                    blue += weight * c.blue;
                }
            }

            new_data[y][x] = Color(Clamp(blue), Clamp(green), Clamp(red));
        }
    }

    return Image(new_data);
}
