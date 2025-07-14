#pragma once

#include "filters.h"

namespace filter {
class Sharpening : public Filter {
public:
    Image Apply(Image& image) override;
};
}  // namespace filter
