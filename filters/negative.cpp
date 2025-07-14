#include "negative.h"

Image filter::Negative::Apply(Image& image) {
    std::vector<std::vector<Color>> new_data = image.GetData();
    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            Color c = image.GetColor(x, y);
            new_data[y][x] = Color(image::utils::MAX_COLOR_VALUE - c.blue, image::utils::MAX_COLOR_VALUE - c.green,
                                   image::utils::MAX_COLOR_VALUE - c.red);
            ;
        }
    }
    return Image(new_data);
}
