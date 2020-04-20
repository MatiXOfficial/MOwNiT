#include <vector>
#include "../utils/point.h"

std::vector<Point> newtonInterpolation(const std::vector<Point> &nodes, const std::vector<double> &pointsX)
{
    int n = nodes.size();
    std::vector< std::vector<double> > F(n, std::vector<double>());
    for (Point node : nodes)
    {
        F[0].push_back(node.getY());
    }
    for (int i = 1; i < n; i++)
    {
        for (int p = 0; p < n - i; p++)
        {
            double val = (F[i - 1][p + 1] - F[i - 1][p]) / (nodes[p + i].getX() - nodes[p].getX());
            F[i].push_back(val);
        }
    }

    std::vector<Point> points;
    for (double x : pointsX)
    {
        double y = F[0][0];
        double factor = 1;
        for (int k = 1; k < n; k++)
        {
            factor *= (x - nodes[k - 1].getX());
            y += (factor * F[k][0]);
        }
        points.push_back(Point(x, y));
    }
    return points;
}

std::vector<Point> newtonInterpolation(const std::vector<double (*)(double)> &funs, 
                                       const std::vector<Point> &nodes, const std::vector<double> &pointsX)
{
    return newtonInterpolation(nodes, pointsX);
}