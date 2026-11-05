#include "complex_analysis/fractal.hpp"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <stdexcept>

#include "complex_analysis/complex.hpp"

namespace complex_analysis {

Rgb colorize(int iterations, int max_iterations) noexcept {
    if (iterations >= max_iterations) {
        return {0, 0, 0};
    }

    const double ratio = static_cast<double>(iterations) / max_iterations;
    const auto channel = [](double value) {
        return static_cast<unsigned char>(std::clamp(value, 0.0, 255.0));
    };
    return {
        channel(255.0 * std::pow(ratio, 0.35)),
        channel(180.0 * std::pow(ratio, 0.55)),
        channel(255.0 * std::pow(1.0 - ratio, 1.5))
    };
}

void render_fractal(const FractalConfig& config, const std::string& output_path) {
    if (config.width == 0 || config.height == 0) {
        throw std::invalid_argument("fractal dimensions must be positive");
    }
    if (config.max_iterations <= 0) {
        throw std::invalid_argument("max_iterations must be positive");
    }
    if (!(config.min_real < config.max_real) ||
        !(config.min_imaginary < config.max_imaginary)) {
        throw std::invalid_argument("fractal bounds must be increasing");
    }

    std::ofstream output(output_path);
    if (!output) {
        throw std::runtime_error("could not open output file: " + output_path);
    }
    output << "P3\n" << config.width << ' ' << config.height << "\n255\n";

    for (std::size_t row = 0; row < config.height; ++row) {
        const double imaginary = config.height == 1
        ? (config.min_imaginary + config.max_imaginary) / 2.0
        : config.max_imaginary -
            (config.max_imaginary - config.min_imaginary) * row / (config.height - 1);
        for (std::size_t column = 0; column < config.width; ++column) {
        const double real = config.width == 1
            ? (config.min_real + config.max_real) / 2.0
            : config.min_real +
                (config.max_real - config.min_real) * column / (config.width - 1);
            Complex z;
            const Complex constant = config.type == FractalType::julia
                ? Complex{config.julia_real, config.julia_imaginary}
                : Complex{real, imaginary};
            if (config.type == FractalType::julia) {
                z = {real, imaginary};
            }

            int iterations = 0;
            while (iterations < config.max_iterations && z.magnitude_squared() <= 4.0) {
                z = z * z + constant;
                ++iterations;
            }
            const Rgb color = colorize(iterations, config.max_iterations);
            output << static_cast<int>(color.red) << ' '
                   << static_cast<int>(color.green) << ' '
                   << static_cast<int>(color.blue) << '\n';
        }
    }
}

}  // namespace complex_analysis
