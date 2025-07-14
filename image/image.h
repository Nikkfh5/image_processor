#pragma once

#include <cstddef>
#include <stdexcept>
#include <cstdint>
#include <vector>

#include "color.h"

class Image {
public:
    Image() = default;
    Image(size_t width, size_t height);
    explicit Image(const std::vector<std::vector<Color>>& data);
    Image(const Image& other);
    ~Image() = default;

    size_t GetHeight() const;
    size_t GetWidth() const;
    const std::vector<std::vector<Color>>& GetData() const;
    Color& GetColor(size_t x, size_t y);
    const Color& GetColor(size_t x, size_t y) const;

    void SetColor(size_t x, size_t y, const Color& color);

    std::vector<Color> new_image_data;
    std::vector<Color> image_data;

private:
    void CheckHeightAndWidth(size_t height, size_t width) const;
    size_t width_ = 0;
    size_t height_ = 0;
    std::vector<std::vector<Color>> data_;
};
