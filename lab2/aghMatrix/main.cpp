#include "aghMatrix.h"
#include <fstream>

int main() 
{
    std::ofstream resultsFile;
    resultsFile.open("results.txt", std::ios::trunc);

    ////////////// Zadanie 1, 2 /////////////////////////
    resultsFile << "Zadanie 1, 2" << std::endl;

    std::vector<std::vector<double>> init { { 1.0, 2.0, 3.0 }, 
                                            { 4.0, 5.0, 7.0 }, 
                                            { 6.0, 8.0, 9.0 } }; 
    AGHMatrix<double> mat1(init);

    std::vector<std::vector<double>> init2 { { 1.0, 2.0, 3.0 }, 
                                             { 2.0, -2.0, 1.0 }, 
                                             { 3.0, 1.0, 8.0 } }; 
    AGHMatrix<double> mat2(init2);

    resultsFile << mat1 << mat2;

    resultsFile << "+" << std::endl << mat1 + mat2;
    resultsFile << "*" << std::endl << mat1 * mat2;

    resultsFile << "isSymmetric" << std::endl;
    resultsFile << mat1.isSymmetric() << " " << mat2.isSymmetric() << std::endl;
    resultsFile << "det" << std::endl;
    resultsFile << mat1.det() << " " << mat2.det() << std::endl << std::endl;
    resultsFile << "transpose" << std::endl;
    resultsFile << mat1.transpose() << mat2.transpose() << std::endl;

    ////////////// Zadanie 3 /////////////////////////
    resultsFile << "Zadanie 3" << std::endl;
    std::vector<std::vector<double>> init_LU { { 5.0, 3.0, 2.0 }, 
                                               { 1.0, 2.0, 0.0 }, 
                                               { 3.0, 0.0, 4.0 } };
    AGHMatrix<double> mat3(init_LU);
    resultsFile << mat3;

    auto LU = mat3.doolittle();
    if (LU[0] * LU[1] == mat3)
    {
        std::cout << "LU: ok" << std::endl;
    }
    else
    {
        std::cout << "LU: ERROR!!!" << std::endl;
    }
    resultsFile << "L:" << std::endl;
    resultsFile << LU[0];
    resultsFile << "U:" << std::endl;
    resultsFile << LU[1];

    ////////////// Zadanie 4 /////////////////////////
    resultsFile << "Zadanie 4" << std::endl;
    std::vector<std::vector<double>> init_cholesky { { 4.0, 12.0, -16.0 }, 
                                                     { 12.0, 37.0, -43.0 }, 
                                                     { -16.0, -43.0, 98.0 } };
    AGHMatrix<double> mat4(init_cholesky);
    resultsFile << mat4;

    auto LLt = mat4.cholesky();
    if (LLt[0] * LLt[1] == mat4)
    {
        std::cout << "cholesky: ok" << std::endl;
    }
    else
    {
        std::cout << "cholesky: ERROR!!!" << std::endl;
    }
    resultsFile << "L:" << std::endl;
    resultsFile << LLt[0];
    resultsFile << "Lt:" << std::endl;
    resultsFile << LLt[1];



    resultsFile.close();
    return 0;
}