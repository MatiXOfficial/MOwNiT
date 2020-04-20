#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>

#include "utils/point.h"
#include "utils/utils.cpp"

#include "interpolations/lagrange_interpolation.cpp"
#include "interpolations/netwon_interpolation.cpp"
#include "interpolations/hermite_interpolation.cpp"

constexpr double k = 4;
constexpr double m = 0.4;

inline double f(double x)
{
    return sin(k * x / M_PI) * exp(-m * x / M_PI);
}
inline double df(double x)
{
    double trigArg = k * x / M_PI;
    return exp(-m * x / M_PI) / M_PI * (k * cos(trigArg) - m * sin(trigArg));
}
inline double ddf(double x)
{
    double trigArg = k * x / M_PI;
    return exp(-m * x / M_PI) / (M_PI * M_PI) * ((m * m - k * k) * sin(trigArg) - 2 * k * m * cos(trigArg));
}

constexpr int maxCount = 80;
constexpr double rangeStart = -20;
constexpr double rangeEnd = 20;
constexpr double step = 0.01;


int main()
{
    std::ofstream dataFile;
    dataFile.open("plots/interpolation_data.json", std::ios::trunc);
    dataFile << "{" << std::endl;

    std::ofstream errorFile;
    errorFile.open("plots/error_data.json", std::ios::trunc);
    errorFile << "{" << std::endl;

    
    auto truePoints = getPoints(f, rangeStart, rangeEnd, step);
    printPointsJson(dataFile, "interpolated function", truePoints);

    auto pointsX = getVectorFromRange(rangeStart, rangeEnd, step);

    std::vector<double (*)(double)> funs = {f};

    printInterpolationDataJsons(dataFile, errorFile, "lagrange", lagrangeInterpolation, "regular", 
                                funs, truePoints, pointsX, maxCount, rangeStart, rangeEnd);
    printInterpolationDataJsons(dataFile, errorFile, "lagrange", lagrangeInterpolation, "chebyshev", 
                                funs, truePoints, pointsX, maxCount, rangeStart, rangeEnd);

    printInterpolationDataJsons(dataFile, errorFile, "newton", newtonInterpolation, "regular", 
                                funs, truePoints, pointsX, maxCount, rangeStart, rangeEnd);
    printInterpolationDataJsons(dataFile, errorFile, "newton", newtonInterpolation, "chebyshev", 
                                funs, truePoints, pointsX, maxCount, rangeStart, rangeEnd);

    funs.push_back(df);
    printInterpolationDataJsons(dataFile, errorFile, "hermite (one der)", hermiteInterpolation, "regular", 
                                funs, truePoints, pointsX, maxCount, rangeStart, rangeEnd);
    printInterpolationDataJsons(dataFile, errorFile, "hermite (one der)", hermiteInterpolation, "chebyshev", 
                                funs, truePoints, pointsX, maxCount, rangeStart, rangeEnd);

    funs.push_back(ddf);
    printInterpolationDataJsons(dataFile, errorFile, "hermite (two ders)", hermiteInterpolation, "regular", 
                                funs, truePoints, pointsX, maxCount, rangeStart, rangeEnd);
    printInterpolationDataJsons(dataFile, errorFile, "hermite (two ders)", hermiteInterpolation, "chebyshev", 
                                funs, truePoints, pointsX, maxCount, rangeStart, rangeEnd, true);

    dataFile << "}";
    errorFile << "}";
    errorFile.close();
    dataFile.close();
}