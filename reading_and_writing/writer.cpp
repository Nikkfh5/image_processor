#include "writer.h"
#include "reader.h"
#include <fstream>
namespace read_and_write {
size_t GetPaddingSize(size_t width) {
    return (4 - (width * image::utils::BYTES_PER_PIXEL) % 4) % 4;
}

void Writer::NumberToBytes(size_t number, unsigned char* bytes) {
    bytes[0] = static_cast<unsigned char>(number & image::utils::BYTE_MASK);
    for (size_t i = 0; i < image::utils::SHIFT_BYTES.size(); i++) {
        bytes[i + 1] = static_cast<unsigned char>((number >> image::utils::SHIFT_BYTES[i]) & image::utils::BYTE_MASK);
    }
}
Writer::Writer(std::string filename) : path_(std::move(filename)) {
}
void Writer::WriteDIBHeader(unsigned char* dib_header, size_t width, size_t height) {
    dib_header[0] = image::utils::DIB_HEADER_SIZE_BYTE;
    for (size_t i = 1; i < image::utils::DIB_HEADER_SIZE; ++i) {
        dib_header[i] = 0;
    }

    NumberToBytes(width, dib_header + image::utils::WIDTH_POSITION);
    NumberToBytes(height, dib_header + image::utils::HEIGHT_POSITION);
    NumberToBytes(image::utils::CNT_OF_PLANES, dib_header + image::utils::CNT_OF_PLANES_POSITION);
    NumberToBytes(image::utils::BYTES_PER_PIXEL * image::utils::BIT_DEPTH, dib_header + image::utils::OFFSET_BIT_DEPTH);

    size_t padding = read_and_write::GetPaddingSize(width);
    size_t raw_size = height * (width * image::utils::BYTES_PER_PIXEL + padding);
    NumberToBytes(raw_size, dib_header + image::utils::DATA_SIZE_POSITION);
}

void Writer::WriteBMPHeader(unsigned char* bmp_header, size_t file_size) {
    bmp_header[0] = image::utils::FORMAT_BYTES[0];
    bmp_header[1] = image::utils::FORMAT_BYTES[1];
    NumberToBytes(file_size, bmp_header + 2);
    bmp_header[image::utils::BMP_HEADER_OFFSET] =
        static_cast<unsigned char>(image::utils::BMP_HEADER_SIZE + image::utils::DIB_HEADER_SIZE);
}
void read_and_write::Writer::WriteImage(const Image& image) const {
    size_t width = image.GetWidth();
    size_t height = image.GetHeight();
    size_t padding_size = GetPaddingSize(width);
    size_t file_size = image::utils::BMP_HEADER_SIZE + image::utils::DIB_HEADER_SIZE +
                       height * (width * image::utils::BYTES_PER_PIXEL + padding_size);

    std::ofstream out_file(path_, std::ios::binary);
    if (!out_file.is_open()) {
        throw std::runtime_error("Cannot open file for writing: " + path_);
    }

    unsigned char bmp_header[image::utils::BMP_HEADER_SIZE] = {};
    unsigned char dib_header[image::utils::DIB_HEADER_SIZE] = {};

    WriteBMPHeader(bmp_header, file_size);
    WriteDIBHeader(dib_header, width, height);

    out_file.write(reinterpret_cast<char*>(bmp_header), image::utils::BMP_HEADER_SIZE);
    out_file.write(reinterpret_cast<char*>(dib_header), image::utils::DIB_HEADER_SIZE);

    unsigned char padding[3] = {0, 0, 0};

    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            Color color = image.GetColor(j, i);
            unsigned char pixel[3] = {color.blue, color.green, color.red};
            out_file.write(reinterpret_cast<char*>(pixel), image::utils::BYTES_PER_PIXEL);
        }
        out_file.write(reinterpret_cast<char*>(padding), static_cast<std::streamsize>(padding_size));
    }

    out_file.close();
}
}  // namespace read_and_write
