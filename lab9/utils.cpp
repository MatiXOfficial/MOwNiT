#include "utils.h"


Triple::Triple(double x, double y, double z) : x(x), y(y), z(z)
{
}

Triple Triple::operator+(Triple other)
{
    return Triple(this->x + other.x, this->y + other.y, this->z + other.z);
}

Triple& Triple::operator=(Triple other)
{
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    return *this;
}

Triple operator*(double h, Triple triple)
{
    return Triple(h * triple.x, h * triple.y, h * triple.z);
}

double Triple::getX()
{
    return x;
}

double Triple::getY()
{
    return y;
}

double Triple::getZ()
{
    return z;
}


void printTriplesVectorToJSON(std::ofstream &file, std::vector<Triple> &vec, std::string title)
{
    file << "\"" << title << "\" : [";
    for (int i = 0; i < vec.size(); i++)
    {
        file << "[" << vec[i].getX() << ", "
                    << vec[i].getY() << ", "
                    << vec[i].getZ() << "]";
        if (i < vec.size() - 1)
        {
            file << ", ";
        }
    }
    file << "]";
}


void printTask4ResultToJSON(std::ofstream &file, std::vector<double> &vec, 
                            double x0, double h, std::string title)
{
    file << "\"" << title << "\" : [";
    double x = x0;
    for (int i = 0; i < vec.size(); i++)
    {
        file << "[" << x << ", " << vec[i] << "]";
        if (i < vec.size() - 1)
        {
            file << ", ";
        }
        x += h;
    }
    file << "]";
}