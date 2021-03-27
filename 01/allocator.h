#include <iostream>
#pragma once

class Allocator
{
private:
    char *ptr;
    size_t offset;
    size_t size_alloc;
    bool ind;
public:
    Allocator ();
    ~Allocator ();

    void makeAllocator(size_t maxSize);

    char* alloc(size_t size);

    void reset();
};


