#include "integrals.h"
#include <random>

double IntegralRectangular::calculate(double start, double end, int n, std::function<double(double)> f)
{
    double width = (end - start) / n;
    double result = 0;
    for (double x = start + width / 2; x < end - EPS; x += width)
    {
        result += f(x);
    }
    result *= width;
    return result;
}

double IntegralTrapezoidal::calculate(double start, double end, int n, std::function<double(double)> f)
{
    double width = (end - start) / n;
    double result = (f(start) + f(end)) / 2.0;
    double x = start + width;
    while (x < end - EPS)
    {
        result += f(x);
        x += width;
    }
    result *= width;
    return result;
}

double IntegralSimpson::calculate(double start, double end, int n, std::function<double(double)> f)
{
    double width = (end - start) / n;
    double result = f(start) + f(end);
    double t = start + width / 2;
    double y = start + width;
    while(y < end - EPS)
    {
        result += 4 * f(t) + 2 * f(y);
        t += width;
        y += width;
    }
    result += 4 * f(t);
    result /= 6;
    result *= width;
    return result;
}

double IntegralMonteCarlo::calculate(double start, double end, int n, std::function<double(double)> f)
{
    double result = 0;
    std::default_random_engine gen;
    std::uniform_real_distribution<double> distr(start, end);
    for (int i = 0; i < n; i++)
    {
        result += f(distr(gen));
    }
    result *= (end - start);
    result /= n;
    return result;
}

double IntegralMonteCarlo::findPi(int n)
{
    std::default_random_engine gen;
    std::uniform_real_distribution<double> distr(0, 1);
    int n_in = 0;
    for (int i = 0; i < n; i++)
    {
        double x = distr(gen);
        double y = distr(gen);
        double dist = sqrt(x*x + y*y);
        if (dist <= 1)
        {
            n_in++;
        }
    }
    return 4.0 * n_in / n;
}