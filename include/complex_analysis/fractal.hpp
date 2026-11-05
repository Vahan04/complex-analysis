#pragma once

#include <cstddef>
#include <string>

namespace complex_analysis {

enum class FractalType {
    mandelbrot,
    julia
};

struct FractalConfig {
    std::size_t width = 1200;
    std::size_t height = 800;
    double min_real = -2.5;
    double max_real = 1.0;
    double min_imaginary = -1.25;
    double max_imaginary = 1.25;
    int max_iterations = 500;
    FractalType type = FractalType::mandelbrot;
    double julia_real = -0.8;
    double julia_imaginary = 0.156;
};

struct Rgb {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

[[nodiscard]] Rgb colorize(int iterations, int max_iterations) noexcept;
void render_fractal(const FractalConfig& config, const std::string& output_path);

}  // namespace complex_analysis
