#include "matrix.h"

#include <stdexcept>
#include <cmath>

constexpr double EPS = 1e-6;

template<typename T>
Matrix<T>::Matrix(const std::vector< std::vector<T> > &values)
{
    rows = values.size();
    cols = values[0].size();
    matrix.resize(this->rows, std::vector<T>(this->cols));

    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->cols; j++)
        {
            matrix[i][j] = values[i][j];
        }
    }
}

template<typename T>
Matrix<T>::Matrix(unsigned rows, unsigned cols, T init) : rows(rows), cols(cols)
{
    matrix.resize(rows, std::vector<T>(cols, init));
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T> &other)
{
    matrix = other.matrix;
    rows = other.rows;
    cols = other.cols;
}

template<typename T>
bool Matrix<T>::operator==(const Matrix<T> &other) const
{
    if (rows != other.rows || cols != other.cols)
        return false;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (std::abs(matrix[i][j] - other(i, j)) > EPS)
            {
                return false;
            }
        }
    }
    return true;
}

template<typename T>
bool Matrix<T>::operator!=(const Matrix<T>& other) const
{
    return !(*this == other);
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &other) const
{
    if (rows != other.rows || cols != other.cols)
        throw std::invalid_argument("wrong dimensions");

    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            result(i, j) = matrix[i][j] + other(i, j);
        }
    }
    return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &other) const
{
    if (rows != other.rows || cols != other.cols)
        throw std::invalid_argument("wrong dimensions");

    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            result(i, j) = matrix[i][j] - other(i, j);
        }
    }
    return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &other) const
{
    if (cols != other.rows)
        throw std::invalid_argument("wrong dimensions");

    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < other.cols; j++)
        {
            for (int k = 0; k < cols; k++)
            {
                result(i, j) += matrix[i][k] * other(k, j);
            }
        }
    }
    return result;
}

template<typename T>
Matrix<T> operator-(const Matrix<T> &matrix)
{
    Matrix<T> result(matrix.rows, matrix.cols);
    for (int i = 0; i < matrix.rows; i++)
    {
        for (int j = 0; j < matrix.cols; j++)
        {
            result(i, j) = -matrix(i, j);
        }
    }
    return result;
}

template<typename T>
T& Matrix<T>::operator()(unsigned row, unsigned col)
{
    return matrix[row][col];
}

template<typename T>
const T& Matrix<T>::operator()(unsigned row, unsigned col) const
{
    return matrix[row][col];
}

template<typename T>
std::ostream& operator<<(std::ostream& output, const Matrix<T> &matrix)
{
    for (int i = 0; i < matrix.rows; i++)
    {
        for (int j = 0; j < matrix.cols; j++)
        {
            output << matrix(i, j) << ", ";
        }
        output << std::endl;
    }
    output << std::endl;
    return output;
}

template<typename T>
unsigned Matrix<T>::getRows() const
{
    return rows;
}

template<typename T>
unsigned Matrix<T>::getCols() const
{
    return cols;
}

template<typename T>
bool Matrix<T>::isSquare() const
{
    return rows == cols;
}

template<typename T>
bool Matrix<T>::isDiagonallyDominant() const
{
    if (!isSquare())
        return false;
        
    for (int i = 0; i < rows; i++)
    {
        T sum = 0;
        for (int j = 0; j < cols; j++)
        {
            if (j != i)
            {
                sum += std::abs(matrix[i][j]);
            }
        }
        if (std::abs(matrix[i][i]) < sum)
        {
            return false;
        }
    }
    return true;
}