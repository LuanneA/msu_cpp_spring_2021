#pragma once
#include <iostream>
using namespace std;

class ProxyRow{
    private:
        int *data_;
        size_t size_;
    public:
    int & operator[](size_t j);
    const int & operator[](size_t j) const;
    ProxyRow(int *data, size_t size_);
};

class Matrix{
    public:
        Matrix(size_t r = 0, size_t c = 0);
        Matrix(const Matrix & M);
        Matrix operator=(const Matrix& M);
        bool operator==(const Matrix &M) const;
        bool operator!=(const Matrix &M) const;
        Matrix& operator*=(int n);
        Matrix operator+(const Matrix &M) const;
        ProxyRow operator[](size_t r);
        const ProxyRow operator[](size_t r) const;
        friend std::ostream &operator<<(std::ostream &out, const Matrix &M);
        size_t getRows() const;
        size_t getColumns() const;
        ~Matrix();
    private:
        ProxyRow *rows_;
        size_t rows;
        size_t cols;
        int** matrix;
};
