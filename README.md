# Complex Analysis Library

A small C++17 library for working with complex numbers without relying on
`std::complex` as the public abstraction.

## Features

- `Complex` values with real and imaginary components
- Arithmetic with complex values and real scalars
- Magnitude, squared magnitude, phase, conjugate, reciprocal, and formatting
- Polar-coordinate construction
- Complex `exp`, `log`, `pow`, `sqrt`, `sin`, `cos`, `tan`, `sinh`, `cosh`, and `tanh`
- Tolerance-aware comparisons for numerical tests

## Build with CMake

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/complex_demo
```

The project requires C++17 or newer.

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
