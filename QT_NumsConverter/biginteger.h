#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include "fft.h"

#include <vector>
#include <string>
#include <ostream>
#include <exception>
#include <QString>
#include <QtMath>

class BigInteger {
public:
    class divide_by_zero : public std::exception {};

    BigInteger();
    BigInteger(QString);
    BigInteger(signed char);
    BigInteger(unsigned char);
    BigInteger(signed short);
    BigInteger(unsigned short);
    BigInteger(signed int);
    BigInteger(unsigned int);
    BigInteger(signed long);
    BigInteger(unsigned long);
    BigInteger(signed long long);
    BigInteger(unsigned long long);

    friend std::ostream& operator<<(std::ostream&, const BigInteger&);
    operator std::string() const;
    const BigInteger operator +() const;
    const BigInteger operator -() const;
    const BigInteger operator ++();
    const BigInteger operator ++(int);
    const BigInteger operator --();
    const BigInteger operator --(int);
    friend bool operator==(const BigInteger&, const BigInteger&);
    friend bool operator<(const BigInteger&, const BigInteger&);
    friend bool operator!=(const BigInteger&, const BigInteger&);
    friend bool operator<=(const BigInteger&, const BigInteger&);
    friend bool operator>(const BigInteger&, const BigInteger&);
    friend bool operator>=(const BigInteger&, const BigInteger&);
    friend const BigInteger operator+(BigInteger, const BigInteger&);
    BigInteger& operator+=(const BigInteger&);
    friend const BigInteger operator-(BigInteger, const BigInteger&);
    BigInteger& operator-=(const BigInteger&);
    friend const BigInteger operator*(const BigInteger&, const BigInteger&);
    BigInteger& operator*=(const BigInteger&);
    friend const BigInteger operator/(const BigInteger&, const BigInteger&);
    BigInteger& operator/=(const BigInteger&);
    friend const BigInteger operator%(const BigInteger&, const BigInteger&);
    BigInteger& operator%=(const BigInteger&);

    bool odd() const;
    bool even() const;
    const BigInteger pow(BigInteger) const;

    int toInt() const;
    QString toQString() const;

private:
    static const long long BASE = 100000;
    std::vector<long long> _digits;
    bool _is_negative;

    void _remove_leading_zeros();
    void _shift_right();

};

#endif // BIGINTEGER_H
