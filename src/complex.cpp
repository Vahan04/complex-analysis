#include "complex_analysis/complex.hpp"

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <ostream>
#include <sstream>
#include <stdexcept>

namespace complex_analysis {
double Complex::magnitude() const noexcept {
    return std::hypot(real_, imaginary_);
}

double Complex::magnitude_squared() const noexcept {
    return real_ * real_ + imaginary_ * imaginary_;
}

double Complex::phase() const noexcept {
    return std::atan2(imaginary_, real_);
}

Complex Complex::conjugate() const noexcept {
    return {real_, -imaginary_};
}

Complex Complex::reciprocal() const {
    const double squared = magnitude_squared();
    if (squared == 0.0) {
        throw std::domain_error("cannot calculate the reciprocal of zero");
    }
    return {real_ / squared, -imaginary_ / squared};
}

std::string Complex::to_string(int precision) const {
    if (precision < 0) {
        throw std::invalid_argument("precision cannot be negative");
    }
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(precision) << real_;
    if (imaginary_ >= 0.0) {
        stream << " + " << imaginary_ << 'i';
    } else {
        stream << " - " << -imaginary_ << 'i';
    }
    return stream.str();
}

Complex& Complex::operator+=(const Complex& other) noexcept {
    real_ += other.real_;
    imaginary_ += other.imaginary_;
    return *this;
}

Complex& Complex::operator-=(const Complex& other) noexcept {
    real_ -= other.real_;
    imaginary_ -= other.imaginary_;
    return *this;
}

Complex& Complex::operator*=(const Complex& other) noexcept {
    const double new_real = real_ * other.real_ - imaginary_ * other.imaginary_;
    imaginary_ = real_ * other.imaginary_ + imaginary_ * other.real_;
    real_ = new_real;
    return *this;
}

Complex& Complex::operator/=(const Complex& other) {
    return *this *= other.reciprocal();
}

Complex& Complex::operator+=(double value) noexcept {
    real_ += value;
    return *this;
}

Complex& Complex::operator-=(double value) noexcept {
    real_ -= value;
    return *this;
}

Complex& Complex::operator*=(double value) noexcept {
    real_ *= value;
    imaginary_ *= value;
    return *this;
}

Complex& Complex::operator/=(double value) {
    if (value == 0.0) {
        throw std::domain_error("cannot divide by zero");
    }
    real_ /= value;
    imaginary_ /= value;
    return *this;
}

Complex operator+(Complex left, const Complex& right) noexcept { return left += right; }
Complex operator-(Complex left, const Complex& right) noexcept { return left -= right; }
Complex operator*(Complex left, const Complex& right) noexcept { return left *= right; }
Complex operator/(Complex left, const Complex& right) { return left /= right; }
Complex operator-(const Complex& value) noexcept { return {-value.real(), -value.imaginary()}; }

Complex operator+(Complex value, double scalar) noexcept { return value += scalar; }
Complex operator+(double scalar, Complex value) noexcept { return value += scalar; }
Complex operator-(Complex value, double scalar) noexcept { return value -= scalar; }
Complex operator-(double scalar, const Complex& value) noexcept {
    return {scalar - value.real(), -value.imaginary()};
}
Complex operator*(Complex value, double scalar) noexcept { return value *= scalar; }
Complex operator*(double scalar, Complex value) noexcept { return value *= scalar; }
Complex operator/(Complex value, double scalar) { return value /= scalar; }
Complex operator/(double scalar, const Complex& value) { return scalar * value.reciprocal(); }

bool operator==(const Complex& left, const Complex& right) noexcept {
    return left.real() == right.real() && left.imaginary() == right.imaginary();
}

bool operator!=(const Complex& left, const Complex& right) noexcept {
    return !(left == right);
}

std::ostream& operator<<(std::ostream& stream, const Complex& value) {
    return stream << value.to_string();
}

Complex polar(double radius, double angle) {
    if (radius < 0.0) {
        throw std::domain_error("polar radius cannot be negative");
    }
    return {radius * std::cos(angle), radius * std::sin(angle)};
}

Complex exp(const Complex& value) noexcept {
    const double scale = std::exp(value.real());
    return {scale * std::cos(value.imaginary()), scale * std::sin(value.imaginary())};
}

Complex log(const Complex& value) {
    if (value.magnitude() == 0.0) {
        throw std::domain_error("the complex logarithm is undefined at zero");
    }
    return {std::log(value.magnitude()), value.phase()};
}

Complex pow(const Complex& base, const Complex& exponent) {
    if (base.magnitude() == 0.0) {
        if (exponent == Complex{}) {
            throw std::domain_error("zero cannot be raised to zero");
        }
        return {};
    }
    return exp(exponent * log(base));
}

Complex pow(const Complex& base, int exponent) {
    if (exponent == 0) {
        return {1.0};
    }
    if (exponent < 0) {
        return pow(base.reciprocal(), -exponent);
    }
    Complex result{1.0};
    Complex factor = base;
    auto remaining = static_cast<unsigned int>(exponent);
    while (remaining > 0) {
        if (remaining % 2 == 1) {
            result *= factor;
        }
        factor *= factor;
        remaining /= 2;
    }
    return result;
}

Complex sqrt(const Complex& value) {
    const double radius = value.magnitude();
    const double real_part = std::sqrt((radius + value.real()) / 2.0);
    const double imaginary_part =
        std::copysign(std::sqrt((radius - value.real()) / 2.0), value.imaginary());
    return {real_part, imaginary_part};
}

Complex sin(const Complex& value) noexcept {
    return {std::sin(value.real()) * std::cosh(value.imaginary()),
            std::cos(value.real()) * std::sinh(value.imaginary())};
}

Complex cos(const Complex& value) noexcept {
    return {std::cos(value.real()) * std::cosh(value.imaginary()),
            -std::sin(value.real()) * std::sinh(value.imaginary())};
}

Complex tan(const Complex& value) {
    return sin(value) / cos(value);
}

Complex sinh(const Complex& value) noexcept {
    return {std::sinh(value.real()) * std::cos(value.imaginary()),
            std::cosh(value.real()) * std::sin(value.imaginary())};
}

Complex cosh(const Complex& value) noexcept {
    return {std::cosh(value.real()) * std::cos(value.imaginary()),
            std::sinh(value.real()) * std::sin(value.imaginary())};
}

Complex tanh(const Complex& value) {
    return sinh(value) / cosh(value);
}

bool approximately_equal(
    const Complex& left,
    const Complex& right,
    double absolute_tolerance,
    double relative_tolerance) noexcept {
    if (absolute_tolerance < 0.0 || relative_tolerance < 0.0) {
        return false;
    }
    const auto close = [absolute_tolerance, relative_tolerance](double a, double b) {
        const double difference = std::abs(a - b);
        return difference <= absolute_tolerance +
            relative_tolerance * std::max(std::abs(a), std::abs(b));
    };
    return close(left.real(), right.real()) && close(left.imaginary(), right.imaginary());
}

}  // namespace complex_analysis
