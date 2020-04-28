#include <utility>

// Przygotowanie macierzy schodkowej
void gaussPrepareMatrix(std::vector< std::vector<double> > &M, int start = 0)
{
    int n = M.size();
    if (n - start == 1)
    {
        return;
    }

    for (int i = start; i < n; i++)
    {
        if (M[i][start] != 0)
        {
            if (i != start)
            {
                for (int j = start; j <= n; j++)
                {
                    std::swap(M[i][j], M[j][i]);
                }
            }
            break;
        }
    }

    for (int i = start + 1; i < n; i++)
    {
        double mult = M[i][start] / M[start][start];
        for (int j = start; j <= n; j++)
        {
            M[i][j] -= mult * M[start][j];
        }
    }
    gaussPrepareMatrix(M, start + 1);
}

std::vector<double> gaussSolve(std::vector< std::vector<double> > A, std::vector<double> B)
{
    // Przygotowanie "połączonej" macierzy
    int n = A.size();
    std::vector< std::vector<double> > M(n, std::vector<double>(n + 1));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            M[i][j] = A[i][j];
        }
        M[i][n] = B[i];
    }
    
    // Obliczenie macierzy schodkowej
    gaussPrepareMatrix(M);

    // Obliczenie rozwiązania
    std::vector<double> X(n);
    for (int i = n - 1; i >= 0; i--)
    {
        X[i] = M[i][n];
        for (int j = i + 1; j < n; j++)
        {
            X[i] -= M[i][j] * X[j];
        }
        X[i] /= M[i][i];
    }
    return X;
}