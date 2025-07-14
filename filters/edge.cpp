#include "edge.h"
#include <algorithm>
#include <cmath>

filter::EdgeDetection::EdgeDetection(double threshold) : threshold_(threshold) {
}

inline uint8_t Gray(const Color& c) {
    return static_cast<uint8_t>(c.red * image::utils::GS_CF[0] + c.green * image::utils::GS_CF[1] +
                                c.blue * image::utils::GS_CF[2]);
}

Image filter::EdgeDetection::Apply(Image& image) {
    const std::vector<std::vector<int>> kernel = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};

    size_t height = image.GetHeight();
    size_t width = image.GetWidth();

    std::vector<std::vector<uint8_t>> gray(height, std::vector<uint8_t>(width));
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            gray[y][x] = Gray(image.GetColor(x, y));
        }
    }

    std::vector<std::vector<Color>> result(height, std::vector<Color>(width));

    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            int conv = 0;
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    size_t nx = std::clamp<int>(static_cast<int>(x) + dx, 0, static_cast<int>(width) - 1);
                    size_t ny = std::clamp<int>(static_cast<int>(y) + dy, 0, static_cast<int>(height) - 1);
                    conv += kernel[dy + 1][dx + 1] * gray[ny][nx];
                }
            }
            double norm_val = conv / image::utils::GRAYSCALE_DIVISOR;
            if (norm_val >= threshold_) {
                result[y][x] =
                    Color(image::utils::MAX_COLOR_VALUE, image::utils::MAX_COLOR_VALUE, image::utils::MAX_COLOR_VALUE);
            } else {
                result[y][x] = Color(0, 0, 0);
            }
        }
    }

    return Image(result);
}
