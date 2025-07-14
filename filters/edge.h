#pragma once

#include "filters.h"

namespace filter {
class EdgeDetection : public Filter {
public:
    explicit EdgeDetection(double threshold);
    Image Apply(Image& image) override;

private:
    double threshold_;
};
}  // namespace filter
