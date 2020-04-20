#include <vector>
#include "../utils/point.h"

std::vector<Point> hermiteInterpolation(const std::vector<double (*)(double)> &funs, 
                                        const std::vector<Point> &nodes, const std::vector<double> &pointsX)
{
    int derNum = funs.size();
    int n = nodes.size() * derNum;

    std::vector<double> nodesX;
    std::vector<std::vector<double>> F(n, std::vector<double>());
    for (Point node : nodes)
    {
        for (int i = 0; i < derNum; i++)
        {
            nodesX.push_back(node.getX());
            F[0].push_back(node.getY());
        }
    }

    int fact = 1;
    for (int i = 1; i < n; i++)
    {
        if (i < derNum)
            fact *= i;
        for (int p = 0; p < n - i; p++)
        {
            int q = p + i;
            if (nodesX[p] == nodesX[q])     // derivative
            {
                F[i].push_back(funs[i](nodesX[p]) / fact);
            }
            else                            // normal
            {
                double val = (F[i - 1][p + 1] - F[i - 1][p]) / (nodesX[q] - nodesX[p]);
                F[i].push_back(val);
            }
        }
    }

    std::vector<Point> points;
    for (double x : pointsX)
    {
        double y = F[0][0];
        double factor = 1;
        for (int k = 1; k < n; k++)
        {
            factor *= (x - nodesX[k - 1]);
            y += (factor * F[k][0]);
        }
        points.push_back(Point(x, y));
    }
    return points;
}