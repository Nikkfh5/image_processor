#pragma once

#include <fstream>
#include <string>

#include "../image/image.h"

namespace read_and_write {
class Reader {
public:
    explicit Reader(const std::string& path);
    Image ReadFile() const;

private:
    static size_t BytesToNumber(const unsigned char* bytes);
    std::string path_;
};

size_t GetPaddingSize(size_t width);
};  // namespace read_and_write
