#include <iostream>
#include "allocator.h"
using namespace std;

void double_makeAllocator(){
    Allocator alloc_new;
    alloc_new.makeAllocator(10);
    char *pointer_new1 = alloc_new.alloc(5);
    assert(pointer_new1 != nullptr);
    alloc_new.makeAllocator(15);
    char *pointer_new2 = alloc_new.alloc(5);
    assert(pointer_new2 != nullptr);
    assert( pointer_new1 != pointer_new2);
}

void alloc_before_make_Allocator(){
    Allocator alloc;
    char *pointer = alloc.alloc(2);
    assert(pointer == nullptr);
}

void alloc_test(){
    Allocator alloc;
    alloc.makeAllocator(10);
    char *pointer1 = alloc.alloc(2);
    char *pointer2 = alloc.alloc(3);
    char *pointer3 = alloc.alloc(5);
    char *pointer4 = alloc.alloc(2);
    assert((pointer1 != nullptr) &&
           (pointer2 != nullptr) &&
           (pointer3 != nullptr) &&
           (pointer4 == nullptr) );

    assert((pointer2 - pointer1 == 2) &&
           (pointer3 - pointer2 == 3));
}

void reset_test(){
    Allocator alloc;
    alloc.makeAllocator(10);
    char *pointer1 = alloc.alloc(2);
    char *pointer2 = alloc.alloc(3);
    alloc.reset();

    pointer1 = alloc.alloc(2);
    pointer2 = alloc.alloc(3);
    char *pointer3 = alloc.alloc(5);
    char *pointer4 = alloc.alloc(2);

    assert((pointer1 != nullptr) &&
            (pointer2 != nullptr) &&
            (pointer3 != nullptr) &&
            (pointer4 == nullptr) );

    assert((pointer2 - pointer1 == 2) &&
            (pointer3 - pointer2 == 3));
}

int main() {
    double_makeAllocator();
    alloc_before_make_Allocator();
    alloc_test();
    reset_test();


    std::cout << "OK" << std::endl;
    return 0;
}



