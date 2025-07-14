#include "pixelate.h"
#include <algorithm>

filter::Pixelate::Pixelate(size_t block_size) : block_size_(block_size) {
}

Image filter::Pixelate::Apply(Image& image) {
    size_t width = image.GetWidth();
    size_t height = image.GetHeight();
    std::vector<std::vector<Color>> new_data = image.GetData();

    for (size_t y = 0; y < height; y += block_size_) {
        for (size_t x = 0; x < width; x += block_size_) {
            int sum_r = 0;
            int sum_g = 0;
            int sum_b = 0;
            int count = 0;

            for (size_t dy = 0; dy < block_size_; ++dy) {
                for (size_t dx = 0; dx < block_size_; ++dx) {
                    size_t ny = y + dy;
                    size_t nx = x + dx;
                    if (ny < height && nx < width) {
                        const Color& c = image.GetColor(nx, ny);
                        sum_r += c.red;
                        sum_g += c.green;
                        sum_b += c.blue;
                        ++count;
                    }
                }
            }

            Color avg(static_cast<uint8_t>(sum_b / count), static_cast<uint8_t>(sum_g / count),
                      static_cast<uint8_t>(sum_r / count));

            for (size_t dy = 0; dy < block_size_; ++dy) {
                for (size_t dx = 0; dx < block_size_; ++dx) {
                    size_t ny = y + dy;
                    size_t nx = x + dx;
                    if (ny < height && nx < width) {
                        new_data[ny][nx] = avg;
                    }
                }
            }
        }
    }

    return Image(new_data);
}
