#ifndef FFT_H
#define FFT_H

#include <complex>
#include <vector>
#include <QtMath>

using Complex = std::complex<double>;
using ComplexArray = std::vector<Complex>;

class FFT {
public:
    static void fft(ComplexArray& data, bool invert);
};

#endif // FFT_H
