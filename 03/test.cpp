#include <iostream>
#include "matrix.h"
using namespace std;


void Test1(){
    const size_t rows = 5;
    const size_t cols = 3;

    Matrix m(rows, cols);

    assert(m.getRows() == 5);
    assert(m.getColumns() == 3);
}

void Test2(){
    const size_t rows = 5;
    const size_t cols = 3;

    Matrix m(rows, cols);
    for (int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++)
        {
            m[i][j] = i + j;
        }
    }
    assert(m[4][1] == 5);
    m *= 3;
    assert(m[4][1] == 15);
}

void Test3(){
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
    std::cout << m3 << std::endl; //проверка вывода матрицы
}


bool Test4(){
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

void Test5(){
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

int main(int argc, const char * argv[]) {
    Test1();
    Test2();
    Test3();
    Test5();
    bool exception = Test4();
    if (exception == true){
        cout << "Okey" << endl;
    } else {
        cout << "Not Okey" << endl;
    }
    return 0;
}

