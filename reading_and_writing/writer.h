#pragma once

#include <string>
#include "../image/image.h"
#include "../utils.h"

namespace read_and_write {
class Writer {
public:
    explicit Writer(std::string filename);
    void WriteImage(const Image &image) const;

private:
    static void NumberToBytes(size_t number, unsigned char *bytes);
    static void WriteBMPHeader(unsigned char *bmp_header, size_t file_size);
    static void WriteDIBHeader(unsigned char *dib_header, size_t width, size_t height);
    std::string path_;
};
}  // namespace read_and_write
