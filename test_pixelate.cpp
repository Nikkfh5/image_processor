#include <iostream>
#include <cassert>
#include "image/image.h"
#include "reading_and_writing/reader.h"
#include "filters/pixelate.h"

bool ImagesEqual(const Image& a, const Image& b) {
    if (a.GetWidth() != b.GetWidth() || a.GetHeight() != b.GetHeight()) {
        return false;
    }
    for (size_t y = 0; y < a.GetHeight(); ++y) {
        for (size_t x = 0; x < a.GetWidth(); ++x) {
            const Color& ca = a.GetColor(x, y);
            const Color& cb = b.GetColor(x, y);
            if (ca.red != cb.red || ca.green != cb.green || ca.blue != cb.blue) {
                return false;
            }
        }
    }
    return true;
}

int Main1() {
    const std::string input_path = "test_data/lenna.bmp";
    const std::string expected_path = "test_data/lenna_pixelated.bmp";
    const size_t block_size = image::utils::BASE_BLOCK_SIZE;

    read_and_write::Reader reader_input(input_path);
    read_and_write::Reader reader_expected(expected_path);

    Image input = reader_input.ReadFile();
    Image expected = reader_expected.ReadFile();

    filter::Pixelate filter(block_size);
    Image result = filter.Apply(input);

    if (!ImagesEqual(result, expected)) {
        std::cerr << "Test failed" << std::endl;
        return 1;
    }

    std::cout << "Pixelate test passed!" << std::endl;
    return 0;
}