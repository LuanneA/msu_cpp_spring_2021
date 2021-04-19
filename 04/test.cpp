#include <iostream>
#include "BigInt.h"
using namespace std;

void test_output(){
    cout << "Test1"<<endl;
    BigInt a = 1;
    BigInt b("123456789012345678901234567890");
    BigInt c = b;
    cout << a << endl;
    cout << b << endl;
    cout << c << endl;
}

void test_sum(){
    BigInt a("12080328838282283");
    BigInt b("5");
    BigInt c = 5;
    BigInt ans1("12080328838282288");
    assert ((a + b) == ans1 && (a + c) == ans1);
    BigInt ans2("12080328838282278");
    assert ((a + (-b)) == ans2 && (a + (-c)) == ans2);
}

void test_sub(){
    BigInt a("12080328838282283");
    BigInt b("5");
    BigInt c = 5;
    BigInt ans1("12080328838282278");
    assert ((a - b) == ans1 && (a - c) == ans1);
    BigInt ans2("12080328838282288");
    assert ((a - (-b)) == ans2 && (a - (-c)) == ans2);
    BigInt ans3("-12080328838282278");
    assert ((b - a) == ans3 && (c - a) == ans3);
}

void test_multi(){
    BigInt a("112080000000");
    BigInt b("5");
    BigInt c = 5;
    BigInt ans1("560400000000");
    assert ((a*b) == ans1 && (a*c) == ans1);
    BigInt ans2("-560400000000");
    assert ((a*(-b)) == ans2 && (a*(-c)) == ans2);
}

void test_comp(){
    BigInt a("112080000000000000");
    BigInt b("5");
    assert ((a > b) == true && (a <= b) == false);
    BigInt c("64648494490000000");
    BigInt d("10000000000000000");
    assert ((d < c) == true);
}

void test_copy(){
    BigInt a("112080000000000000");
    BigInt b(a);
    BigInt c = a;
}

BigInt Create(const string s){
    BigInt ret(s);
    return ret;
}

void test_move(){
    BigInt a("112080000000000000");
    BigInt b = Create("112080000000000000");
    a = Create("112080000000000000");
}

int main(int argc, const char * argv[]){
    test_output();
    test_sum();
    test_sub();
    test_multi();
    test_comp();
    test_copy();
    test_move();
    return 0;
}

