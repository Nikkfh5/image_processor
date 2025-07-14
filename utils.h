#include <array>
#include <cstddef>
#include <cstdint>
#ifndef IMAGE_UTILS_H
#define IMAGE_UTILS_H

namespace image::utils {
const uint32_t BMP_HEADER_SIZE = 14;
const uint32_t DIB_HEADER_SIZE = 40;
const uint32_t F_B_FIRST_POS = 0;
const uint32_t F_B_SECOND_POS = 1;
const uint32_t WIDTH_POSITION = 4;
const uint32_t HEIGHT_POSITION = 8;
const uint32_t BYTES_PER_PIXEL = 3;
const uint32_t INPUT_FILE_POSITION = 0;
const uint32_t OUTPUT_FILE_POSITION = 1;
const size_t CNT_OF_PLANES = 1;
const size_t CNT_OF_PLANES_POSITION = 12;
const size_t DATA_SIZE_POSITION = 20;
const std::array<double, 3> GS_CF = {0.299, 0.587, 0.114};
const std::array<char, 2> FORMAT_BYTES = {'B', 'M'};
const std::array<int32_t, 3> SHIFT_BYTES = {8, 16, 24};
const uint8_t MAX_COLOR_VALUE = 255;
const double GRAYSCALE_DIVISOR = 255.0;
const uint8_t BIT_DEPTH = 8;
const uint8_t DIB_HEADER_SIZE_BYTE = 40;
const uint8_t OFFSET_BIT_DEPTH = 14;
const uint8_t BMP_HEADER_OFFSET = 10;
const uint8_t BYTE_MASK = 0xFF;
const int NORMING = 12;
const auto MAXL_COLOR_VALUE = 255L;
const int BASE_BLOCK_SIZE = 25;
const int BASE_BLUE_COLOR = 10;
const int BASE_RED_COLOR = 30;
const int BASE_GREEN_COLOR = 20;
const int BASE_COORDINATES = 5;
const int BIG_COORDINATES = 20;
const int NORM_COORDINATES = 10;

}  // namespace image::utils
#endif
