#include "crop.h"

filter::Crop::Crop(size_t width, size_t height) : crop_width_(width), crop_height_(height) {
}

Image filter::Crop::Apply(Image& image) {
    size_t actual_width = std::min(crop_width_, image.GetWidth());
    size_t actual_height = std::min(crop_height_, image.GetHeight());

    std::vector<std::vector<Color>> cropped_data;
    cropped_data.reserve(actual_height);
    size_t first_y = image.GetHeight() - actual_height;
    for (size_t y = 0; y < actual_height; ++y) {
        std::vector<Color> row;
        row.reserve(actual_width);
        for (size_t x = 0; x < actual_width; ++x) {
            row.push_back(image.GetColor(x, first_y + y));
        }
        cropped_data.push_back(std::move(row));
    }

    return Image(cropped_data);
}
