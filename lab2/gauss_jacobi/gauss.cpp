#include "../aghMatrix/aghMatrix.h"
#include <utility>

// Przygotowanie macierzy schodkowej
template <typename T>
void gaussPrepareMatrix(AGHMatrix<T> &M, int start = 0)
{
    int n = M.get_rows();
    if (n - start == 1)
    {
        return;
    }

    for (int i = start; i < n; i++)
    {
        if (M(i, start) != 0)
        {
            if (i != start)
            {
                for (int j = start; j <= n; j++)
                {
                    std::swap(M(i, j), M(j, i));
                }
            }
            break;
        }
    }

    for (int i = start + 1; i < n; i++)
    {
        double mult = M(i, start) / M(start, start);
        for (int j = start; j <= n; j++)
        {
            M(i, j) -= mult * M(start, j);
        }
    }
    gaussPrepareMatrix(M, start + 1);
}

template <typename T>
AGHMatrix<double> gaussSolve(AGHMatrix<T> &A, AGHMatrix<T> &B)
{
    // Przygotowanie "połączonej" macierzy
    int n = A.get_rows();
    std::vector< std::vector<T> > newMatrix(n, std::vector<T>(n + 1));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            newMatrix[i][j] = A(i, j);
        }
        newMatrix[i][n] = B(i, 0);
    }
    AGHMatrix<T> M(newMatrix);
    
    // Obliczenie macierzy schodkowej
    gaussPrepareMatrix(M);

    // Obliczenie rozwiązania
    std::vector< std::vector<double> > x(n, std::vector<double>(1, 0));
    for (int i = n - 1; i >= 0; i--)
    {
        x[i][0] = M(i, n);
        for (int j = i + 1; j < n; j++)
        {
            x[i][0] -= M(i, j) * x[j][0];
        }
        x[i][0] /= M(i, i);
    }
    return AGHMatrix<double>(x);
}