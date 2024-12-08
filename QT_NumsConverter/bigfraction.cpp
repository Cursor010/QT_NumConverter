#include "bigfraction.h"

BigInteger BigFraction::gcd(BigInteger first_number, BigInteger second_number) {
    if (second_number == 0) return first_number;
    return gcd(second_number, first_number % second_number);
}

BigFraction::BigFraction() : num_(0), den_(1) {}

BigFraction::BigFraction(BigInteger num, BigInteger den) {
    if (den == 0) {
        throw std::invalid_argument("Division by zero!");
    }
    num_ = num;
    den_ = den;
    normalize();
}

BigFraction::BigFraction(const BigFraction& other) : num_(other.num_), den_(other.den_) {}

BigInteger BigFraction::num() const { return num_; }

BigInteger BigFraction::den() const { return den_; }

BigFraction& BigFraction::operator=(const BigFraction& other) {
    if (this != &other) {
        num_ = other.num();
        den_ = other.den();
    }
    return *this;
}

BigFraction& BigFraction::operator+() {
    return *this;
}

BigFraction BigFraction::operator-() const {
    return BigFraction(-num_, den_);
}

BigFraction& BigFraction::operator++() {
    num_ += den_;
    return *this;
}

BigFraction BigFraction::operator++(int) {
    BigFraction current(*this);
    num_ += den_;
    return current;
}

BigFraction& BigFraction::operator--() {
    num_ -= den_;
    return *this;
}

BigFraction BigFraction::operator--(int) {
    BigFraction current(*this);
    num_ -= den_;
    return current;
}

BigFraction& BigFraction::operator+=(const BigFraction& other) {
    num_ = num_ * other.den() + other.num() * den_;
    den_ *= other.den();
    normalize();
    return *this;
}

BigFraction& BigFraction::operator-=(const BigFraction& other) {
    num_ = num_ * other.den() - other.num() * den_;
    den_ *= other.den();
    normalize();
    return *this;
}

BigFraction& BigFraction::operator*=(const BigFraction& other) {
    num_ *= other.num();
    den_ *= other.den();
    normalize();
    return *this;
}

BigFraction& BigFraction::operator/=(const BigFraction& other) {
    if (other.num_ == 0) {
        throw std::invalid_argument("Division by zero!");
    }
    num_ *= other.den();
    den_ *= other.num();
    normalize();
    return *this;
}

BigFraction BigFraction::operator+(const BigFraction& other) const {
    BigFraction res(*this);
    res += other;
    return res;
}

BigFraction BigFraction::operator-(const BigFraction& other) const {
    BigFraction res(*this);
    res -= other;
    return res;
}

BigFraction BigFraction::operator*(const BigFraction& other) const {
    BigFraction res(*this);
    res *= other;
    return res;
}

BigFraction BigFraction::operator/(const BigFraction& other) const {
    BigFraction res(*this);
    res /= other;
    return res;
}

BigFraction BigFraction::operator+(BigInteger other) const {
    BigFraction res(*this);
    res += BigFraction(other);
    return res;
}

BigFraction BigFraction::operator-(BigInteger other) const {
    BigFraction res(*this);
    res -= BigFraction(other);
    return res;
}

BigFraction BigFraction::operator*(BigInteger other) const {
    BigFraction res(*this);
    res *= BigFraction(other);
    return res;
}

BigFraction BigFraction::operator/(BigInteger other) const {
    BigFraction res(*this);
    res /= BigFraction(other);
    return res;
}

bool BigFraction::operator==(const BigFraction& other) const {
    return num_ == other.num() && den_ == other.den();
}

bool BigFraction::operator!=(const BigFraction& other) const {
    return !(*this == other);
}

bool BigFraction::operator<(const BigFraction& other) const {
    return num_ * other.den() < other.num() * den_;
}

bool BigFraction::operator<=(const BigFraction& other) const {
    return num_ * other.den() <= other.num() * den_;
}

bool BigFraction::operator>(const BigFraction& other) const {
    return num_ * other.den() > other.num() * den_;
}

bool BigFraction::operator>=(const BigFraction& other) const {
    return num_ * other.den() >= other.num() * den_;
}

void BigFraction::normalize() {
    BigInteger gcd_ = gcd(num_, den_);
    num_ /= gcd_;
    den_ /= gcd_;
    if (den_ < 0) {
        num_ = -num_;
        den_ = -den_;
    }
}

QTextStream& operator<<(QTextStream& out, const BigFraction& fract) {
    return out << fract.num() << '/' << fract.den();
}

BigFraction operator*(BigInteger num, const BigFraction& other) {
    return BigFraction(num) * other;
}

BigFraction operator/(BigInteger num, const BigFraction& other) {
    return BigFraction(num) / other;
}

BigFraction operator+(BigInteger num, const BigFraction& other) {
    return BigFraction(num) + other;
}

BigFraction operator-(BigInteger num, const BigFraction& other) {
    return BigFraction(num) - other;
}

bool operator==(BigInteger num, const BigFraction& other) {
    return num == other.num() && other.den() == 1;
}

bool operator!=(BigInteger num, const BigFraction& other) {
    return !(BigFraction(num) == other);
}

bool operator<(BigInteger num, const BigFraction& other) {
    return num * other.den() < other.num();
}

bool operator<=(BigInteger num, const BigFraction& other) {
    return num * other.den() <= other.num();
}

bool operator>(BigInteger num, const BigFraction& other) {
    return num * other.den() > other.num();
}

bool operator>=(BigInteger num, const BigFraction& other) {
    return num * other.den() >= other.num();
}

bool BigFraction::isZero() const {
    return num_ == 0;
}
