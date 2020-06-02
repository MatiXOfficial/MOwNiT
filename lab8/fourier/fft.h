#pragma once
#include "ft.h"

class FFT : public FT
{
private:
    double EPS = 1e-9;
    void fillWithZeros();
    
public:
    FFT(const std::vector<std::complex<double>> &data);
    FFT(const std::vector<double> &realData);
    FFT(int N, double min = -1000.0, double max = 1000.0);

    int getDataSize();
    
    std::vector<std::complex<double>> calculate();
};

#include "fft.cpp"