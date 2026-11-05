#include <cmath>
#include <iostream>

#include "complex_analysis/complex.hpp"

int main() {
    using complex_analysis::Complex;
    using complex_analysis::exp;
    using complex_analysis::log;
    using complex_analysis::polar;
    using complex_analysis::pow;
    using complex_analysis::sqrt;

    const Complex z{2.0, 3.0};
    std::cout << "z = " << z << '\n'
              << "|z| = " << z.magnitude() << '\n'
              << "arg(z) = " << z.phase() << " radians\n"
              << "conjugate(z) = " << z.conjugate() << '\n'
              << "z^3 = " << pow(z, 3) << '\n'
              << "exp(z) = " << exp(z) << '\n'
              << "log(z) = " << log(z) << '\n'
              << "sqrt(z) = " << sqrt(z) << '\n'
              << "polar(2, pi/4) = " << polar(2.0, std::acos(-1.0) / 4.0) << '\n';
}
