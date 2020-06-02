#include "fft.h"
#include "dft.h"

void FFT::fillWithZeros()
{
    int N = data.size();
    double l = std::log2(N) - EPS;
    int N_new = std::pow(2, std::ceil(l));
    data.resize(N_new);
}

FFT::FFT(const std::vector<std::complex<double>> &data) : FT(data)
{
    fillWithZeros();
}

FFT::FFT(const std::vector<double> &realData) : FT(realData)
{
    fillWithZeros();
}

FFT::FFT(int N, double min, double max) : FT(N, min, max)
{
    fillWithZeros();
}

int FFT::getDataSize()
{
    return data.size();
}

std::vector<std::complex<double>> FFT::calculate()
{
    int N = data.size();
    if (N <= 4)
    {
        return DFT(data).calculate();
    }

    int N_half = N / 2;
    std::vector<std::complex<double>> evenData(N_half), oddData(N_half);
    int j = 0;
    for (int i = 0; i < N; i += 2)
    {
        evenData[j] = data[i];
        oddData[j] = data[i + 1];
        j++;
    }

    auto X_even = FFT(evenData).calculate();
    auto X_odd = FFT(oddData).calculate();

    std::vector<std::complex<double>> result(N);
    for (int k = 0; k < N_half; k++)
    {
        auto oddFactor = std::polar(1.0, -2.0 * M_PI * k / N) * X_odd[k];
        result[k] = X_even[k] + oddFactor;
        result[k + N_half] = X_even[k] - oddFactor;
    }
    return result;
}