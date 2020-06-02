#include "ft.h"
#include <chrono>
#include <random>

FT::FT(const std::vector<std::complex<double>> &data) : data(data)
{
}

FT::FT(const std::vector<double> &realData)
{
    int N = realData.size();
    this->data.resize(N);
    for (int i = 0; i < N; i++)
    {
        data[i] = std::complex<double>(realData[i], 0.0);
    }
}

FT::FT(int N, double min, double max)
{
    std::default_random_engine gen;
    std::uniform_real_distribution<double> uniform(min, max);
    data.resize(N);
    for (int i = 0; i < N; i++)
    {
        data[i] = (uniform(gen), uniform(gen));
    }
}

double FT::timeCalculate()
{
    auto start = std::chrono::steady_clock::now();
    calculate();
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    return duration.count() / 1e6;
}