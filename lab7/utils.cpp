#include "utils.h"
#include "integrals.h"
#include <math.h>
#include <iomanip>

void printIntegralJson(std::ofstream &file, std::string title, std::string x_title, 
                       Integral &&integral, std::function<double(double)> f,
                       double start, double end, double trueValue, const std::vector<int> &N)
{
    file << "{\"title\" : \"" << title << "\", \"x_title\" : \"" << x_title << "\", \"errors\" : [";
    for (int i = 0; i < N.size(); i++)
    {
        int n = N[i];
        double approx = integral.calculate(start, end, n, f);
        double err = std::abs(trueValue - approx);
        file << "[" << n << ", " << std::setprecision(6) << err << "]";

        if (i < N.size() - 1)
            file << ", ";
        else
            file << "]}";
    }
}

void printFunctionIntegralsJson(int f_idx, std::ofstream &file, std::function<double(double)> f,
                                double start, double end, double trueValue, 
                                const std::vector<int> &N_intervals, const std::vector<int> &N_samples)
{
    file << "\"f" << std::setprecision(2) << f_idx << " (" << start << ", " << end << ") errors\" : [";
    printIntegralJson(file, "rectangular", "number of intervals", IntegralRectangular(), 
                      f, start, end, trueValue, N_intervals);
    file << ", ";
    printIntegralJson(file, "trapezoidal", "number of intervals", IntegralTrapezoidal(), 
                      f, start, end, trueValue, N_intervals);
    file << ", ";
    printIntegralJson(file, "simpson", "number of intervals", IntegralSimpson(), 
                      f, start, end, trueValue, N_intervals);
    file << ", ";
    printIntegralJson(file, "monte carlo", "number of samples", IntegralMonteCarlo(), 
                      f, start, end, trueValue, N_samples);
    file << " ]";
}