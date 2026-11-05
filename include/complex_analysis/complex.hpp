#pragma once

#include <cstddef>
#include <iosfwd>
#include <string>

namespace complex_analysis {

class Complex {
public:
    constexpr Complex(double real = 0.0, double imaginary = 0.0) noexcept
        : real_(real), imaginary_(imaginary) {}

    [[nodiscard]] constexpr double real() const noexcept { return real_; }
    [[nodiscard]] constexpr double imaginary() const noexcept { return imaginary_; }
    [[nodiscard]] double magnitude() const noexcept;
    [[nodiscard]] double magnitude_squared() const noexcept;
    [[nodiscard]] double phase() const noexcept;
    [[nodiscard]] Complex conjugate() const noexcept;
    [[nodiscard]] Complex reciprocal() const;
    [[nodiscard]] std::string to_string(int precision = 6) const;

    Complex& operator+=(const Complex& other) noexcept;
    Complex& operator-=(const Complex& other) noexcept;
    Complex& operator*=(const Complex& other) noexcept;
    Complex& operator/=(const Complex& other);

    Complex& operator+=(double value) noexcept;
    Complex& operator-=(double value) noexcept;
    Complex& operator*=(double value) noexcept;
    Complex& operator/=(double value);

private:
    double real_;
    double imaginary_;
};

[[nodiscard]] Complex operator+(Complex left, const Complex& right) noexcept;
[[nodiscard]] Complex operator-(Complex left, const Complex& right) noexcept;
[[nodiscard]] Complex operator*(Complex left, const Complex& right) noexcept;
[[nodiscard]] Complex operator/(Complex left, const Complex& right);
[[nodiscard]] Complex operator-(const Complex& value) noexcept;

[[nodiscard]] Complex operator+(Complex value, double scalar) noexcept;
[[nodiscard]] Complex operator+(double scalar, Complex value) noexcept;
[[nodiscard]] Complex operator-(Complex value, double scalar) noexcept;
[[nodiscard]] Complex operator-(double scalar, const Complex& value) noexcept;
[[nodiscard]] Complex operator*(Complex value, double scalar) noexcept;
[[nodiscard]] Complex operator*(double scalar, Complex value) noexcept;
[[nodiscard]] Complex operator/(Complex value, double scalar);
[[nodiscard]] Complex operator/(double scalar, const Complex& value);

[[nodiscard]] bool operator==(const Complex& left, const Complex& right) noexcept;
[[nodiscard]] bool operator!=(const Complex& left, const Complex& right) noexcept;
std::ostream& operator<<(std::ostream& stream, const Complex& value);

[[nodiscard]] Complex polar(double radius, double angle);
[[nodiscard]] Complex exp(const Complex& value) noexcept;
[[nodiscard]] Complex log(const Complex& value);
[[nodiscard]] Complex pow(const Complex& base, const Complex& exponent);
[[nodiscard]] Complex pow(const Complex& base, int exponent);
[[nodiscard]] Complex sqrt(const Complex& value);
[[nodiscard]] Complex sin(const Complex& value) noexcept;
[[nodiscard]] Complex cos(const Complex& value) noexcept;
[[nodiscard]] Complex tan(const Complex& value);
[[nodiscard]] Complex sinh(const Complex& value) noexcept;
[[nodiscard]] Complex cosh(const Complex& value) noexcept;
[[nodiscard]] Complex tanh(const Complex& value);

[[nodiscard]] bool approximately_equal(
    const Complex& left,
    const Complex& right,
    double absolute_tolerance = 1e-12,
    double relative_tolerance = 1e-12) noexcept;

}  // namespace complex_analysis
