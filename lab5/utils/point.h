#pragma once

#include <iostream>

class Point
{
private:
    const double x;
    const double y;

public:
    Point(double x, double y) : x(x), y(y) {}

    double getX() const;
    double getY() const;
    
    friend std::ostream& operator<<(std::ostream &out, const Point &point);
};

#include "point.cpp"