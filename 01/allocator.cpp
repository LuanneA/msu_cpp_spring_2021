#include <iostream>
#include "allocator.h"



Allocator::Allocator (){
    ptr = nullptr;
    offset = 0;
    size_alloc = 0;
}

Allocator::~Allocator (){
    delete [] ptr;
}

void Allocator::makeAllocator(size_t maxSize){
    ptr = nullptr;
    ptr = new char[maxSize];
    offset = 0;
    size_alloc = maxSize;
}

char* Allocator::alloc(size_t size){
    if (offset + size > size_alloc || ptr == nullptr)
        return nullptr;
    char* pointer = ptr + offset;
    offset += size;
    return pointer;
}

void Allocator::reset(){
    offset = 0;
}



