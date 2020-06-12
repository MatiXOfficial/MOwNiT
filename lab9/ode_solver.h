#pragma once
#include <vector>

template<typename T>
class ODESolver
{
    T (*odeFun)(T vars, double t);

public:
    ODESolver(T odeFun(T vars, double t));

    std::vector<T> euler(double h = 0.001, int n = 50'000, T vars = T(), double t0 = 0.0);
    std::vector<T> backwardEuler(double h = 0.001, int n = 50'000, T vars = T(), double t0 = 0.0, int itNum = 100);

    std::vector<T> rungeKuttaSecondOrder(double h = 0.001, int n = 50'000, T vars = T(), double t0 = 0.0);
    std::vector<T> rungeKuttaFourthOrder(double h = 0.001, int n = 50'000, T vars = T(), double t0 = 0.0);
};

#include "ode_solver.cpp"