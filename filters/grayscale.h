#pragma once

#include "filters.h"

namespace filter {
class Grayscale : public Filter {
public:
    Image Apply(Image& image) override;
};
}  // namespace filter