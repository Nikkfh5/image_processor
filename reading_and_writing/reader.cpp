#include "reader.h"
#include "../utils.h"

Image read_and_write::Reader::ReadFile() const {
    unsigned char bmp_header[image::utils::BMP_HEADER_SIZE];
    std::ifstream img_file;
    img_file.open(path_, std::ios::binary | std::ios::in);
    if (!img_file.is_open()) {
        throw std::invalid_argument("File" + path_ + " not found");
    }
    if (errno == EACCES) {
        throw std::invalid_argument("File" + path_ + " is not accessible");
    }
    img_file.read(reinterpret_cast<char *>(bmp_header), image::utils::BMP_HEADER_SIZE);
    if (bmp_header[image::utils::F_B_FIRST_POS] != image::utils::FORMAT_BYTES[image::utils::F_B_FIRST_POS] ||
        bmp_header[image::utils::F_B_SECOND_POS] != image::utils::FORMAT_BYTES[image::utils::F_B_SECOND_POS]) {
        throw std::invalid_argument("File" + path_ + " is not BMP file");
    }

    try {
        unsigned char dib_header[image::utils::DIB_HEADER_SIZE];
        img_file.read(reinterpret_cast<char *>(dib_header), image::utils::DIB_HEADER_SIZE);
        size_t width = BytesToNumber(dib_header + image::utils::WIDTH_POSITION);
        size_t height = BytesToNumber(dib_header + image::utils::HEIGHT_POSITION);
        Image image(width, height);
        std::vector<std::vector<Color>> image_data(height);
        std::vector<Color> tmp_row(width);
        for (size_t i = 0; i < height; ++i) {
            for (size_t j = 0; j < width; ++j) {
                unsigned char pix[image::utils::BYTES_PER_PIXEL];
                img_file.read(reinterpret_cast<char *>(pix), image::utils::BYTES_PER_PIXEL);
                tmp_row[j].Set(static_cast<uint8_t>(pix[0]), static_cast<uint8_t>(pix[1]),
                               static_cast<uint8_t>(pix[2]));
            }
            image_data[i] = tmp_row;
            img_file.ignore(static_cast<std::streamsize>(GetPaddingSize(width)));
        }
        image = Image(image_data);
        img_file.close();
        return image;
    } catch (std::exception &e) {
        throw std::invalid_argument("Error reading file: " + path_ + ": " + static_cast<std::string>(e.what()));
    }
}
read_and_write::Reader::Reader(const std::string &path) : path_(path) {
}
size_t read_and_write::Reader::BytesToNumber(const unsigned char *bytes) {
    size_t number = *bytes;
    for (size_t i = 0; i < image::utils::SHIFT_BYTES.size(); i++) {
        number += *(bytes + i + 1) << image::utils::SHIFT_BYTES[i];
    }
    return number;
}
