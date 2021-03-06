#pragma once 

#include <vector>
#include <iostream>

template <typename T> class AGHMatrix 
{
private:
    std::vector<std::vector<T>> matrix;
    unsigned rows;
    unsigned cols;

    // Zadanie 2
    AGHMatrix<T> createMinor(int i, int j);
    T minorDet();

public:
    AGHMatrix(const std::vector<std::vector<T>>& matrix);
    AGHMatrix(unsigned _rows, unsigned _cols, const T& _initial);
    AGHMatrix(const AGHMatrix<T>& rhs);
    virtual ~AGHMatrix() = default;

    // Operator overloading, for "standard" mathematical matrix operations                                                                                                                                                          
    AGHMatrix<T>& operator=(const AGHMatrix<T>& rhs);
    bool operator==(const AGHMatrix<T>& rhs);
    bool operator!=(const AGHMatrix<T>& rhs);

    // Matrix mathematical operations                                                                                                                                                                                               
    AGHMatrix<T> operator+(const AGHMatrix<T>& rhs);
    AGHMatrix<T> operator*(const AGHMatrix<T>& rhs);

    // Access the individual elements                                                                                                                                                                                               
    T& operator()(const unsigned& row, const unsigned& col);
    const T& operator()(const unsigned& row, const unsigned& col) const;
    
    // Printing matrix
    std::ostream& operator<<(const AGHMatrix<T>& matrix);

    // Access the row and column sizes                                                                                                                                                                                              
    unsigned get_rows() const;
    unsigned get_cols() const;

    // Zadanie 2
    bool isSymmetric();
    T det();
    AGHMatrix<T> transpose();

    // Zadanie 3 - faktoryzacja LU
    std::vector< AGHMatrix<double> > doolittle();

    // Zadanie 4 - faktoryzacja Cholesky'ego
    std::vector< AGHMatrix<double> > cholesky();
};

#include "aghMatrix.cpp"
