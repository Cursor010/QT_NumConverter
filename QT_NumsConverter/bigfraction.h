#ifndef BIGFRACTION_H
#define BIGFRACTION_H

#include "biginteger.h"

#include <QString>
#include <QTextStream>
#include <QDebug>

class BigFraction {
public:
    BigFraction();
    BigFraction(BigInteger num, BigInteger den = 1);
    BigFraction(const BigFraction& other);
    ~BigFraction() = default;

    BigInteger num() const;
    BigInteger den() const;

    BigFraction& operator=(const BigFraction& other);
    BigFraction& operator+();
    BigFraction operator-() const;

    BigFraction& operator++();
    BigFraction operator++(int);
    BigFraction& operator--();
    BigFraction operator--(int);

    BigFraction& operator+=(const BigFraction& other);
    BigFraction& operator-=(const BigFraction& other);
    BigFraction& operator*=(const BigFraction& other);
    BigFraction& operator/=(const BigFraction& other);

    BigFraction operator+(const BigFraction& other) const;
    BigFraction operator-(const BigFraction& other) const;
    BigFraction operator*(const BigFraction& other) const;
    BigFraction operator/(const BigFraction& other) const;

    BigFraction operator+(BigInteger other) const;
    BigFraction operator-(BigInteger other) const;
    BigFraction operator*(BigInteger other) const;
    BigFraction operator/(BigInteger other) const;

    bool operator==(const BigFraction& other) const;
    bool operator!=(const BigFraction& other) const;
    bool operator<(const BigFraction& other) const;
    bool operator<=(const BigFraction& other) const;
    bool operator>(const BigFraction& other) const;
    bool operator>=(const BigFraction& other) const;

    friend QTextStream& operator<<(QTextStream&, const BigFraction&);
    friend BigFraction operator*(BigInteger num, const BigFraction& other);
    friend BigFraction operator/(BigInteger num, const BigFraction& other);
    friend BigFraction operator+(BigInteger num, const BigFraction& other);
    friend BigFraction operator-(BigInteger num, const BigFraction& other);
    bool isZero() const;

private:
    BigInteger num_, den_;

    void normalize();
    BigInteger gcd(BigInteger first_number, BigInteger second_number);
};

Q_DECLARE_METATYPE(BigFraction)

#endif // BIGFRACTION_H
