#pragma once

#include <memory>
#include "../image/image.h"
#include "../parser/parser.h"
#include "../utils.h"

namespace filter {
class Filter {
public:
    Filter() = default;
    virtual ~Filter() = default;
    virtual Image Apply(Image& image) = 0;

protected:
    template <typename T>
    std::vector<T> GetPixColors(const std::vector<std::vector<T>>& trans_matr, const Image& image, size_t i,
                                size_t j) const;
};
std::unique_ptr<Filter> MakeFilter(const parser::Argument& arguments);
}  // namespace filter
