#pragma once

#define _USE_MATH_DEFINES

#include "point.h"
#include "../least_squares_approximation.cpp"

#include <vector>
#include <fstream>
#include <cmath>
#include <string>

std::vector<Point> getPoints(double f(double), double start, double end, double step);
std::vector<Point> getPointsFromCount(double f(double), double start, double end, int count);
std::vector<Point> getChebyshevPoints(double f(double), double start, double end, int count);
template <class T>
std::vector<T> getVectorFromRange(T start, T end, T step);

std::vector<Point> findPolyPoints(std::vector<double> X, std::vector<double> A);
std::vector<Point> countTrygonometricPoints(std::vector<double> X, std::vector<double> A, std::vector<double> B, double start, double end);

double findError(double f(double), std::vector<Point> points);

void printPointsJson(std::ofstream &dataFile, std::string title, const std::vector<Point> &points, 
                     const std::vector<Point> &nodes = std::move(std::vector<Point>()), bool isLast = false);

void printLinearApproximationJson(std::ofstream &dataFile, std::ofstream &errorFile, std::string funName, double f(double), 
                                 std::vector<int> N, int deg, double start, double end, const std::vector<double> &pointsX, 
                                 std::vector<Point> truePoints, bool isLast = false);

void printTrygonometricApproximationJson(std::ofstream &dataFile, std::ofstream &errorFile, std::string funName, double f(double), 
                                         std::vector< std::pair<int, std::vector<int>> > NM, double start, double end, const std::vector<double> &pointsX, 
                                         std::vector<Point> truePoints, bool isLast = false);


std::vector<Point> getPoints(double f(double), double start, double end, double step)
{
    std::vector<Point> points;
    for (double x = start; x <= end; x += step)
    {
        points.push_back(Point(x, f(x)));
    }
    return points;
}

std::vector<Point> getPointsFromCount(double f(double), double start, double end, int count)
{
    double step = (end - start) / (count - 1);
    return getPoints(f, start, end, step);
}

template <class T>
std::vector<T> getVectorFromRange(T start, T end, T step)
{
    std::vector<T> arr;
    for (double x = start; x <= end; x += step)
    {
        arr.push_back(x);
    }
    return arr;
}

std::vector<Point> getChebyshevPoints(double f(double), double start, double end, int count)
{
    std::vector<Point> points;
    for (int k = 0; k < count; k++)
    {
        double x = cos(((2 * k + 1) * M_PI) / (count * 2));
        x = ((end - start) / 2) * x + (start + end) / 2;    // Scaling to proper range
        points.push_back(Point(x, f(x)));
    }
    return points;
}

std::vector<Point> findPolyPoints(std::vector<double> X, std::vector<double> A)
{
    std::vector<Point> result;
    for (double x : X)
    {
        double y = 0;
        for (int i = 0; i < A.size(); i++)
        {
            y += A[i] * std::pow(x, i);
        }
        result.push_back(Point(x, y));
    }
    return result;
}

std::vector<Point> findTrygonometricPoints(std::vector<double> X, std::vector<double> A, std::vector<double> B, double start, double end)
{
    std::vector<Point> result;
    for (double x : X)
    {
        double y = A[0] / 2;
        for (int k = 1; k < A.size(); k++)  // Counting + transformation from [start, end] to [0, 2*PI]
        {
            y += A[k] * cos(k * ((x - start) / (end - start) * 2 * M_PI));
            y += B[k] * sin(k * ((x - start) / (end - start) * 2 * M_PI));
        }
        result.push_back(Point(x, y));
    }
    return result;
}

double findError(const std::vector<Point> &truePoints, const std::vector<Point> &approximatedPoints)
{
    double error = 0;
    for (int i = 0; i < truePoints.size(); i++)
    {
        error += std::abs(approximatedPoints[i].getY() - truePoints[i].getY());
    }
    return error;
}

void printPointsJson(std::ofstream &dataFile, std::string title, const std::vector<Point> &points, 
                     const std::vector<Point> &nodes, bool isLast)
{
    dataFile << "\t\"" << title << "\": [[";

    if (nodes.size() > 0)
    {
        for (int i = 0; i < nodes.size() - 1; i++)
        {
            dataFile << nodes[i] << ",";
        }
        dataFile << nodes.back();
    }
    dataFile << "], [";

    for (int i = 0; i < points.size() - 1; i++)
    {
        dataFile << points[i] << ",";
    }
    dataFile << points.back() << "]]";

    if (isLast == false)
    {
        dataFile << ",";
    }
    dataFile << std::endl;
}

void printLinearApproximationJson(std::ofstream &dataFile, std::ofstream &errorFile, std::string funName, double f(double), 
                                 std::vector<int> N, int deg, double start, double end, const std::vector<double> &pointsX, 
                                 std::vector<Point> truePoints, bool isLast)
{
    errorFile << "\"" << funName << " algebraic approx m=" << deg << "\": [";
    for (int i = 0; i < N.size() - 1; i++)
    {
        int n = N[i];
        auto nodes = getPointsFromCount(f, start, end, n);
        auto A = algebraicLeastSquares(nodes, deg);
        auto points = findPolyPoints(pointsX, A);
        std::string title = funName + " algebraic approx m=" + std::to_string(deg) + ", n=" + std::to_string(n);
        printPointsJson(dataFile, title, points, nodes, false);

        errorFile << "[" << n << "," << findError(truePoints, points) << "],";
    }

    auto nodes = getPointsFromCount(f, start, end, N.back());
    auto A = algebraicLeastSquares(nodes, deg);
    auto points = findPolyPoints(pointsX, A);
    std::string title = funName + " algebraic approx m=" + std::to_string(deg) + ", n=" + std::to_string(N.back());
    printPointsJson(dataFile, title, points, nodes, isLast);

    errorFile << "[" << N.back() << "," << findError(truePoints, points) << "]]";
    if (!isLast)
        errorFile << ",";
    errorFile << std::endl;
}

void printTrygonometricApproximationJson(std::ofstream &dataFile, std::ofstream &errorFile, std::string funName, double f(double), 
                                         std::vector< std::pair<int, std::vector<int>> > NM, double start, double end, const std::vector<double> &pointsX, 
                                         std::vector<Point> truePoints, bool isLast)
{
    for (int i = 0; i < NM.size() - 1; i++)
    {
        int deg = NM[i].first;
        auto N = NM[i].second;
        errorFile << "\"" << funName << " trygonometric approx m=" << deg << "\" : [";
        for (int i = 0; i < N.size(); i++)
        {
            int n = N[i];
            auto nodes = getPointsFromCount(f, start, end, n);
            auto pair = trygonometricLeastSquares(nodes, deg);
            auto points = findTrygonometricPoints(pointsX, pair.first, pair.second, start, end);
            std::string title = funName + " trygonometric approx m=" + std::to_string(deg) + ", n=" + std::to_string(n);
            printPointsJson(dataFile, title, points, nodes, false);

            errorFile << "[" << n << "," << findError(truePoints, points) << "]";
            if (i < N.size() - 1)
                errorFile << ",";
            else
                errorFile << "]," << std::endl;
        }
    }

    int deg = NM.back().first;
    auto N = NM.back().second;
    errorFile << "\"" << funName << " trygonometric approx m=" << deg << "\" : [";
    for (int i = 0; i < N.size() - 1; i++)
    {
        int n = N[i];
        auto nodes = getPointsFromCount(f, start, end, n);
        auto pair = trygonometricLeastSquares(nodes, deg);
        auto points = findTrygonometricPoints(pointsX, pair.first, pair.second, start, end);
        std::string title = funName + " trygonometric approx m=" + std::to_string(deg) + ", n=" + std::to_string(n);
        printPointsJson(dataFile, title, points, nodes, false);

        errorFile << "[" << n << "," << findError(truePoints, points) << "],";
    }

    int n = N.back();
    auto nodes = getPointsFromCount(f, start, end, n);
    auto pair = trygonometricLeastSquares(nodes, deg);
    auto points = findTrygonometricPoints(pointsX, pair.first, pair.second, start, end);
    std::string title = funName + " trygonometric approx m=" + std::to_string(deg) + ", n=" + std::to_string(n);
    printPointsJson(dataFile, title, points, nodes, isLast);

    errorFile << "[" << n << "," << findError(truePoints, points) << "]]";
    if (!isLast)
        errorFile << ",";
    errorFile << std::endl;
}