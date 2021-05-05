#pragma once
#include <iostream>
#include <sstream>
#include "Allocator.h"
#include "Iterator.h"
using namespace std;

template <class T>
class Vector{
private:
    T* vec;
    size_t size_;
    size_t capacity_;
    Allocator<T> alloc;
public:
    Vector(size_t n = 0){
        size_ = n;
        capacity_ = n;
        vec = alloc.allocate(capacity_);
    }
    ~Vector(){}
    
    T& operator[](size_t t) const{
        if(t > size_)
            throw out_of_range("out_of_range");
        return vec[t];
    }
    
    void push_back(const T& x){
        if (size_ == capacity_){
            reserve(size_ * 2 + 1);
        }
        vec[size_] = x;
        size_ ++;
    }
    
    void push_back(T && x){
        if (size_ == capacity_){
            reserve(2 * capacity_ + 1);
        }
        vec[size_] = move(x);
        size_++;
    }
    
    void pop_back(){
        if( size_ > 0 ){
            size_--;
            alloc.destroy(vec + size_);
        }
    }
    
    template <class... Args>
    void emplace_back(Args&&... args){
        if (size_ == capacity_){
            reserve(2 * capacity_ + 1);
        }
        new (static_cast<void*>(vec + size_)) T(std::forward<Args>(args)...);
        ++size_;
    }
    
    bool empty() const {
        return (size_ == 0);
    }
    
    size_t size() const {
        return size_;
    }
    
    void clear(){
        while (size_ != 0){
            alloc.destroy(vec + size_);
            size_--;
        }
    }
    
    Iterator<T> begin()noexcept{
        return Iterator<T>(vec);
    }
    
    Iterator<T> end()noexcept{
        return Iterator<T>(vec + size_);
    }
    
    reverse_iterator<Iterator<T>> rbegin(){
        return reverse_iterator<Iterator<T>>(end());
    }

    reverse_iterator<Iterator<T>> rend(){
        return reverse_iterator<Iterator<T>>(begin());
    }
    
    void resize(size_t n){
        if (n < size_){
            size_ --;
            while (size_ != n){
                alloc.destroy(vec + size_);
                size_ --;
            }
        } else {
            if(n >= capacity_)
                this->reserve(n);
            while(size_ != n){
                alloc.construct(vec + size_);
                size_ ++;
            }
        }
        return;
    }
    
    void reserve(size_t n){
        if (n <= size_)
            return;
        T* temp = alloc.allocate(n);
        for (size_t i = 0; i < size_; i++){
            temp[i] = move(vec[i]);
        }
        alloc.deallocate(vec, capacity_);
        vec = temp;
        capacity_ = n;
    }
    
    size_t capacity(){
        return capacity_;
    }
    
};
