#include <vector>
#include "../utils/point.h"

std::vector<Point> lagrangeInterpolation(const std::vector<Point> &nodes, const std::vector<double> &pointsX)
{
    int n = nodes.size();
    std::vector<Point> points;
    for (int i = 0; i < pointsX.size(); i++)
    {
        double x = pointsX[i];
        double y = 0;
        for (int k = 0; k < n; k++)
        {
            double xk = nodes[k].getX();
            double d = 1, m = 1;
            for (int j = 0; j < n; j++)
            {
                if (j == k)
                    continue;
                d *= (x - nodes[j].getX());
                m *= (xk - nodes[j].getX());
            }
            double Lk = d / m;
            y += (Lk * nodes[k].getY());
        }
        points.push_back(Point(x, y));
    }
    return points;
}

std::vector<Point> lagrangeInterpolation(const std::vector<double (*)(double)> &funs, 
                                        const std::vector<Point> &nodes, const std::vector<double> &pointsX)
{
    return lagrangeInterpolation(nodes, pointsX);
}