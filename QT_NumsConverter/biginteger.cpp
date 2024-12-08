#include "biginteger.h"

// Создает длинное целое число со значением 0
BigInteger::BigInteger() {
    this->_is_negative = false;
}

// Создает длинное целое число из C++-строки
BigInteger::BigInteger(QString str) {
    if (str.length() == 0) {
        this->_is_negative = false;
    } else {
        if (str[0] == '-') {
            str = str.mid(1);
            this->_is_negative = true;
        } else {
            this->_is_negative = false;
        }

        for (long long i = str.length(); i > 0; i -= 9) {
            if (i < 9)
                this->_digits.push_back(str.mid(0, i).toLongLong());
            else
                this->_digits.push_back(str.mid(i - 9, 9).toLongLong());
        }

        this->_remove_leading_zeros();
    }
}

// Удаляет ведущие нули
void BigInteger::_remove_leading_zeros() {
    while (this->_digits.size() > 1 && this->_digits.back() == 0) {
        this->_digits.pop_back();
    }

    if (this->_digits.size() == 1 && this->_digits[0] == 0) this->_is_negative = false;
}

// Печатает число в поток вывода
std::ostream& operator <<(std::ostream& os, const BigInteger& bi) {
    if (bi._digits.empty()) os << 0;
    else {
        if (bi._is_negative) os << '-';
        os << bi._digits.back();
        char old_fill = os.fill('0');
        for (long long i = static_cast<long long>(bi._digits.size()) - 2; i >= 0; --i)
            os << bi._digits[i];
        os.fill(old_fill);
    }
    return os;
}

// Сравнивает два числа на равенство
bool operator==(const BigInteger& left, const BigInteger& right) {
    if (left._is_negative != right._is_negative) return false;
    if (left._digits.empty()) {
        if (right._digits.empty() || (right._digits.size() == 1 && right._digits[0] == 0)) return true;
        else return false;
    }

    if (right._digits.empty()) {
        if (left._digits.size() == 1 && left._digits[0] == 0) return true;
        else return false;
    }

    if (left._digits.size() != right._digits.size()) return false;
    for (size_t i = 0; i < left._digits.size(); ++i) if (left._digits[i] != right._digits[i]) return false;

    return true;
}

// Возвращает копию переданного числа
const BigInteger BigInteger::operator+() const {
    return BigInteger(*this);
}

// Возвращает переданное число с другим знаком
const BigInteger BigInteger::operator-() const {
    BigInteger copy(*this);
    copy._is_negative = !copy._is_negative;
    return copy;
}

// Проверяет, является ли левый операнд меньше правого
bool operator<(const BigInteger& left, const BigInteger& right) {
    if (left == right) return false;
    if (left._is_negative) {
        if (right._is_negative) return ((-right) < (-left));
        else return true;
    }
    else if (right._is_negative) return false;
    else {
        if (left._digits.size() != right._digits.size()) {
            return left._digits.size() < right._digits.size();
        } else {
            for (long long i = left._digits.size() - 1; i >= 0; --i) {
                if (left._digits[i] != right._digits[i]) return left._digits[i] < right._digits[i];
            }

            return false;
        }
    }
}

// Сравнивает два числа на неравенство
bool operator!=(const BigInteger& left, const BigInteger& right) {
    return !(left == right);
}

// Проверяет, является ли левый операнд меньше либо равен правого
bool operator<=(const BigInteger& left, const BigInteger& right) {
    return (left < right || left == right);
}

// Проверяет, является ли левый операнд больше правого
bool operator>(const BigInteger& left, const BigInteger& right) {
    return !(left <= right);
}

// Проверяет, является ли левый операнд больше либо равен правого
bool operator>= (const BigInteger& left, const BigInteger& right) {
    return !(left < right);
}

// Складывает два числа
const BigInteger operator+(BigInteger left, const BigInteger& right) {
    if (left._is_negative) {
        if (right._is_negative) return -(-left + (-right));
        else return right - (-left);
    } else if (right._is_negative) return left - (-right);
    long long carry = 0;
    for (size_t i = 0; i < std::max(left._digits.size(), right._digits.size()) || carry != 0; ++i) {
        if (i == left._digits.size()) left._digits.push_back(0);
        left._digits[i] += carry + (i < right._digits.size() ? right._digits[i] : 0);
        carry = left._digits[i] >= BigInteger::BASE;
        if (carry != 0) left._digits[i] -= BigInteger::BASE;
    }

    return left;
}

// Прибавляет к текущему числу новое
BigInteger& BigInteger::operator+=(const BigInteger& value) {
    return *this = (*this + value);
}

// Префиксный инкремент
const BigInteger BigInteger::operator++() {
    return (*this += 1);
}

// Преобразует число к строке
QString BigInteger::toQString() const {
    QString result;
    if (_is_negative) result += '-';

    if (_digits.empty()) {
        result += "0";
    } else {
        result += QString::number(_digits.back());
        for (int i = _digits.size() - 2; i >= 0; --i) {
            result += QString::number(_digits[i], 10).rightJustified(9, '0'); // Добавление ведущих нулей
        }
    }
    return result;
}

int BigInteger::toInt() const {
    // Обработка случая, когда число слишком большое для `int`
    if (_digits.empty() || (_digits.size() == 1 && _digits[0] == 0)) {
        return 0; // Ноль
    }

    // Проверяем положительное или отрицательное число
    if (_is_negative) {
        if (_digits.size() > 1 || _digits[0] > static_cast<unsigned>(std::numeric_limits<int>::max()) + 1) {
            throw std::overflow_error("Negative BigInteger is too large to fit in an int.");
        }
        return -static_cast<int>(_digits[0]); // Отрицательное число
    } else {
        if (_digits.size() > 1 || _digits[0] > static_cast<unsigned>(std::numeric_limits<int>::max())) {
            throw std::overflow_error("BigInteger is too large to fit in an int.");
        }
        return static_cast<int>(_digits[0]); // Положительное число
    }
}

// Преобразует signed char к BigInteger
BigInteger::BigInteger(signed char c) {
    if (c < 0) this->_is_negative = true;
    else this->_is_negative = false;
    this->_digits.push_back(std::abs(c));
}

// Преобразует unsigned char к BigInteger
BigInteger::BigInteger(unsigned char c) {
    this->_is_negative = false;
    this->_digits.push_back(c);
}

// Преобразует signed short к BigInteger
BigInteger::BigInteger(signed short s) {
    if (s < 0) this->_is_negative = true;
    else this->_is_negative = false;
    this->_digits.push_back(std::abs(s));
}

// Преобразует unsigned short к BigInteger
BigInteger::BigInteger(unsigned short s) {
    this->_is_negative = false;
    this->_digits.push_back(s);
}

// Преобразует signed int к BigInteger
BigInteger::BigInteger(signed int i) {
    if (i < 0) this->_is_negative = true;
    else this->_is_negative = false;
    this->_digits.push_back(std::abs(i) % BigInteger::BASE);
    i /= BigInteger::BASE;
    if (i != 0) this->_digits.push_back(std::abs(i));
}

// Преобразует unsigned int к BigInteger
BigInteger::BigInteger(unsigned int i) {
    this->_digits.push_back(i % BigInteger::BASE);
    i /= BigInteger::BASE;
    if (i != 0) this->_digits.push_back(i);
}

// Преобразует signed long к BigInteger
BigInteger::BigInteger(signed long l) {
    if (l < 0) this->_is_negative = true;
    else this->_is_negative = false;
    this->_digits.push_back(std::abs(l) % BigInteger::BASE);
    l /= BigInteger::BASE;
    if (l != 0) this->_digits.push_back(std::abs(l));
}

// Преобразует unsigned long к BigInteger
BigInteger::BigInteger(unsigned long l) {
    this->_digits.push_back(l % BigInteger::BASE);
    l /= BigInteger::BASE;
    if (l != 0) this->_digits.push_back(l);
}

// Преобразует signed long long к BigInteger
BigInteger::BigInteger(signed long long l) {
    if (l < 0) { this->_is_negative = true; l = -l; }
    else this->_is_negative = false;
    do {
        this->_digits.push_back(l % BigInteger::BASE);
        l /= BigInteger::BASE;
    } while (l != 0);
}

// Преобразует unsigned long long к BigInteger
BigInteger::BigInteger(unsigned long long l) {
    this->_is_negative = false;
    do {
        this->_digits.push_back(l % BigInteger::BASE);
        l /= BigInteger::BASE;
    } while (l != 0);
}

// Постфиксный инкремент
const BigInteger BigInteger::operator++(int) {
    *this += 1;
    return *this - 1;
}

// Префиксный декремент
const BigInteger BigInteger::operator--() {
    return *this -= 1;
}

// Постфиксный декремент
const BigInteger BigInteger::operator--(int) {
    *this -= 1;
    return *this + 1;
}

// Вычитает два числа
const BigInteger operator-(BigInteger left, const BigInteger& right) {
    if (right._is_negative) return left + (-right);
    else if (left._is_negative) return -(-left + right);
    else if (left < right) return -(right - left);
    long long carry = 0;
    for (size_t i = 0; i < right._digits.size() || carry != 0; ++i) {
        left._digits[i] -= carry + (i < right._digits.size() ? right._digits[i] : 0);
        carry = left._digits[i] < 0;
        if (carry != 0) left._digits[i] += BigInteger::BASE;
    }

    left._remove_leading_zeros();
    return left;
}

// Вычитает из текущего числа новое
BigInteger& BigInteger::operator-=(const BigInteger& value) {
    return *this = (*this - value);
}

// Перемножает два числа
const BigInteger operator*(const BigInteger& left, const BigInteger& right) {

    std::vector<long long> a = left._digits, b = right._digits;
    size_t n = 1;
    while (n < a.size() + b.size()) {
        n <<= 1;
    }

    ComplexArray fa(n), fb(n);

    for (size_t i = 0; i < a.size(); ++i)
        fa[i] = Complex(a[i], 0);
    for (size_t i = 0; i < b.size(); ++i)
        fb[i] = Complex(b[i], 0);

    FFT::fft(fa, false);
    FFT::fft(fb, false);

    for (size_t i = 0; i < n; ++i) {
        fa[i] *= fb[i];
    }

    FFT::fft(fa, true);

    std::vector<long long> result(n);
    long long carry = 0;
    for (size_t i = 0; i < n; ++i) {
        long long val = static_cast<long long>(std::round(fa[i].real()));
        result[i] = (val + carry) % BigInteger::BASE;
        carry = (val + carry) / BigInteger::BASE;
    }

    while (!result.empty() && result.back() == 0)
        result.pop_back();

    BigInteger res;
    res._digits = result;
    res._is_negative = left._is_negative != right._is_negative;
    return res;
}

// Домножает текущее число на указанное
BigInteger& BigInteger::operator*=(const BigInteger& value) {
    return *this = (*this * value);
}

// Сдвигает все разряды на 1 вправо (домножает на BASE)
void BigInteger::_shift_right() {
    if (this->_digits.size() == 0) {
        this->_digits.push_back(0);
        return;
    }
    this->_digits.push_back(this->_digits[this->_digits.size() - 1]);
    for (size_t i = this->_digits.size() - 2; i > 0; --i) this->_digits[i] = this->_digits[i - 1];
    this->_digits[0] = 0;
}

// Делит два числа
const BigInteger operator/(const BigInteger& left, const BigInteger& right) {
    if (right == 0) throw BigInteger::divide_by_zero();
    BigInteger b = right;
    b._is_negative = false;
    BigInteger result, current;
    result._digits.resize(left._digits.size());
    for (long long i = static_cast<long long>(left._digits.size()) - 1; i >= 0; --i) {
        current._shift_right();
        current._digits[0] = left._digits[i];
        current._remove_leading_zeros();
        long long x = 0, l = 0, r = BigInteger::BASE;
        while (l <= r) {
            long long m = (l + r) / 2;
            BigInteger t = b * m;
            if (t <= current) {
                x = m;
                l = m + 1;
            } else r = m - 1;
        }

        result._digits[i] = x;
        current = current - b * x;
    }

    result._is_negative = left._is_negative != right._is_negative;
    result._remove_leading_zeros();
    return result;
}

// Делит текущее число на указанное
BigInteger& BigInteger::operator/=(const BigInteger& value) {
    return *this = (*this / value);
}

// Возвращает остаток от деления двух чисел
const BigInteger operator%(const BigInteger& left, const BigInteger& right) {
    BigInteger result = left - (left / right) * right;
    if (result._is_negative) result += right;
    return result;
}

// Присваивает текущему числу остаток от деления на другое число
BigInteger& BigInteger::operator%=(const BigInteger& value) {
    return *this = (*this % value);
}

// Проверяет, является ли текущее число нечетным
bool BigInteger::odd() const {
    if (this->_digits.size() == 0) return false;
    return this->_digits[0] & 1;
}

// Проверяет, является ли текущее число четным
bool BigInteger::even() const {
    return !this->odd();
}

// Возводит текущее число в указанную степень
const BigInteger BigInteger::pow(BigInteger n) const {
    BigInteger a(*this), result(1);
    while (n != 0) {
        if (n.odd()) result *= a;
        a *= a;
        n /= 2;
    }

    return result;
}
