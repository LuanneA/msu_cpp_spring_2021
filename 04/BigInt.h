#pragma once
#include <iostream>
using namespace std;

class BigInt{
    private:
        char * big_integer;
        bool sign = 0;
        size_t integer_size;
    public:
        BigInt();
        BigInt(const string &s);
        BigInt(int32_t a);
        BigInt(const BigInt & other);
        ~BigInt();
        BigInt(BigInt && other);
        BigInt& operator=(int32_t a);
        BigInt& operator=(const BigInt& other);
        friend ostream &operator<<(ostream& out, const BigInt& s);
        friend BigInt operator+(const BigInt& a, const BigInt& b);
        BigInt operator-()const;
        BigInt & operator =(BigInt && other);
        friend BigInt operator +(const BigInt a, const int32_t b) ;
        friend BigInt operator -(const BigInt a, const int32_t b);
        friend BigInt operator *(const BigInt a, const int32_t b);
        friend BigInt operator -(const BigInt& a, const BigInt& b);
        bool operator ==(const BigInt & other) const;
        bool operator !=(const BigInt & other) const;
        bool operator <(const BigInt & other) const;
        bool operator >=(const BigInt & other) const;
        bool operator <=(const BigInt & other) const;
        bool operator >(const BigInt & other) const;
        friend BigInt operator *(const BigInt & a, const BigInt & b);
};
