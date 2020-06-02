#pragma once
#include "ft.h"

class DFT : public FT
{
public:
    DFT(const std::vector<std::complex<double>> &data);
    DFT(const std::vector<double> &realData);
    DFT(int N, double min = -1000.0, double max = 1000.0);
    
    std::vector<std::complex<double>> calculate();
};

#include "dft.cpp"