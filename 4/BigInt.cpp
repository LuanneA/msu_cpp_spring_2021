#include <iostream>
#include "BigInt.h"
using namespace std;


BigInt:: BigInt(){
    big_integer = nullptr;
    integer_size = 0;
}

BigInt:: BigInt(const string &s) {
    unsigned long start = s.find_first_not_of("-");
    string number = s.substr(start);
    integer_size = number.length();
    big_integer = new char[integer_size];
    strcpy(big_integer, number.c_str());
    if (s[0] == '-'){
        sign = 1;
    }
}

BigInt::BigInt(int32_t a){
    string s = to_string(a);
    if (a < 0){
        sign = 1;
        big_integer =  strdup(&s.c_str()[1]);
        integer_size = s.length()-1;
    } else {
        sign = 0;
        big_integer =  strdup(s.c_str());
        integer_size = s.length();
    }
}

BigInt::BigInt(const BigInt & other){
    sign = other.sign;
    integer_size = other.integer_size;
    big_integer = new char[integer_size];
    for (int i = 0; i < integer_size; i++)
    {
        big_integer[i] = other.big_integer[i];
    }
}

BigInt::BigInt(BigInt && other){
    big_integer = other.big_integer;
    integer_size = move(other.integer_size);
    sign = move(other.sign);
    other.big_integer = nullptr;
    other.integer_size = 0;
    other.sign = 0;
}

BigInt & BigInt::operator =(BigInt && other){
    if(this == &other)
    {
        return *this;
    }
    integer_size = move(other.integer_size);
    big_integer = other.big_integer;
    sign = move(other.sign);
    other.big_integer = nullptr;
    other.integer_size = 0;
    other.sign = 0;
    return * this;
}

BigInt& BigInt::operator=(int32_t a){
    return *new BigInt(a);
}

BigInt& BigInt::operator=(const BigInt& other){
    char * number = new char[other.integer_size];
    delete [] big_integer;
    big_integer = number;
    for (int i = 0; i < other.integer_size; i++){
        big_integer[i] = other.big_integer[i];
    }
    sign = other.sign;
    integer_size = other.integer_size;
    return *this;
}

ostream& operator<<(std::ostream& out, const BigInt& s){
    if (s.sign){
        out << "-";
    }
    for (int j = 0; j < s.integer_size; j++){
        out << s.big_integer[j];
    }
    out << endl;
    return out;
}

BigInt operator+(const BigInt& a, const BigInt& b){
    // a < 0, b>
    if (a.sign == 1 && b.sign == 0){
        return b - (-a);
    }
    if (a.sign == 0 && b.sign == 1){
        return a - (-b);
    }
    //a >= 0, b >= 0
    char *A = nullptr;
    char *B = nullptr;
    int new_size = 0;
    if (a.integer_size == b.integer_size){
        A = a.big_integer;
        B = b.big_integer;
        new_size = int(a.integer_size);
    }
    if (a.integer_size > b.integer_size){
        A = a.big_integer;
        B = new char[a.integer_size];
        for (int i = 0; i < a.integer_size - b.integer_size; i ++){
            B[i] = '0';
        }
        for (size_t i = a.integer_size - b.integer_size; i < a.integer_size ; i ++){
            B[i] = b.big_integer[i-(a.integer_size - b.integer_size)];
        }
        new_size = int(a.integer_size);
    } else {
        if (a.integer_size < b.integer_size){
            B = new char[b.integer_size];
            B = b.big_integer;
            A = new char[b.integer_size];
            for (int i = 0; i < b.integer_size - a.integer_size; i ++){
                A[i] = '0';
            }
            for (size_t i = b.integer_size - a.integer_size; i < b.integer_size ; i ++){
                A[i] = a.big_integer[i-(b.integer_size - a.integer_size)];
            }
            new_size = int(b.integer_size);
        }
    }
    int rem = 0;
    int x;
    int y;
    char * temp = new char[new_size];
    for (int i = new_size-1; i >= 0; i --){
        x = A[i] - '0';
        y = B[i] - '0';
        temp[i] = (x + y + rem) % 10 + '0';
        rem = (x + y) / 10;
    }
    BigInt result;
    if (rem == 0){
        string s(max(a.integer_size, b.integer_size), '0');
        result = BigInt(s);
        for ( int j = 0; j <= result.integer_size - 1; j++){
            result.big_integer[j] = temp[j];
        }
    } else{
        string s(max(a.integer_size, b.integer_size) + 1, '0');
        result = BigInt(s);
        result.big_integer[0] = '1';
        for ( int j = 0; j < b.integer_size; j++){
            result.big_integer[j+1] = temp[j];
        }
    }
    if (a.sign > 0){
        result.sign = 1;
    } else {
        result.sign = 0;
    }

    return result;
}

BigInt BigInt::operator-() const{
    BigInt result = BigInt(*this);
    result.sign = !result.sign;
    return result;
}

BigInt operator +(const BigInt a, const int32_t b) {
    BigInt temp = BigInt(b);
    return a + temp;
}

BigInt operator -(const BigInt a, const int32_t b) {
    BigInt temp = BigInt(b);
    return a - temp;
}

BigInt operator *(const BigInt a, const int32_t b) {
    BigInt temp = BigInt(b);
    return a * temp;
}

BigInt operator-(const BigInt& a, const BigInt& b){
    if (a.sign == 0 && b.sign == 1){
        return a +(-b);
    }
    if (a.sign == 1 && b.sign == 0){
        return -((-a) +b);
    }
    if(a.sign == 1 && b.sign == 1){
        return a + (-b);
    }
    //a >= 0, b >= 0
    BigInt result;
    if (a < b){
        result = b - a;
        result.sign = 1;
        return result;
    }
    char *A = nullptr;
    char *B = nullptr;
    int new_size = 0;
    if (a.integer_size == b.integer_size){

        new_size = int(a.integer_size);
        A = a.big_integer;
        B = b.big_integer;
    }
    if (a.integer_size > b.integer_size){
        A = a.big_integer;
        B = new char[a.integer_size];
        for (int i = 0; i < a.integer_size - b.integer_size; i ++){
            B[i] = '0';
        }
        for (size_t i = a.integer_size - b.integer_size; i < a.integer_size ; i ++){
            B[i] = b.big_integer[i-(a.integer_size - b.integer_size)];
        }
        new_size = int(a.integer_size);
    } else {
        if (a.integer_size < b.integer_size){
            B = new char[b.integer_size];
            B = b.big_integer;
            A = new char[b.integer_size];
            for (int i = 0; i < b.integer_size - a.integer_size; i ++){
                A[i] = '0';
            }
            for (size_t i = b.integer_size - a.integer_size; i < b.integer_size ; i ++){
                A[i] = a.big_integer[i-(b.integer_size - a.integer_size)];
            }
            new_size = int(b.integer_size);
        }
    }
    int rem = 0;
    int x;
    int y;
    char * temp = new char[new_size];
    for (int i = new_size-1; i >= 0; i --){
        x = A[i] - '0';
        y = B[i] - '0';
        if ( x - y - rem >= 0){
            temp[i] = (x - y - rem) + '0';
            rem = 0;
        } else {
            temp[i] = (10 + x - y - rem) + '0';
            rem = 1;
        }
    }
    if (rem == 0){
        string s(max(a.integer_size, b.integer_size), '0');
        result = BigInt(s);
        for ( int j = 0; j <= result.integer_size - 1; j++){
            result.big_integer[j] = temp[j];
        }
    } else{
        string s(max(a.integer_size, b.integer_size) + 1, '0');
        result = BigInt(s);
        result.big_integer[0] = '1';
        for ( int j = 0; j < b.integer_size; j++){
            result.big_integer[j+1] = temp[j];
        }
    }
    return result;
}

bool BigInt::operator ==(const BigInt & other) const{
    if(integer_size != other.integer_size){
        return false;
    }
    for (int i = 0; i < integer_size; i++){
        if(big_integer[i] != other.big_integer[i]){
            return false;
        }
    }
    return true;
}


bool BigInt::operator !=(const BigInt & other) const{
    return !(*this == other);
}


bool BigInt::operator <(const BigInt & other) const{
    if(*this == other){
        return false;
    }
    if(sign == 1){
        if(other.sign == 1){
            return ((-other) < (-*this));
        } else {
            return true;
        }
    } else
        if(other.sign == 1){
            return false;
    } else {
        if(integer_size != other.integer_size){
            return integer_size < other.integer_size;
        } else {
            for (int i = 0; i <= int(integer_size) - 1; --i){
                if (big_integer[i] != other.big_integer[i]){
                    return big_integer[i] < other.big_integer[i];
                }
            }
            return false;
        }
    }
}


bool BigInt::operator >=(const BigInt & other) const{
    return !(*this < other);
}


bool BigInt::operator <=(const BigInt & other) const{
    return ((*this < other) || (*this == other));
}


bool BigInt::operator >(const BigInt & other) const{
    return !(*this <= other);
}

BigInt::~BigInt(){
    delete[] big_integer;
}

BigInt operator *(const BigInt & a, const BigInt & b){
    int x = 0;
    int y = 0;
    int c = 0;
    int * res = new int [int(a.integer_size + b.integer_size)];
    for (int i = 0; i < int(a.integer_size + b.integer_size); i++){
        res[i] = 0;
    }
    for (int i = 0; i < int(a.integer_size); i++){
        c = 0;
        for (int j = 0; j < int(b.integer_size); j++){
            x = a.big_integer[int(a.integer_size) - i - 1] - '0';
            y = b.big_integer[int(b.integer_size) - j - 1] - '0';
            res[int(b.integer_size) + int(a.integer_size) - (i + j) - 1] += c + x * y;
            c = res[int(b.integer_size) + int(a.integer_size) - (i + j) - 1] / 10;
            res[int(b.integer_size) + int(a.integer_size) - (i + j) - 1] %= 10;
        }
        res[int(a.integer_size) + int(b.integer_size) - (i + int(b.integer_size)) - 1] += c;
    }
    bool flag = 1;
    int j = 0;
    char *res1 = new char[a.integer_size + b.integer_size];
    for (int i = 0; i < int(a.integer_size + b.integer_size); i++){
        if (flag == 0){
            res1[j] = res[i] + '0';
            j ++;
        } else {
            if (res[i] != 0){
                res1[j]= res[i] + '0';
                flag = 0;
                j ++;
            }
        }
    }
    string str (j, '0');
    BigInt result = BigInt(str);
    for (int i = 0; i < j; i++){
        result.big_integer[i] = res1[i];
    }
    result.integer_size = a.integer_size + b.integer_size;
    if (a.sign ^ b.sign){
        result.sign = 1;
    }
    else{
        result.sign = 0;
    }
    result.integer_size --;
    return result;
}
