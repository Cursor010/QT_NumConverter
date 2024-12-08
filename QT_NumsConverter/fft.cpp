#include "fft.h"

void FFT::fft(ComplexArray& data, bool invert) {
    size_t n = data.size();
    if (n <= 1) return;

    ComplexArray even(n / 2), odd(n / 2);
    for (size_t i = 0; 2 * i < n; ++i) {
        even[i] = data[2 * i];
        odd[i] = data[2 * i + 1];
    }

    fft(even, invert);
    fft(odd, invert);

    double angle = 2 * M_PI / n * (invert ? -1 : 1);
    Complex w(1), wn(std::cos(angle), std::sin(angle));
    for (size_t i = 0; 2 * i < n; ++i) {
        data[i] = even[i] + w * odd[i];
        data[i + n / 2] = even[i] - w * odd[i];
        if (invert) {
            data[i] /= 2;
            data[i + n / 2] /= 2;
        }
        w *= wn;
    }
}
