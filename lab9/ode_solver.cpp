#include "ode_solver.h"

template<typename T>
ODESolver<T>::ODESolver(T odeFun(T vars, double t))
{
    this->odeFun = odeFun;
}

template<typename T>
std::vector<T> ODESolver<T>::euler(double h, int n, T vars, double t0)
{
    std::vector<T> result(n + 1);
    result[0] = vars;
    double t = t0;

    for (int i = 1; i <= n; i++)
    {
        result[i] = result[i - 1] + h * odeFun(result[i - 1], t);
        t += h;
    }
    return result;
}

template<typename T>
std::vector<T> ODESolver<T>::backwardEuler(double h, int n, T vars, double t0, int itNum)
{
    std::vector<T> result(n + 1);
    result[0] = vars;
    double t = t0;

    for (int i = 1; i <= n; i++)
    {
        t += h;
        result[i] = result[i - 1];
        for (int j = 0; j < itNum; j++)
        {
            result[i] = result[i - 1] + h * odeFun(result[i], t);
        }
    }
    return result;
}

template<typename T>
std::vector<T> ODESolver<T>::rungeKuttaSecondOrder(double h, int n, T vars, double t0)
{
    std::vector<T> result(n + 1);
    result[0] = vars;
    double t = t0;

    for (int i = 1; i <= n; i++)
    {
        result[i] = result[i - 1] + h * odeFun(result[i - 1] + h / 2.0 * odeFun(result[i - 1], t), t + h / 2.0);
        t += h;
    }
    return result;
}

template<typename T>
std::vector<T> ODESolver<T>::rungeKuttaFourthOrder(double h, int n, T vars, double t0)
{
    std::vector<T> result(n + 1);
    result[0] = vars;
    double t = t0;

    for (int i = 1; i <= n; i++)
    {
        auto k1 = odeFun(result[i - 1], t);
        auto k2 = odeFun(result[i - 1] + h / 2.0 * k1, t + h / 3.0);
        auto k3 = odeFun(result[i - 1] + h / 2.0 * k2, t + 2 * h / 3.0);
        auto k4 = odeFun(result[i - 1] + h * k3, t + h);
        result[i] = result[i - 1] + h / 6.0 * (k1 + 2 * k2 + 2 * k3 + k4);
        t += h;
    }
    return result;
}