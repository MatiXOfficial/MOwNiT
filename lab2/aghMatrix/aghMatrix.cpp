#include "aghMatrix.h"
#include <stdexcept>
#include <math.h>

constexpr double EPS = 1e-8;


// Parameter Constructor                                                                                                                                                      
template<typename T>
AGHMatrix<T>::AGHMatrix(const std::vector<std::vector<T>>& mat) 
{
  matrix.resize(mat.size());
  for (unsigned i = 0; i < mat.size(); i++) 
  {
    matrix[i].resize(mat[i].size());
    for(unsigned j = 0; j < mat[i].size(); j++)
    {
      matrix[i][j] = mat[i][j];
    }
  }
  rows = matrix.size();
  cols = matrix[1].size();
}

// Parameter Constructor                                                                                                                                                      
template<typename T>
AGHMatrix<T>::AGHMatrix(unsigned _rows, unsigned _cols, const T& _initial) 
{
  matrix.resize(_rows);
  for (unsigned i=0; i<matrix.size(); i++) 
  {
    matrix[i].resize(_cols, _initial);
  }
  rows = _rows;
  cols = _cols;
}

// Copy Constructor                                                                                                                                                           
template<typename T>
AGHMatrix<T>::AGHMatrix(const AGHMatrix<T>& rhs) 
{
  matrix = rhs.matrix;
  rows = rhs.get_rows();
  cols = rhs.get_cols();
}

// Get the number of rows of the matrix                                                                                                                                       
template<typename T>
unsigned AGHMatrix<T>::get_rows() const 
{
  return this->rows;
}

// Get the number of columns of the matrix                                                                                                                                    
template<typename T>
unsigned AGHMatrix<T>::get_cols() const 
{
  return this->cols;
}

// Assignment Operator                                                                                                                                                        
template<typename T>
AGHMatrix<T>& AGHMatrix<T>::operator=(const AGHMatrix<T>& rhs) 
{
  if (&rhs == this)
    return *this;

  unsigned new_rows = rhs.get_rows();
  unsigned new_cols = rhs.get_cols();

  matrix.resize(new_rows);
  for (unsigned i=0; i<matrix.size(); i++) 
  {
    matrix[i].resize(new_cols);
  }

  for (unsigned i=0; i<new_rows; i++) 
  {
    for (unsigned j=0; j<new_cols; j++) 
    {
      matrix[i][j] = rhs(i, j);
    }
  }
  rows = new_rows;
  cols = new_cols;

  return *this;
}

template<typename T>
bool AGHMatrix<T>::operator==(const AGHMatrix<T>& rhs)
{
  if (this->rows != rhs.get_rows() || this->cols != rhs.get_cols())
  {
    return false;
  }
  for (int i = 0; i < this->rows; i++)
  {
    for (int j = 0; j < this->cols; j++)
    {
      if (std::abs(this->matrix[i][j] - rhs(i, j)) > EPS)
      {
        return false;
      }
    }
  }
  return true;
}

template<typename T>
bool AGHMatrix<T>::operator!=(const AGHMatrix<T>& rhs)
{
  return !((*this) == rhs);
}

// Access the individual elements                                                                                                                                             
template<typename T>
T& AGHMatrix<T>::operator()(const unsigned& row, const unsigned& col) 
{
  return this->matrix[row][col];
}

// Access the individual elements (const)                                                                                                                                     
template<typename T>
const T& AGHMatrix<T>::operator()(const unsigned& row, const unsigned& col) const 
{
  return this->matrix[row][col];
}

// Addition of two matrices                                                                                                                                                   
template<typename T>
AGHMatrix<T> AGHMatrix<T>::operator+(const AGHMatrix<T>& rhs) 
{
  if (this->rows != rhs.get_rows() || this->cols != rhs.get_cols())
  {
    throw std::invalid_argument("Wrong dimensions!");
  }
  std::vector< std::vector<T> > newMatrix(this->rows, std::vector<T>(this->cols));
  for (int i = 0; i < this->rows; i++)
  {
    for (int j = 0; j < this->cols; j++)
    {
      newMatrix[i][j] = this->matrix[i][j] + rhs(i, j);
    }
  }
  return AGHMatrix<T>(newMatrix);
}

// Left multiplication of this matrix and another                                                                                                                              
template<typename T>
AGHMatrix<T> AGHMatrix<T>::operator*(const AGHMatrix<T>& rhs) 
{
  if (this->cols != rhs.get_rows())
  {
    throw std::invalid_argument("Wrong dimensions!");
  }
  std::vector< std::vector<T> > newMatrix(this->rows, std::vector<T>(rhs.get_cols(), 0));
  for (int i = 0; i < this->rows; i++)
  {
    for (int j = 0; j < rhs.get_cols(); j++)
    {
      for (int k = 0; k < this->cols; k++)
      {
        newMatrix[i][j] += this->matrix[i][k] * rhs(k, j);
      }
    }
  }
  return AGHMatrix<T>(newMatrix);
}

// Printing matrix                                                                                                                        
template<typename T>
std::ostream& operator<<(std::ostream& stream, const AGHMatrix<T>& matrix) 
{
  for (int i=0; i<matrix.get_rows(); i++) 
  { 
    for (int j=0; j<matrix.get_cols(); j++) 
    {
        stream << matrix(i,j) << ", ";
    }
    stream << std::endl;
  }
  stream << std::endl;
}

// Zadanie 2
template<typename T>
bool AGHMatrix<T>::isSymmetric()
{
  if (this->rows != this->cols)
  {
    throw std::invalid_argument("Matrix should be square!");
  }
  for (int i = 1; i < this->rows; i++)
  {
    for (int j = 0; j < i; j++)
    {
      if (this->matrix[i][j] != this->matrix[i][j])
      {
        return false;
      }
    }
  }
  return true;
}

template<typename T>
AGHMatrix<T> AGHMatrix<T>::createMinor(int i, int j)
{
  std::vector< std::vector<T> > newMatrix;
  for (int k = 0; k < this->rows; k++)
  {
    if (k != i)
    {
      newMatrix.push_back({});
      for (int l = 0; l < this->cols; l++)
      {
        if (l != j)
        {
          newMatrix.back().push_back(this->matrix[k][l]);
        }
      }
    }
  }
  return AGHMatrix<T>(newMatrix);
}

template<typename T>
T AGHMatrix<T>::minorDet()
{
  if (this->rows == 1)
  {
    return this->matrix[0][0];
  }
  T det = 0;
  int sign = 1;
  for (int i = 0; i < this->rows; i++)
  {
    AGHMatrix<T> newMatrix = this->createMinor(i, 0);
    det += sign * this->matrix[i][0] * newMatrix.minorDet();
    sign = -sign;
  }
  return det;
}

template<typename T>
T AGHMatrix<T>::det()
{
  if (this->cols != this->rows)
  {
    throw std::invalid_argument("Matrix should be square!");
  }
  return this->minorDet();
}

template<typename T>
AGHMatrix<T> AGHMatrix<T>::transpose()
{
  std::vector< std::vector<T> > newMatrix(this->cols, std::vector<T>(this->rows));
  for (int i = 0; i < this->rows; i++)
  {
    for (int j = 0; j < this->cols; j++)
    {
      newMatrix[j][i] = this->matrix[i][j];
    }
  }
  return AGHMatrix<T>(newMatrix);
}

// Zadanie 3
template<typename T>
std::vector< AGHMatrix<double> > AGHMatrix<T>::doolittle()
{
  if (this->rows != this->cols)
  {
    throw std::invalid_argument("Matrix should be square!");
  }
  int n = this->rows;

  std::vector< std::vector<double> > l(n, std::vector<T>(n, 0));
  for (int i = 0; i < n; i++)
  {
    l[i][i] = 1;
  }
  std::vector< std::vector<double> > u(n, std::vector<T>(n, 0));

  for (int i = 0; i < n; i++)
  {
    for (int j = i; j < n; j++)
    {
      u[i][j] = this->matrix[i][j];
      for (int k = 0; k < i; k++)
      {
        u[i][j] -= l[i][k] * u[k][j];
      }
    }
    for (int j = i + 1; j < n; j++)
    {
      double sum = 0;
      for (int k = 0; k < i; k++)
      {
        sum += l[j][k] * u[k][i];
      }
      l[j][i] = (1.0 / u[i][i]) * (this->matrix[j][i] - sum);
    }
  }

  return {AGHMatrix<double>(l), AGHMatrix<double>(u)};
}

// Zadanie 4
template <typename T>
std::vector< AGHMatrix<double> > AGHMatrix<T>::cholesky()
{
  if (!this->isSymmetric())
  {
    throw std::invalid_argument("Matrix should be symmetric!");
  }
  int n = this->rows;

  std::vector< std::vector<double> > l(n, std::vector<T>(n, 0));
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j <= i; j++)
    {
      double sum = 0;
      if (j == i)
      {
        for (int k = 0; k < j; k++)
        {
          sum += l[j][k] * l[j][k];
        }
        l[j][j] = sqrt(this->matrix[j][j] - sum);
      }
      else
      {
        for (int k = 0; k < j; k++)
        {
          sum += l[i][k] * l[j][k];
        }
        l[i][j] = (this->matrix[i][j] - sum) / l[j][j];
      }
    }
  }

  AGHMatrix<double> L(l);
  return {L, L.transpose()};
}