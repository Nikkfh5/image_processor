#pragma once

#include "filters.h"

namespace filter {
class Crop : public Filter {
public:
    Crop(size_t width, size_t height);
    Image Apply(Image& image) override;

private:
    size_t crop_width_;
    size_t crop_height_;
};
}  // namespace filter
