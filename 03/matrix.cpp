#include <iostream>
#include "matrix.h"
using namespace std;

int & ProxyRow::operator[](size_t j){
    return data_[j];
}

ProxyRow::ProxyRow(int *data){
    data_ = data;
}


Matrix::Matrix(size_t r, size_t c){
    rows = r;
    cols = c;
    matrix = (int**) new int*[rows];
    for (int i = 0; i < rows; i++)
         matrix[i] = new int[cols];
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            matrix[i][j] = 0;
}

Matrix::Matrix(const Matrix & M){
    rows = M.rows;
    cols = M.cols;
    matrix = (int**) new int*[rows];
    for (int i = 0; i < rows; i++)
         matrix[i] = new int[cols];
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
          matrix[i][j] = M[i][j];
}

Matrix Matrix::operator=(const Matrix& M){
     if (rows != M.rows || cols != M.cols){
          throw std::out_of_range("");
     }
     for (int i = 0; i < rows; i++)
         for (int j = 0; j < cols; j++)
             matrix[i][j] = M[i][j];
     return *this;
}

bool Matrix::operator==(const Matrix &M) const{
    if ((rows != M.rows) || (cols != M.cols)){
        return false;
    }
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j){
            if (M[i][j] != matrix[i][j]){
                return false;
            }
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix &M) const{
    return (!(*this == M));
}

Matrix Matrix::operator*=(int n){
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j){
            matrix[i][j] *= n;
        }
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix &M) const{
    if ((M.rows != rows) || (M.cols != cols)){
        throw std::out_of_range("");
    }
    Matrix new_matrix(M.rows, M.cols);
    for (size_t i = 0; i < M.rows; i++){
        for (size_t j = 0; j < M.cols; j++){
            new_matrix[i][j] = matrix[i][j] + M[i][j];
        }
    }
    return new_matrix;
}

ProxyRow Matrix::operator[](size_t r){
    if (r >= rows){
        throw std::out_of_range("");
    }
    return ProxyRow(matrix[r]);
}

ProxyRow Matrix::operator[](size_t r) const
{
    if (r >= rows){
        throw std::out_of_range("");
    }
    return ProxyRow(matrix[r]);
}

std::ostream& operator<<(std::ostream &out, const Matrix &M){
    for (size_t i = 0; i < M.rows; ++i) {
        for (size_t j = 0; j < M.cols; ++j) {
            out << M[i][j] << ' ';
        }
        out << endl;
    }
    return out;
}

size_t Matrix::getRows(){
    return rows;
}

size_t Matrix::getColumns(){
    return cols;
}


Matrix::~Matrix(){
    if (rows > 0){
        for (int i = 0; i < rows; i++)
        delete[] matrix[i];
    }
    if (cols > 0)
         delete[] matrix;
}
