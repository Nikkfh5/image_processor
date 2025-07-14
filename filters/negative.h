#pragma once

#include "filters.h"

namespace filter {
class Negative : public Filter {
public:
    Image Apply(Image& image) override;
};
}  // namespace filter
