#pragma once

#define _USE_MATH_DEFINES

#include <vector>
#include <functional>

#include "utils/gauss.cpp"
#include "utils/point.h"

//////////////////// Algebraic ////////////////////////
std::vector<double> algebraicLeastSquares(std::vector<Point> points, int m)
{
    m++;
    int n = points.size();

    std::vector< std::vector<double> > G(m, std::vector<double>(m));
    for (int k = 0; k < m; k++)
    {
        for (int j = 0; j < m; j++)
        {
            for (int i = 0; i < n; i++)
            {
                G[k][j] += std::pow(points[i].getX(), j + k);
            }
        }
    }

    std::vector<double> B(m);
    for (int k = 0; k < m; k++)
    {
        for (int i = 0; i < n; i++)
        {
            B[k] += points[i].getY() * std::pow(points[i].getX(), k);
        }
    }

    return(gaussSolve(G, B));
}

//////////////////// Trygonometric ///////////////////////
std::pair<std::vector<double>, std::vector<double>> trygonometricLeastSquares(std::vector<Point> points, int m)
{
    m++;
    int n = points.size();
    double L = n / 2.0;
    std::vector<double> A(m, 0);
    std::vector<double> B(m, 0);

    for (int k = 0; k < m; k++)
    {
        for (int i = 0; i < n; i++)
        {
            A[k] += points[i].getY() * cos(k * M_PI * i / L);
            B[k] += points[i].getY() * sin(k * M_PI * i / L);
        }
        A[k] /= L;
        B[k] /= L;
    }

    return std::make_pair(A, B);
}