#pragma once

#define _USE_MATH_DEFINES

#include "point.h"

#include <vector>
#include <fstream>
#include <cmath>

std::vector<Point> getPoints(double f(double), double start, double end, double step);
std::vector<Point> getPointsFromCount(double f(double), double start, double end, int count);
std::vector<Point> getChebyshevPoints(double f(double), double start, double end, int count);
std::vector<double> getVectorFromRange(double start, double end, double step);

double findError(double f(double), std::vector<Point> points);

void printPointsJson(std::ofstream &dataFile, std::string title, const std::vector<Point> &points, 
                     const std::vector<Point> &nodes = std::move(std::vector<Point>()), bool isLast = false);

void printInterpolationDataJsons(std::ofstream &dataFile, std::ofstream &errorFile, std::string interpolationName,
                                 std::vector<Point> interpolation(const std::vector<double (*)(double)> &funs, const std::vector<Point>&, const std::vector<double>&),
                                 std::string nodeType, const std::vector<double (*)(double)> &funs, const std::vector<Point> &truePoints,
                                 const std::vector<double> &pointsX, int maxCount, double start, double end, bool isLast=false);


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

std::vector<double> getVectorFromRange(double start, double end, double step)
{
    std::vector<double> arr;
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

double findError(const std::vector<Point> &truePoints, const std::vector<Point> &interpolatedPoints)
{
    double error = 0;
    for (int i = 0; i < truePoints.size(); i++)
    {
        error += std::abs(interpolatedPoints[i].getY() - truePoints[i].getY());
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

void printInterpolationDataJsons(std::ofstream &dataFile, std::ofstream &errorFile, std::string interpolationName,
                                 std::vector<Point> interpolation(const std::vector<double (*)(double)> &funs, const std::vector<Point>&, const std::vector<double>&),
                                 std::string nodeType, const std::vector<double (*)(double)> &funs, const std::vector<Point> &truePoints,
                                 const std::vector<double> &pointsX, int maxCount, double start, double end, bool isLast)
{
    errorFile << "\t\"" << interpolationName << ": " << nodeType << "\": [";
    auto f = funs[0];
    for (int count = 2; count < maxCount - 1; count++)
    {
        std::vector<Point> nodes;
        if (nodeType == "regular")
            nodes = getPointsFromCount(f, start, end, count);
        else
            nodes = getChebyshevPoints(f, start, end, count);

        auto points = interpolation(funs, nodes, pointsX);

        std::string title = interpolationName + ": " + std::to_string(count) + " " + nodeType + " nodes";
        printPointsJson(dataFile, title, points, nodes);

        double error = findError(truePoints, points);
        errorFile << "[" << count << "," << error << "], ";
    }

    std::vector<Point> nodes;
    if (nodeType == "regular")
        nodes = getPointsFromCount(f, start, end, maxCount);
    else
        nodes = getChebyshevPoints(f, start, end, maxCount);

    auto points = interpolation(funs, nodes, pointsX);
    std::string title = interpolationName + ": " + std::to_string(maxCount) + " " + nodeType + " nodes";
    if (isLast)
        printPointsJson(dataFile, title, points, nodes, true);
    else
        printPointsJson(dataFile, title, points, nodes);

    double error = findError(truePoints, points);
    errorFile << "[" << maxCount << "," << error << "]]";
    if (isLast == false)
        errorFile << ",";
    errorFile << std::endl;
}