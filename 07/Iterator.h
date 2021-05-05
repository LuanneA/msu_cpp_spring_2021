#pragma once
#include <iostream>
#include <sstream>
using namespace std;

template <class T>
class Iterator : public std::iterator<std::forward_iterator_tag, T>{
    T* current_;

public:
    explicit Iterator(T* cur){
        current_ = cur;
    }

    bool operator==(const Iterator<T>& other) const{
        return current_ == other.current_;
    }

    bool operator!=(const Iterator<T>& other) const{
        return !(*this == other);
    }
    
    bool operator<(const Iterator<T>& other) const {
           return current_ < other.current_;
    }

    bool operator>(const Iterator<T>& other) const {
        return other < *this;
    }

    bool operator>=(const Iterator<T>& other) const {
        return !(*this < other);
    }

    bool operator<=(const Iterator<T>& other) const {
        return !(*this > other);
    }
    

    Iterator<T>& operator++(){
        current_ ++;
        return *this;
    }
    
    Iterator<T>& operator--(){
        current_ --;
        return *this;
    }
    
    Iterator<T> operator+(size_t n) const{
           return Iterator(current_ + n);
       }
    
    Iterator<T> operator-(size_t n) const{
           return Iterator(current_ - n);
    }
    
    T& operator*() const {
        return *current_;
    }
    
    Iterator<T>& operator+=(size_t n){
        current_ += n;
        return *this;
    }

    Iterator<T>& operator-=(size_t n){
        current_ -= n;
        return *this;
    }
    
    T& operator[](int n) const{
           return current_[n];
    }
};
