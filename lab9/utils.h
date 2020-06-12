#pragma once
#include <tuple>
#include <vector>
#include <fstream>
#include <string>

class Triple
{
    double x;
    double y;
    double z;

public:
    Triple(double x = 0.0, double y = 0.0, double z = 0.0);

    Triple operator+(Triple other);
    Triple& operator=(Triple other);
    friend Triple operator*(double h, Triple triple);

    double getX();
    double getY();
    double getZ();
};


void printTriplesVectorToJSON(std::ofstream &file, std::vector<Triple> &vec, std::string title);

void printTask4ResultToJSON(std::ofstream &file, std::vector<double> &vec, 
                            double x0, double xk, double h, std::string title);

#include "utils.cpp"