#include "image.h"

Image::Image(size_t width, size_t height) : width_(width), height_(height), data_(height, std::vector<Color>(width)) {
}

Image::Image(const std::vector<std::vector<Color>>& data)
    : width_(data.empty() ? 0 : data[0].size()), height_(data.size()), data_(data) {
}

Image::Image(const Image& other) : width_(other.width_), height_(other.height_), data_(other.data_) {
}

void Image::CheckHeightAndWidth(size_t x, size_t y) const {
    if (x >= width_ || y >= height_) {
        throw std::invalid_argument("Coordinates out of range");
    }
}

size_t Image::GetHeight() const {
    return height_;
}

size_t Image::GetWidth() const {
    return width_;
}

const std::vector<std::vector<Color>>& Image::GetData() const {
    return data_;
}

Color& Image::GetColor(size_t x, size_t y) {
    CheckHeightAndWidth(x, y);
    return data_[y][x];
}

const Color& Image::GetColor(size_t x, size_t y) const {
    CheckHeightAndWidth(x, y);
    return data_[y][x];
}

void Image::SetColor(size_t x, size_t y, const Color& color) {
    CheckHeightAndWidth(x, y);
    data_[y][x] = color;
}
