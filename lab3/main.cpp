#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <climits>

constexpr double start1 = 3.0/2 * M_PI , end1 = 2 * M_PI;
inline double f1(double x)
{
    return cos(x) * cosh(x) - 1;
}

// constexpr double start2 = 0, end2 = M_PI / 2;    // Wrong for tangent
constexpr double start2 = 0 + 1e-6, end2 = M_PI / 2 - 1e-6;
inline double f2(double x)
{
    return 1/x - tan(x);
}

constexpr double start3 = 1, end3 = 3;
inline double f3(double x)
{
    return pow(2, -x) + exp(x) + 2 * cos(x) - 6;
}

constexpr double h = 1e-7;
std::vector<double> epsilons = {1e-7, 1e-15, 1e-33};
std::vector< double (*)(double) > funs = {f1, f2, f3};
std::vector< std::pair<double, double> > intervals = 
    {std::make_pair(start1, end1), std::make_pair(start2, end2), std::make_pair(start3, end3)};
    
void writeResults(std::ofstream&, std::string, std::pair<double, int> (double (double), double, double, double, int), int = INT_MAX);
inline bool oppositeSigns(double x, double y)
{
    return (x > 0 && y < 0) || (x < 0 && y > 0);
}

std::pair<double, int> solveBisection(double f(double), double a, double b, double eps, int nmax = INT_MAX);
std::pair<double, int> solveNewton(double f(double), double a, double b, double eps, int nmax = INT_MAX);
std::pair<double, int> solveSecant(double f(double), double a, double b, double eps, int nmax = INT_MAX);

int main()
{
    std::ofstream file;
    file.open("results.txt", std::ios::trunc);

    writeResults(file, "Bisection", solveBisection, 1000);
    writeResults(file, "Newton", solveNewton, 1000);
    writeResults(file, "solveSecant", solveSecant, 1000);

    file.close();
}

/////////////// Definitons /////////////////////////////////////
void writeResults(std::ofstream& file, std::string title, std::pair<double, int> fun(double (double), double, double, double, int), int nmax)
{
    file << title << std::endl;
    for (int i = 0; i < funs.size(); i++)
    {
        auto f = funs[i];
        auto start = intervals[i].first;
        auto end = intervals[i].second;
        file << "fun " << i + 1 << ", start = " << start << ", end = " << end << std::endl;
        for (double eps : epsilons)
        {
            auto result = fun(f, start, end, eps, nmax);
            if (result.first != -1)
            {
                file << std::setprecision(1) << "eps: " << eps << ", result: " << std::setprecision(20) 
                    << result.first << " after " << result.second << " iterations" << std::endl;
            }
            else
            {
                file << "---->eps: " << std::setprecision(1) << eps << ", not finished after " 
                     << result.second << " iterations" << std::endl;
            }
        }
        file << "--------------------------------------" << std::endl;
    }
    file << "=================================================" << std::endl;
}

std::pair<double, int> solveBisection(double f(double), double a, double b, double eps, int nmax)
{
    double fa = f(a), fb = f(b);
    if (!oppositeSigns(fa, fb))
    {
        throw std::invalid_argument("The function values are not of opposite sign!");
    }
    double c, fc;
    int i = 0;
    while (i < nmax)
    {
        c = (a + b) / 2;
        fc = f(c);
        if (fc == 0 || fabs(c - a) <= eps)   // main loop condition
        {
            return {c, i};
        }
        i++;
        if (oppositeSigns(fa, fc))
        {
            b = c;
            fb = fc;
        }
        else
        {
            a = c;
            fa = fc;
        }
    }
    return {-1, i};
}

std::pair<double, int> solveNewton(double f(double), double a, double b, double eps, int nmax)
{
    if (!oppositeSigns(f(a), f(b)))
    {
        throw std::invalid_argument("The function values are not of opposite sign!");
    }
    double x = a, xold, fder;
    int i = 0;
    while(i < nmax) // First condition
    {
        fder = (f(x + h) - f(x - h)) / (2 * h);   // f'(x)
        xold = x;
        x = x - f(x) / fder;
        i++;
        if (fabs(x - xold) <= eps)   // Second condition
        {
            return {x, i};
        }
    }
    return {-1, i};
}

std::pair<double, int> solveSecant(double f(double), double a, double b, double eps, int nmax)
{
    double fa = f(a), fb = f(b);
    if (!oppositeSigns(fa, fb))
    {
        throw std::invalid_argument("The function values are not of opposite sign!");
    }
    double x;
    int i = 0;
    while (i < nmax)    // First condition
    {
        x = (fb * a - fa * b) / (fb - fa);
        if (fabs(x - b) <= eps)     // Second condition
        {
            return {x, i};
        }
        i++;
        a = b;  fa = fb;
        b = x;  fb = f(x);
    }
    return {-1, i};
}