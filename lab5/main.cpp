#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

#include "utils/point.h"
#include "utils/utils.cpp"

#include "least_squares_approximation.cpp"

constexpr int m1 = 3;
constexpr int m2 = 6;

constexpr double start = -5;
constexpr double end = 5;
constexpr double step = 0.01;

inline double f(double x)
{
    return sin(40 * x / M_PI) * exp(-2 * x / M_PI);
}

inline double g(double x)
{
    return x * x - cos(10 * M_PI * x);
}

int main()
{
    std::ofstream dataFile;
    dataFile.open("data/approximation_data.json", std::ios::trunc);
    dataFile << "{" << std::endl;

    std::ofstream errorFile;
    errorFile.open("data/error_data.json", std::ios::trunc);
    errorFile << "{" << std::endl;

    auto fpoints = getPoints(f, start, end, step);
    printPointsJson(dataFile, "true f", fpoints);
    auto gpoints = getPoints(g, start, end, step);
    printPointsJson(dataFile, "true g", gpoints);

    auto pointsX = getVectorFromRange(start, end, step);

    std::vector<int> N = getVectorFromRange(6, 100, 1);
    printLinearApproximationJson(dataFile, errorFile, "f", f, N, m1, start, end, pointsX, fpoints);
    printLinearApproximationJson(dataFile, errorFile, "f", f, N, m2, start, end, pointsX, fpoints);

    printLinearApproximationJson(dataFile, errorFile, "g", g, N, m1, start, end, pointsX, gpoints);
    printLinearApproximationJson(dataFile, errorFile, "g", g, N, m2, start, end, pointsX, gpoints);

    std::vector< std::pair<int, std::vector<int>> > NM = {std::make_pair(3, getVectorFromRange(10, 500, 1)),
                                                          std::make_pair(10, getVectorFromRange(21, 500, 1)),
                                                          std::make_pair(50, getVectorFromRange(101, 500, 1)),
                                                          std::make_pair(100, getVectorFromRange(201, 500, 1))};
    printTrygonometricApproximationJson(dataFile, errorFile, "f", f, NM, start, end, pointsX, fpoints);
    printTrygonometricApproximationJson(dataFile, errorFile, "g", g, NM, start, end, pointsX, gpoints, true);
    
    errorFile << "}";
    errorFile.close();

    dataFile << "}";
    dataFile.close();
}