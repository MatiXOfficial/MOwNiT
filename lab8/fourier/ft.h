#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <complex>
#include <vector>

class FT
{
protected:
    std::vector<std::complex<double>> data;

public:
    FT(const std::vector<std::complex<double>> &data);
    FT(const std::vector<double> &realData);
    FT(int N, double min, double max);
    
    virtual std::vector<std::complex<double>> calculate() = 0;

    double timeCalculate();
};


#include "ft.cpp"