#pragma once
#include <functional>


class Integral
{
protected:
    constexpr static double EPS = 1e-8;
public:
    virtual double calculate(double start, double end, int n, std::function<double(double)> f) = 0;
};


class IntegralRectangular : public Integral
{
public:
    double calculate(double start, double end, int n, std::function<double(double)> f);
};

class IntegralTrapezoidal : public Integral
{
public:
    double calculate(double start, double end, int n, std::function<double(double)> f);
};

class IntegralSimpson : public Integral
{
public:
    double calculate(double start, double end, int n, std::function<double(double)> f);
};

class IntegralMonteCarlo : public Integral
{
public:
    double calculate(double start, double end, int n, std::function<double(double)> f);
    double findPi(int n);
};


#include "integrals.cpp"