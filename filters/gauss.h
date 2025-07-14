#pragma once

#include "filters.h"
#include <math.h>

namespace filter {
class GaussianBlurFilter : public Filter {
public:
    GaussianBlurFilter() = default;
    explicit GaussianBlurFilter(float sigma);
    Image Apply(Image& image) final;

private:
    static std::vector<int> BoxesForGauss(float sigma, double number);
    static void BoxBlur(const std::vector<Color>& source, std::vector<Color>& target, size_t width, size_t height,
                        float sigma);
    static void BoxBlurH(const std::vector<Color>& source, std::vector<Color>& target, size_t width, size_t height,
                         float sigma);
    static void BoxBlurT(const std::vector<Color>& source, std::vector<Color>& target, size_t width, size_t height,
                         float sigma);
    float sigma_ = 0.0f;
};
}  // namespace filter
