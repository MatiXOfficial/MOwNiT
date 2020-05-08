#include <fstream>

#include "utils/matrix.h"
#include "methods.cpp"
#include "utils/utils.cpp"

constexpr int maxit = 50;

int main()
{
    std::vector< std::vector<double> > init;

    // linear equation no 1
    init = {{2, 1}, {5, 7}};
    Matrix<double> A1(init);
    init = {{11}, {13}};
    Matrix<double> B1(init);
    init = {{7.111111}, {-3.222222}};
    Matrix<double> X1(init);

    // linear equation no 2
    init = {{4, 1, 2}, {0, 2, 1}, {-4, 2, 8}};
    Matrix<double> A2(init);
    init = {{-2}, {-5}, {0}};
    Matrix<double> B2(init);
    init = {{-0.117647}, {-2.823529}, {0.647059}};
    Matrix<double> X2(init);

    // linear equation no 3
    init = {{-37, 9, 22}, {2, 14, -9}, {1, -3, 5}};
    Matrix<double> A3(init);
    init = {{5.6}, {-6.5}, {22.37}};
    Matrix<double> B3(init);
    init = {{3.514818}, {2.37322}, {5.194968}};
    Matrix<double> X3(init);

    // linear equation no 4
    init = {{10, -1, 2, 0}, {-1, 11, -1, 3}, {2, -1, 10, -1}, {0, 3, -1, 8}};
    Matrix<double> A4(init);
    init = {{6}, {25}, {-11}, {15}};
    Matrix<double> B4(init);
    init = {{1}, {2}, {-1}, {1}};
    Matrix<double> X4(init);

    // linear equation no 5
    init = {{-9, 1, 5, 1}, {1, 11, -3, 4}, {3, 6, 22.997, 4}, {2.1, 2.2, 2.3, 32.22}};
    Matrix<double> A5(init);
    init = {{5}, {-1}, {8}, {2}};
    Matrix<double> B5(init);
    init = {{-0.33776}, {0.022211}, {0.376450}, {0.055698}};
    Matrix<double> X5(init);

    // linear equation no 6
    init = {{13, 8, -1, 1, -1}, {2, 20, 7, -1, 1}, {4, 22, 36.6, -3, 2}, {1, -5, 0, -19.91, 1}, {3, 25, -2, -3.1, 52}};
    Matrix<double> A6(init);
    init = {{3.1}, {28}, {0}, {-6.45}, {5.46}};
    Matrix<double> B6(init);
    init = {{-1.036275}, {1.878502}, {-0.992324}, {-0.239557}, {-0.790789}};
    Matrix<double> X6(init);

    std::vector<Matrix<double>> Aarr = {A1, A2, A3, A4, A5, A6};
    std::vector<Matrix<double>> Barr = {B1, B2, B3, B4, B5, B6};
    std::vector<Matrix<double>> Xarr = {X1, X2, X3, X4, X5, X6};

    std::ofstream resultsFile;
    resultsFile.open("data/results.txt", std::ios::trunc);
    resultsFile << "Optimal numbers of iterations" << std::endl;
    resultsFile << "-----------------------------" << std::endl;

    Matrix<double> A, B, X;
    for (int i = 0; i < Aarr.size(); i++)
    {
        A = Aarr[i];    B = Barr[i];    X = Xarr[i];
        resultsFile << "Equation no: " << i + 1 << std::endl;
        resultsFile << "      jacobi: " << findOptimalItersCountJacobi(A, B, X) << std::endl;
        resultsFile << "gauss-seidel: " << findOptimalItersCountGaussSeidel(A, B, X) << std::endl;
        auto sorOptConf = findOptimalSorConf(A, B, X);
        resultsFile << "         sor: " << sorOptConf.first << " (" << sorOptConf.second << ")" << std::endl;
        resultsFile << "-----------------------------" << std::endl;
    }

    resultsFile.close();

    std::vector<double> omegas = {1.13, 0.93, 0.99, 1.02, 0.94, 1.02};

    std::ofstream dataFile;
    dataFile.open("data/data.json", std::ios::trunc);
    dataFile << "{" << std::endl;

    for (int i = 0; i < Aarr.size(); i++)
    {
        A = Aarr[i];    B = Barr[i];    X = Xarr[i];    double omega = omegas[i];
        dataFile << "\"eq no " << i + 1 << ", jacobi\":";
        printJacobiErrorsJSON(dataFile, A, B, X, maxit);
        dataFile << "\"eq no " << i + 1 << ", gauss_seidel\":";
        printGaussSeidelErrorsJSON(dataFile, A, B, X, maxit);
        dataFile << "\"eq no " << i + 1 << ", sor\":";
        if (i < Aarr.size() - 1)
            printSORErrorsJSON(dataFile, A, B, X, omega, maxit);
        else
            printSORErrorsJSON(dataFile, A, B, X, omega, maxit, true);
    }
    dataFile << "}";
    
    dataFile.close();
}