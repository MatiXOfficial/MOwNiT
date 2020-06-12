#include <iostream>
#include <cmath>
#include "utils.h"
#include "ode_solver.h"

constexpr double sigma = 10.0;
constexpr double beta = 8.0 / 3.0;
constexpr double ro = 28.0;
Triple lorenzFuns(Triple vars, double t);

constexpr double x0 = 0.0;
constexpr double xk = 40.0;
constexpr double m = 1.0;
constexpr double k = 2.0;
double task4Fun(double x, double t);
double task4ExactFun(double x);


int main()
{
    auto file = std::ofstream("data/results.json");
    
    /***********************
     *** Zadanie 2 ********* 
    ************************/
    file << "{" << std::endl
         << "\"lorenz\" : " << std::endl
         << "{" << std::endl;

    ODESolver<Triple> lorenz(lorenzFuns);

    auto result = lorenz.euler(0.001, 50'000, Triple(0.0, 2.0, 20.0));
    printTriplesVectorToJSON(file, result, "euler, h=0.001");
    file << "," << std::endl;

    result = lorenz.backwardEuler(0.001, 50'000, Triple(0.0, 2.0, 20.0));
    printTriplesVectorToJSON(file, result, "backward euler, h=0.001");
    file << "," << std::endl;

    result = lorenz.rungeKuttaSecondOrder(0.001, 50'000, Triple(0.0, 2.0, 20.0));
    printTriplesVectorToJSON(file, result, "RK 2nd order, h=0.001");
    file << "," << std::endl;

    result = lorenz.rungeKuttaFourthOrder(0.001, 50'000, Triple(0.0, 2.0, 20.0));
    printTriplesVectorToJSON(file, result, "RK 4th order, h=0.001");

    file << std::endl << "}," << std::endl;

    /***********************
     *** Zadanie 4 ********* 
    ************************/
    file << "\"task 4\" : " << std::endl
         << "{" << std::endl;

    ODESolver<double> task4solver(task4Fun);
    double a = task4ExactFun(x0);

    std::vector<int> N = {100, 500, 1000, 10000};
    for (int i = 0; i < N.size(); i++)
    {
        int n = N[i];
        double h = (xk - x0) / n;

        auto t4res = task4solver.euler(h, n, a, x0);
        printTask4ResultToJSON(file, t4res, x0, h, "euler, n=" + std::to_string(n));
        file << "," << std::endl;

        t4res = task4solver.backwardEuler(h, n, a, x0);
        printTask4ResultToJSON(file, t4res, x0, h, "backward euler, n=" + std::to_string(n));
        file << "," << std::endl;

        t4res = task4solver.rungeKuttaSecondOrder(h, n, a, x0);
        printTask4ResultToJSON(file, t4res, x0, h, "RK 2nd order, n=" + std::to_string(n));
        file << "," << std::endl;

        t4res = task4solver.rungeKuttaFourthOrder(h, n, a, x0);
        printTask4ResultToJSON(file, t4res, x0, h, "RK 4th order, n=" + std::to_string(n));
        file << "," << std::endl;

        double x = x0;
        for (int i = 0; i < t4res.size(); i++)
        {
            t4res[i] = task4ExactFun(x);
            x += h;
        }
        printTask4ResultToJSON(file, t4res, x0, h, "exact solution, n=" + std::to_string(n));

        if (i < N.size() - 1)
        {
            file << "," << std::endl;
        }
    }

    
    file << std::endl << "}" << std::endl;

    file << std::endl << "}";
}


///////////// Definitions //////////////////
Triple lorenzFuns(Triple vars, double t)
{
    double x = vars.getX();
    double y = vars.getY();
    double z = vars.getZ();

    double f_x = sigma * (y - x);
    double f_y = x * (ro - z) - y;
    double f_z = x * y - beta * z;

    return Triple(f_x, f_y, f_z);
}

double task4Fun(double y, double x)
{
    return k * m * y * std::sin(m * x) + 
           k * k * m * std::sin(m * x) * std::cos(m * x);
}

double task4ExactFun(double x)
{
    return std::exp(-k * std::cos(m * x)) - k * std::cos(m * x) + 1;
}