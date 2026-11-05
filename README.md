# ComplexLab

A C++17 toolkit for exploring complex numbers, mathematical functions, and
fractals without relying on `std::complex` as the public abstraction.

## Features

- `Complex` values with real and imaginary components
- Arithmetic with complex values and real scalars
- Magnitude, squared magnitude, phase, conjugate, reciprocal, and formatting
- Polar-coordinate construction
- Complex `exp`, `log`, `pow`, `sqrt`, `sin`, `cos`, `tan`, `sinh`, `cosh`, and `tanh`
- Tolerance-aware comparisons for numerical tests
- Mandelbrot and Julia set rendering to portable PPM images
- `complexlab` command-line renderer with configurable size and iterations

## Build with CMake

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/complex_demo
./build/complexlab --output mandelbrot.ppm
./build/complexlab --type julia --julia -0.8 0.156 --output julia.ppm
```

The project requires C++17 or newer.

PPM files can be opened by macOS Preview, GIMP, ImageMagick, and most image
viewers. For a smaller quick render:

```bash
./build/complexlab --width 800 --height 600 --iterations 300
```

## Example

```cpp
#include "complex_analysis/complex.hpp"

using complex_analysis::Complex;
using complex_analysis::pow;

int main() {
    const Complex z{2.0, 3.0};
    const Complex result = pow(z, 3);
}
```

## Roadmap

- PNG export and richer color palettes
- Newton fractals and escape-time smoothing
- Complex contour integration and numerical root finding
- Interactive viewer and benchmarks
