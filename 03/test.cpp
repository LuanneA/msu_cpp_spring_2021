#include <iostream>
#include "matrix.h"
using namespace std;


void Test_size(){
    const size_t rows = 5;
    const size_t cols = 3;

    Matrix m(rows, cols);

    assert(m.getRows() == 5);
    assert(m.getColumns() == 3);
}

void Test_input_multiplication(){
    const size_t rows = 5;
    const size_t cols = 3;

    Matrix m(rows, cols);
    for (int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++)
        {
            m[i][j] = i + j;
        }
    }
    for (int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++)
        {
            assert(m[i][j] == i + j);
        }
    }
    m *= 3;
    for (int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++)
        {
            assert(m[i][j] == (i + j)*3);
        }
    }
}

void Test_output(){
    const size_t rows = 5;
    const size_t cols = 3;
    Matrix m2(rows, cols);
    Matrix m1(rows, cols);
    for (int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++)
        {
            m2[i][j] = 1;
        }
    }
    for (int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++)
        {
            m1[i][j] = 1;
        }
    }
    Matrix m3 = m1 + m2;
    for (int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++)
        {
            m3[i][j] = m2[i][j] + m1[i][j];
        }
    }
    std::cout << m3 << std::endl; //проверка вывода матрицы
}


bool Test_out_of_range(){
    bool exception = false;
    const size_t rows_1 = 5;
    const size_t cols_1 = 3;
    Matrix m(rows_1, cols_1);
    try {
        m[6][3] = 17;
    }
    catch(out_of_range){
        exception = true; //проверка выброса исключения
    }
    return exception;
}

void Test_copy(){
    const size_t rows = 5;
    const size_t cols = 3;
    Matrix m(rows, cols);
    for (int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++)
        {
            m[i][j] = 1;
        }
    }
    Matrix m_copy = m;
    for (int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            assert(m[i][j] == m_copy[i][j]);
        }
    }
}

void Test_one_dim_matrix(){
    const size_t rows = 1;
    const size_t cols = 1;
    Matrix m1(rows, cols);
    Matrix m2(rows, cols);
    m1[0][0] = 5;
    m2[0][0] = 6;
    Matrix m3 = m1 + m2;
    assert(m3[0][0] == 11);
}

bool Test_Different_Dimensions(){
    bool exception = false;
    Matrix m1(4, 2);
    Matrix m2(2, 4);
    try{
        Matrix m3 = m1 + m2;
    } catch(out_of_range){
        exception = true;
    }
    return exception;
}

bool Test_out_of_range2(){
    bool exception = false;
    const size_t rows_1 = 5;
    const size_t cols_1 = 3;
    Matrix m(rows_1, cols_1);
    try {
        m[3][8] = 17;
    }
    catch(out_of_range){
        exception = true; //проверка выброса исключения
    }
    return exception;
}

int main(int argc, const char * argv[]) {
    Test_size();
    Test_input_multiplication();
    Test_output();
    Test_copy();
    Test_one_dim_matrix();
    bool exception1 = Test_out_of_range();
    bool exception2 = Test_Different_Dimensions();
    bool exception3 =  Test_out_of_range2();
    if ((exception1 == true) and (exception2 == true) and (exception3 == true)){
        cout << "Okey" << endl;
    } else {
        cout << "Not Okey" << endl;
    }
    return 0;
}

