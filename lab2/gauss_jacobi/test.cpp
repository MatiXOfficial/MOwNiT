#include "gauss.cpp"
#include "jacobi.cpp"

int main()
{
    // Gauss
    std::vector< std::vector<double> > initA { {0.0001, -5.0300, 5.8090, 7.8320},
                                               {2.2660, 1.9950, 1.2120, 8.0080},
                                               {8.8500, 5.6810, 4.5520, 1.3020},
                                               {6.7750, -2.253, 2.9080, 3.9700} };
    AGHMatrix<double> A(initA);

    std::vector< std::vector<double> > initB { {9.5740},
                                               {7.2190}, 
                                               {5.7300}, 
                                               {6.2910} };
    AGHMatrix<double> B(initB);

    std::vector< std::vector<double> > initX { {0.21602477},
                                               {-0.00791511}, 
                                               {0.63524333}, 
                                               {0.74617428} };
    AGHMatrix<double> X(initX);
    std::cout << "Gauss:" << std::endl;
    AGHMatrix<double> XGauss = gaussSolve(A, B);
    if (X == XGauss)
    {
        std::cout << "ok" << std::endl;
    }
    else
    {
        std::cout << "ERROR!" << std::endl;
    }

    // Jacobi
    std::vector< std::vector<double> > initA2 { {12, 5, 2, 3},
                                                {-2, 10, -1, 5},
                                                {5, 1, 14, -7},
                                                {3, 2, -8, -16} };
    AGHMatrix<double> A2(initA2);

    std::vector< std::vector<double> > initB2 { {2},
                                                {8}, 
                                                {0}, 
                                                {-2} };
    AGHMatrix<double> B2(initB2);

    std::vector< std::vector<double> > initX2 { {-0.17493889},
                                                {0.70358168}, 
                                                {0.08183654}, 
                                                {0.1392284} };
    AGHMatrix<double> X2(initX2);

    AGHMatrix<double> XJacobi(B2.get_rows(), 1, 0);
    int acc = 0;
    while (XJacobi != X2)
    {
        acc++;
        XJacobi = jacobiSolve(A2, B2, acc);
        if (acc % 5 == 0)
        {
            std::cout << "iteration " << acc << std::endl << XJacobi;
        }
    }
    std::cout << "Jacobi:" << std::endl;
    std::cout << "Matrices are equal after " << acc << " iterations." << std::endl;
}