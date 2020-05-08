#pragma once

#include <vector>
#include <iostream>

template<typename T> class Matrix
{
private:
    std::vector< std::vector<T> > matrix;
    unsigned rows;
    unsigned cols;

public:
    Matrix() = default;
    Matrix(const std::vector< std::vector<T> > &values);
    Matrix(unsigned rows, unsigned cols, T init = 0);
    Matrix(const Matrix<T> &other);
    virtual ~Matrix() = default;

    bool operator==(const Matrix<T> &other) const;
    bool operator!=(const Matrix<T> &other) const;

    Matrix<T> operator+(const Matrix<T> &other) const;
    Matrix<T> operator-(const Matrix<T> &other) const;
    Matrix<T> operator*(const Matrix<T> &other) const;
    template<typename U>
    friend Matrix<U> operator-(const Matrix<U> &matrix);


    T& operator()(unsigned row, unsigned col = 0);
    const T& operator()(unsigned row, unsigned col = 0) const;

    template<typename U>
    friend std::ostream& operator<<(std::ostream& output, const Matrix<U> &matrix);

    unsigned getRows() const;
    unsigned getCols() const;

    bool isSquare() const;
    bool isDiagonallyDominant() const;
};

#include "matrix.cpp"