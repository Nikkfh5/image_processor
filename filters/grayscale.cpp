#include "grayscale.h"

Image filter::Grayscale::Apply(Image& image) {
    std::vector<std::vector<Color>> new_image_data;
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        std::vector<Color> new_row(image.GetWidth());
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            const Color& pix = image.GetColor(j, i);
            uint8_t gray_color =
                static_cast<uint8_t>(pix.red * image::utils::GS_CF[0] + pix.green * image::utils::GS_CF[1] +
                                     pix.blue * image::utils::GS_CF[2]);
            new_row[j] = {gray_color, gray_color, gray_color};
        }
        new_image_data.push_back(new_row);
    }
    return Image(new_image_data);
}
