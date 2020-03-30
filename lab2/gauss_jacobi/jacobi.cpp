#include "../aghMatrix/aghMatrix.h"

template <typename T>
AGHMatrix<double> jacobiSolve(AGHMatrix<T> &A, AGHMatrix<T> &B, int acc)
{
    int n = A.get_rows();
    for (int i = 0; i < n; i++)
    {
        T sum = -abs(A(i, i));
        for (int j = 0; j < n; j++)
        {
            sum += abs(A(i, j));
        }
        if (abs(A(i, i)) <= sum)
        {
            throw std::invalid_argument("Matrix should be diagonally dominant!");
        }
    }

    std::vector< std::vector<double> > l(n, std::vector<double>(n, 0));
    std::vector< std::vector<double> > nm(n, std::vector<double>(n, 0));
    std::vector< std::vector<double> > u(n, std::vector<double>(n, 0));
    for (int i = 0; i < n; i++)
    {
        nm[i][i] = -1.0 / A(i, i);
        for (int j = 0; j < i; j++)
        {
            l[i][j] = A(i, j);
            u[j][i] = A(j, i);
        }
    }
    AGHMatrix<double> L(l);
    AGHMatrix<double> N(nm);
    AGHMatrix<double> U(u);

    AGHMatrix<double> M = N * (L + U);

    for (int i = 0; i < n; i++)
    {
        N(i, i) = - N(i, i);
    }

    AGHMatrix<double> X(n, 1, 0);
    for (int i = 0; i < acc; i++)
    {
        X = (M * X) + (N * B);
    }
    return X;
}