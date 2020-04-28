#include "point.h"

double Point::getX() const
{
    return this->x;
}
double Point::getY() const
{
    return this->y;
}

std::ostream& operator<<(std::ostream &out, const Point &point)
{
    out << "[" << point.x << "," << point.y << "]";
    return out;
}