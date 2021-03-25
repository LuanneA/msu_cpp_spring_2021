#include <iostream>

using namespace std;

class Allocator
{
private:
    char *ptr = nullptr;
    size_t offset;
    size_t size_alloc;
public:
    Allocator (){
        ptr = nullptr;
        offset = 0;
        size_alloc = 0;
    }

    ~Allocator (){
        delete [] ptr;
    }

    void makeAllocator(size_t maxSize){
        if (ptr != nullptr){
            delete [] ptr;
            ptr = nullptr;
            offset = 0;
            size_alloc = 0;
        }
        ptr = new char[maxSize];
        offset = 0;
        size_alloc = maxSize;
    }

    char* alloc(size_t size){
        if (offset + size > size_alloc || ptr == nullptr)
               return nullptr;
        char* pointer = ptr + offset;
        offset += size;
        return pointer;
    }

    void reset(){
        offset = 0;
    }
};

int main() {
    Allocator alloc;
    alloc.makeAllocator(10);
    char *pointer1 = alloc.alloc(2);
    char *pointer2 = alloc.alloc(3);
    char *pointer3 = alloc.alloc(5);
    char *pointer4 = alloc.alloc(2);
    assert( (pointer1 != nullptr) &&
        (pointer2 != nullptr) &&
            (pointer3 != nullptr) &&
                (pointer4 == nullptr) );

    assert( (pointer2 - pointer1  == 2) &&
           (pointer3 - pointer2 == 3));

    alloc.reset();

    pointer1 = alloc.alloc(2);
    pointer2 = alloc.alloc(3);
    pointer3 = alloc.alloc(5);
    pointer4 = alloc.alloc(2);

    assert( (pointer1 != nullptr) &&
            (pointer2 != nullptr) &&
            (pointer3 != nullptr) &&
            (pointer4 == nullptr) );

    assert( (pointer2 - pointer1 == 2) &&
            (pointer3 - pointer2 == 3) );

    std::cout << "OK" << std::endl;
    return 0;
}

