#include "filters.h"
#include "gauss.h"
#include "grayscale.h"
#include "negative.h"
#include "crop.h"
#include "edge.h"
#include "sharp.h"
#include "pixelate.h"
template <typename T>
std::vector<T> filter::Filter::GetPixColors(const std::vector<std::vector<T>>& trans_matr, const Image& image, size_t i,
                                            size_t j) const {
    std::vector<T> colors;
    size_t mat_height = trans_matr.size();
    size_t mat_width = trans_matr[0].size();

    for (size_t di = 0; di < mat_height; ++di) {
        for (size_t dj = 0; dj < mat_width; ++dj) {
            size_t x = i + di - mat_height / 2;
            size_t y = j + dj - mat_width / 2;

            if (x < image.GetHeight() && y < image.GetWidth()) {
                colors.push_back(image.GetColor(y, x));
            }
        }
    }
    return colors;
}

std::unique_ptr<filter::Filter> filter::MakeFilter(const parser::Argument& argument) {
    const std::string& name = argument.name;
    if (name == "-neg") {
        if (!argument.parameters.empty()) {
            throw std::invalid_argument("Invalid argument for -neg");
        }
        return std::make_unique<filter::Negative>();
    } else if (name == "-pixelate") {
        if (argument.parameters.size() != 1) {
            throw std::invalid_argument("Invalid argument for -pixelate");
        }
        size_t size = std::stoul(argument.parameters[0]);
        return std::make_unique<filter::Pixelate>(size);
    } else if (name == "-edge") {
        if (argument.parameters.size() != 1) {
            throw std::invalid_argument("Invalid argument for -edge");
        }
        try {
            double threshold = std::stod(argument.parameters[0]);
            return std::make_unique<filter::EdgeDetection>(threshold);
        } catch (...) {
            throw std::invalid_argument("Invalid threshold for -edge");
        }
    } else if (name == "-sharp") {
        if (!argument.parameters.empty()) {
            throw std::invalid_argument("Invalid argument for -sharp");
        }
        return std::make_unique<filter::Sharpening>();
    } else if (name == "-crop") {
        if (argument.parameters.size() != 2) {
            throw std::invalid_argument("Invalid argument for -crop");
        }
        size_t w = std::stoi(argument.parameters[0]);
        size_t h = std::stoi(argument.parameters[1]);
        return std::make_unique<filter::Crop>(w, h);
    }

    else if (name == "-gs") {
        if (!argument.parameters.empty()) {
            throw std::invalid_argument("Invalid argument for -gs");
        }
        return std::make_unique<filter::Grayscale>();
    } else if (name == "-blur") {
        if (argument.parameters.size() != 1) {
            throw std::invalid_argument("Invalid argument for -blur");
        }
        try {
            float sigma = std::stof(argument.parameters.front());
            return std::make_unique<GaussianBlurFilter>(sigma);
        } catch (const std::invalid_argument& e) {
            throw std::invalid_argument("Invalid argument for -blur" + static_cast<std::string>(e.what()));
        }
    }
    throw std::invalid_argument("Unknown filter: " + name);
}
