#include "gauss.h"
#include <cmath>
#include <algorithm>
filter::GaussianBlurFilter::GaussianBlurFilter(float sigma) {
    sigma_ = sigma;
}
inline uint8_t Clamp255(double value) {
    return static_cast<uint8_t>(std::max(0.0, std::min(image::utils::GRAYSCALE_DIVISOR, std::round(value))));
}
std::vector<int> filter::GaussianBlurFilter::BoxesForGauss(float sigma, double number) {
    double width_ideal = sqrt(image::utils::NORMING * sigma * sigma / number + 1);
    int width_lower = floor(width_ideal);
    if (width_lower % 2 == 0) {
        --width_lower;
    }
    int width_upper = width_lower + 2;
    double m_ideal = (image::utils::NORMING * sigma * sigma - number * width_lower * width_lower -
                      4 * number * width_lower - 3 * number) /
                     (-4 * width_lower - 4);
    double m = round(m_ideal);
    std::vector<int> sizes;
    for (int i = 0; i < number; ++i) {
        sizes.push_back(i < m ? width_lower : width_upper);
    }
    return sizes;
}

void filter::GaussianBlurFilter::BoxBlur(const std::vector<Color>& source, std::vector<Color>& target, size_t width,
                                         size_t height, float sigma) {
    for (int i = 0; i < static_cast<int>(source.size()); ++i) {
        target[i] = source[i];
    }
    BoxBlurH(source, target, width, height, sigma);
    BoxBlurT(source, target, width, height, sigma);
}

void filter::GaussianBlurFilter::BoxBlurH(const std::vector<Color>& source, std::vector<Color>& target, size_t width,
                                          size_t height, float sigma) {
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            double new_red = 0;
            double new_green = 0;
            double new_blue = 0;
            int count = 0;

            for (int x = static_cast<int>(static_cast<float>(j) - sigma);
                 x <= static_cast<int>(static_cast<float>(j) + sigma); ++x) {
                int clamped_x = std::min(static_cast<int>(width - 1), std::max(0, x));
                const Color& c = source[i * width + clamped_x];

                new_red += static_cast<double>(c.red);
                new_green += static_cast<double>(c.green);
                new_blue += static_cast<double>(c.blue);
                ++count;
            }

            target[i * width + j] =
                Color(Clamp255(new_blue / count), Clamp255(new_green / count), Clamp255(new_red / count));
        }
    }
}

void filter::GaussianBlurFilter::BoxBlurT(const std::vector<Color>& source, std::vector<Color>& target, size_t width,
                                          size_t height, float sigma) {
    for (size_t i = 0; i < width; ++i) {
        for (size_t j = 0; j < height; ++j) {
            double new_red = 0;
            double new_green = 0;
            double new_blue = 0;
            int count = 0;

            for (int y = static_cast<int>(static_cast<float>(j) - sigma);
                 y <= static_cast<int>(static_cast<float>(j) + sigma); ++y) {
                int clamped_y = std::min(static_cast<int>(height - 1), std::max(0, y));
                const Color& c = source[clamped_y * width + i];

                new_red += static_cast<double>(c.red);
                new_green += static_cast<double>(c.green);
                new_blue += static_cast<double>(c.blue);
                ++count;
            }

            target[j * width + i] =
                Color(Clamp255(new_blue / count), Clamp255(new_green / count), Clamp255(new_red / count));
        }
    }
}
Image filter::GaussianBlurFilter::Apply(Image& image) {
    const int radius = static_cast<int>(std::ceil(3 * sigma_));
    const int kernel_size = 2 * radius + 1;
    const double two_sigma_sq = 2.0 * sigma_ * sigma_;
    std::vector<double> kernel(kernel_size);
    double kernel_sum = 0.0;
    for (int i = -radius; i <= radius; ++i) {
        double weight = std::exp(-(i * i) / two_sigma_sq);
        kernel[i + radius] = weight;
        kernel_sum += weight;
    }
    for (double& w : kernel) {
        w /= kernel_sum;
    }

    size_t height = image.GetHeight();
    size_t width = image.GetWidth();

    std::vector<std::vector<Color>> temp(height, std::vector<Color>(width));
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            double r = 0;
            double g = 0;
            double b = 0;
            for (int k = -radius; k <= radius; ++k) {
                int nx = std::clamp(static_cast<int>(x) + k, 0, static_cast<int>(width) - 1);
                const Color& c = image.GetColor(nx, y);
                double w = kernel[k + radius];
                r += c.red * w;
                g += c.green * w;
                b += c.blue * w;
            }
            temp[y][x] = Color(static_cast<uint8_t>(std::clamp(std::lround(b), 0L, image::utils::MAXL_COLOR_VALUE)),
                               static_cast<uint8_t>(std::clamp(std::lround(g), 0L, image::utils::MAXL_COLOR_VALUE)),
                               static_cast<uint8_t>(std::clamp(std::lround(r), 0L, image::utils::MAXL_COLOR_VALUE)));
        }
    }
    std::vector<std::vector<Color>> result(height, std::vector<Color>(width));
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            double r = 0;
            double g = 0;
            double b = 0;
            for (int k = -radius; k <= radius; ++k) {
                int ny = std::clamp(static_cast<int>(y) + k, 0, static_cast<int>(height) - 1);
                const Color& c = temp[ny][x];
                double w = kernel[k + radius];
                r += c.red * w;
                g += c.green * w;
                b += c.blue * w;
            }
            result[y][x] = Color(static_cast<uint8_t>(std::clamp(std::lround(b), 0L, image::utils::MAXL_COLOR_VALUE)),
                                 static_cast<uint8_t>(std::clamp(std::lround(g), 0L, image::utils::MAXL_COLOR_VALUE)),
                                 static_cast<uint8_t>(std::clamp(std::lround(r), 0L, image::utils::MAXL_COLOR_VALUE)));
        }
    }

    return Image(result);
}
