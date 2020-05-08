#pragma once

#include "utils/matrix.h"


template<typename T>
Matrix<double> jacobi(const Matrix<T> &A, const Matrix<T> &B, int iters, const Matrix<double> &init)
{
    if (!A.isDiagonallyDominant())
        throw std::invalid_argument("matrix is not diagonally dominant");

    int n = A.getRows();
    
    Matrix<double> X = init;
    Matrix<double> Xprev;

    for (int it = 1; it <= iters; it++)
    {
        Xprev = X;
        for (int i = 0; i < n; i++)
        {
            double sum = 0;
            for (int j = 0; j < n; j++)
            {
                if (j == i)
                    continue;
                sum += A(i, j) * Xprev(j);
            }
            X(i) = (B(i) - sum) / A(i, i);
        }
    }

    return X;
}

template<typename T>
Matrix<double> jacobi(const Matrix<T> &A, const Matrix<T> &B, int iters, double init = 0)
{
    Matrix<double> X(A.getRows(), 1, init);
    return jacobi(A, B, iters, X);
}


template<typename T>
Matrix<double> gaussSeidel(const Matrix<T> &A, const Matrix<T> &B, int iters, const Matrix<double> &init)
{
    if (!A.isDiagonallyDominant())
        throw std::invalid_argument("matrix is not diagonally dominant");

    int n = A.getRows();
    
    Matrix<double> X = init;

    for (int it = 0; it < iters; it++)
    {
        for (int i = 0; i < n; i++)
        {
            double sum = 0;
            for (int j = 0; j < n; j++)
            {
                if (i == j)
                    continue;
                sum += A(i, j) * X(j, 0);
            }
            X(i) = (B(i) - sum) / A(i, i);
        }
    }
    return X;
}

template<typename T>
Matrix<double> gaussSeidel(const Matrix<T> &A, const Matrix<T> &B, int iters, double init = 0)
{
    Matrix<double> X(A.getRows(), 1, init);
    return gaussSeidel(A, B, iters, X);
}


template<typename T>
Matrix<double> sor(const Matrix<T> &A, const Matrix<T> &B, double omega, int iters, const Matrix<double> &init)
{
    if (!A.isDiagonallyDominant())
        throw std::invalid_argument("matrix is not diagonally dominant");

    int n = A.getRows();
    
    Matrix<double> X = init;
    
    for (int it = 0; it < iters; it++)
    {
        for (int i = 0; i < n; i++)
        {
            double sum = 0;
            for (int j = 0; j < n; j++)
            {
                if (i == j)
                    continue;
                sum += A(i, j) * X(j, 0);
            }
            X(i) = (1 - omega) * X(i) + omega * (B(i) - sum) / A(i, i);
        }
    }
    return X;
}

template<typename T>
Matrix<double> sor(const Matrix<T> &A, const Matrix<T> &B, double omega, int iters, double init = 0)
{
    Matrix<double> X(A.getRows(), 1, init);
    return sor(A, B, omega, iters, X);
}