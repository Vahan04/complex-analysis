#include <cassert>
#include <cmath>
#include <stdexcept>

#include "complex_analysis/complex.hpp"
#include "complex_analysis/fractal.hpp"

using complex_analysis::Complex;
using complex_analysis::approximately_equal;

int main() {
    const Complex a{3.0, 4.0};
    const Complex b{1.0, -2.0};

    assert(a.real() == 3.0);
    assert(a.imaginary() == 4.0);
    assert(a.magnitude() == 5.0);
    assert((a.conjugate() == Complex{3.0, -4.0}));
    assert((a + b == Complex{4.0, 2.0}));
    assert((a - b == Complex{2.0, 6.0}));
    assert((a * b == Complex{11.0, -2.0}));
    assert(approximately_equal(a / b, Complex{-1.0, 2.0}));
    assert(approximately_equal(complex_analysis::sqrt(Complex{3.0, 4.0}), Complex{2.0, 1.0}));
    assert(approximately_equal(
        complex_analysis::exp(complex_analysis::log(a)), a));
    assert(approximately_equal(
        complex_analysis::sin(Complex{0.0, 0.0}), Complex{}));
    assert(approximately_equal(
        complex_analysis::cos(Complex{0.0, 0.0}), Complex{1.0}));

    bool threw = false;
    try {
        (void)a.reciprocal();
    } catch (...) {
        threw = true;
    }
    assert(!threw);

    try {
        (void)Complex{}.reciprocal();
    } catch (const std::domain_error&) {
        threw = true;
    }
    assert(threw);

    const auto inside = complex_analysis::colorize(100, 100);
    const auto outside = complex_analysis::colorize(0, 100);
    assert(inside.red == 0 && inside.green == 0 && inside.blue == 0);
    assert(outside.red == 0 && outside.green == 0 && outside.blue == 255);
}
