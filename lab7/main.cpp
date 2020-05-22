#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <string>
#include <iomanip>

#include "integrals.h"
#include "utils.h"

std::vector< std::function<double(double)> > funs = {[](double x) { return exp(-x*x); },        // f1(x) = e^(-x^2)
                                                     [](double x) { return sqrt(1 + x*x*x); },  // f2(x) = sqrt(1 + x^3)
                                                     [](double x) { return sin(4*x) / x; },     // f3(x) = sin(2x) / x
                                                     [](double x) { return sin(x*x); }};        // f4(x) = sin(x^2)

std::vector< std::pair<double, double> > intervals = {std::make_pair(1, 3),
                                                      std::make_pair(1, 3),
                                                      std::make_pair(1, 3),
                                                      std::make_pair(1, 3)};

std::vector<double> trueValues = {0.139383, 6.229959, -0.253232, 0.463294};

int main()
{
    std::vector<int> N_intervals;
    for (int i = 1; i <= 100; i++)
    {
        N_intervals.push_back(i);
    }

    std::vector<int> N_samples;
    for (int i = 100; i <= 100000; i += 100)
    {
        N_samples.push_back(i);
    }

    std::ofstream file("data/results_data.json", std::ios::trunc);
    file << "{" << std::endl;

    for (int i = 0; i < funs.size(); i++)
    {
        auto f = funs[i];
        auto interval = intervals[i];
        auto trueValue = trueValues[i];
        printFunctionIntegralsJson(i + 1, file, f, interval.first, interval.second, trueValue, N_intervals, N_samples);

        if (i < funs.size() - 1)
            file << "," << std::endl;
        else
            file << std::endl << "}";
    }

    file.close();

    std::cout << "True PI: " << M_PI << std::endl;
    for (int n : {10, 100, 1000, 100000, 1000000, 10000000})
    {
        double calculated_pi = IntegralMonteCarlo().findPi(n);
        std::cout << "Monte Carlo approximation for " << std::setw(8) << n << " samples: " << calculated_pi << std::endl;
    }
}