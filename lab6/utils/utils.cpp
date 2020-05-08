#include <climits>
#include "matrix.h"
#include "../methods.cpp"

int findOptimalItersCountJacobi(const Matrix<double> &A, const Matrix<double> &B, const Matrix<double> &Xtrue)
{
    Matrix<double> X(A.getRows(), 1, 0);

    int i = 0;
    while(X != Xtrue)
    {
        X = jacobi(A, B, 1, X);
        i++;
    }
    return i;
}

int findOptimalItersCountGaussSeidel(const Matrix<double> &A, const Matrix<double> &B, const Matrix<double> &Xtrue)
{
    Matrix<double> X(A.getRows(), 1, 0);

    int i = 0;
    while(X != Xtrue)
    {
        X = gaussSeidel(A, B, 1, X);
        i++;
    }
    return i;
}

int findOptimalItersCountSor(const Matrix<double> &A, const Matrix<double> &B, const Matrix<double> &Xtrue, double omega)
{
    Matrix<double> X(A.getRows(), 1, 0);

    int i = 0;
    while(X != Xtrue)
    {
        X = sor(A, B, omega, 1, X);
        i++;
    }
    return i;
}

std::pair<int, double> findOptimalSorConf(const Matrix<double> &A, const Matrix<double> &B, const Matrix<double> &Xtrue)
{
    int iopt = INT_MAX;
    double omegaopt = 1;
    for (double omega = 0.01; omega < 2; omega += 0.01)
    {
        int i = findOptimalItersCountSor(A, B, Xtrue, omega);
        if (i < iopt)
        {
            iopt = i;
            omegaopt = omega;
        }
    }
    return {iopt, omegaopt};
}

double printJacobiErrorsJSON(std::ofstream &out, Matrix<double> &A, const Matrix<double> &B, const Matrix<double> &Xtrue, int maxit, bool isLast = false)
{
    Matrix<double> X(A.getRows(), 1, 0);
    double error;

    out << "[";
    for (int it = 1; it <= maxit; it++)
    {
        X = jacobi(A, B, 1, X);
        error = 0;
        for (int i = 0; i < Xtrue.getRows(); i++)
        {
            error += std::abs(Xtrue(i) - X(i));
        }
        out << "[" << it << "," << error << "]";

        if (it < maxit)
        {
            out << ",";
        }
        else
        {
            out << "]";
            if (!isLast)
                out << ",";
            out << std::endl;
        }
    }
}

double printGaussSeidelErrorsJSON(std::ofstream &out, Matrix<double> &A, const Matrix<double> &B, const Matrix<double> &Xtrue, int maxit, bool isLast = false)
{
    Matrix<double> X(A.getRows(), 1, 0);
    double error;

    out << "[";
    for (int it = 1; it <= maxit; it++)
    {
        X = gaussSeidel(A, B, 1, X);
        error = 0;
        for (int i = 0; i < Xtrue.getRows(); i++)
        {
            error += std::abs(Xtrue(i) - X(i));
        }
        out << "[" << it << "," << error << "]";

        if (it < maxit)
        {
            out << ",";
        }
        else
        {
            out << "]";
            if (!isLast)
                out << ",";
            out << std::endl;
        }
    }
}

double printSORErrorsJSON(std::ofstream &out, Matrix<double> &A, const Matrix<double> &B, const Matrix<double> &Xtrue, double omega, int maxit, bool isLast = false)
{
    Matrix<double> X(A.getRows(), 1, 0);
    double error;

    out << "[";
    for (int it = 1; it <= maxit; it++)
    {
        X = sor(A, B, omega, 1, X);
        error = 0;
        for (int i = 0; i < Xtrue.getRows(); i++)
        {
            error += std::abs(Xtrue(i) - X(i));
        }
        out << "[" << it << "," << error << "]";

        if (it < maxit)
        {
            out << ",";
        }
        else
        {
            out << "]";
            if (!isLast)
                out << ",";
            out << std::endl;
        }
    }
}