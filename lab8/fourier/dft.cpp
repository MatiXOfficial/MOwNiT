#include "dft.h"

DFT::DFT(const std::vector<std::complex<double>> &data) : FT(data)
{
}

DFT::DFT(const std::vector<double> &realData) : FT(realData)
{
}

DFT::DFT(int N, double min, double max) : FT(N, min, max)
{
}

std::vector<std::complex<double>> DFT::calculate()
{
    int N = data.size();
    std::vector<std::complex<double>> result(N);
    for (int k = 0; k < N; k++)
    {
        std::complex<double> sum(0.0, 0.0);
        for (int n = 0; n < N; n++)
        {
            sum += data[n] * std::polar(1.0, -2.0 * M_PI * k * n / N);
        }
        result[k] = sum;
    }
    return result;
}