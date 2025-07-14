#pragma once

#include "filters.h"

namespace filter {
class Pixelate : public Filter {
public:
    explicit Pixelate(size_t block_size);
    Image Apply(Image& image) override;

private:
    size_t block_size_;
};
}  // namespace filter
