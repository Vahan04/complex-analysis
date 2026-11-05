#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

#include "complex_analysis/fractal.hpp"

namespace {

void print_usage(const char* program) {
    std::cout
        << "Usage: " << program << " [options]\n\n"
        << "Render a Mandelbrot or Julia set as a PPM image.\n\n"
        << "Options:\n"
        << "  --type mandelbrot|julia   Fractal type (default: mandelbrot)\n"
        << "  --output FILE              Output PPM path (default: fractal.ppm)\n"
        << "  --width N                  Image width (default: 1200)\n"
        << "  --height N                 Image height (default: 800)\n"
        << "  --iterations N             Maximum iterations (default: 500)\n"
        << "  --julia REAL IMAGINARY     Julia constant (default: -0.8 0.156)\n"
        << "  --help                     Show this help\n";
}

std::size_t parse_size(const std::string& value, const char* option) {
    const long parsed = std::strtol(value.c_str(), nullptr, 10);
    if (parsed <= 0) {
        throw std::invalid_argument(std::string(option) + " must be positive");
    }
    return static_cast<std::size_t>(parsed);
}

}  // namespace

int main(int argc, char** argv) {
    try {
        complex_analysis::FractalConfig config;
        std::string output_path = "fractal.ppm";

        for (int index = 1; index < argc; ++index) {
            const std::string option = argv[index];
            if (option == "--help") {
                print_usage(argv[0]);
                return 0;
            }
            if (index + 1 >= argc && option != "--help") {
                throw std::invalid_argument("missing value for " + option);
            }
            if (option == "--type") {
                const std::string type = argv[++index];
                if (type == "mandelbrot") {
                    config.type = complex_analysis::FractalType::mandelbrot;
                } else if (type == "julia") {
                    config.type = complex_analysis::FractalType::julia;
                } else {
                    throw std::invalid_argument("type must be mandelbrot or julia");
                }
            } else if (option == "--output") {
                output_path = argv[++index];
            } else if (option == "--width") {
                config.width = parse_size(argv[++index], "--width");
            } else if (option == "--height") {
                config.height = parse_size(argv[++index], "--height");
            } else if (option == "--iterations") {
                config.max_iterations = static_cast<int>(
                    parse_size(argv[++index], "--iterations"));
            } else if (option == "--julia") {
                config.julia_real = std::stod(argv[++index]);
                if (++index >= argc) {
                    throw std::invalid_argument("--julia requires real and imaginary values");
                }
                config.julia_imaginary = std::stod(argv[index]);
            } else {
                throw std::invalid_argument("unknown option: " + option);
            }
        }

        complex_analysis::render_fractal(config, output_path);
        std::cout << "Wrote " << output_path << '\n';
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
