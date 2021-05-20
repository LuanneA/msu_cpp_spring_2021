#include "ThreadPool.h"
#include <iostream>

struct A{
    int i = 1;
};

int foo(const A&a) { return a.i; };

int main(int argc, const char * argv[]) {

    ThreadPool pool(8);

    auto task1 = pool.exec(foo, A());
    assert(task1.get() == 1);

    auto task2 = pool.exec([]() { return 1; });
    assert(task2.get() == 1);
    
    for( int i = 0; i < 10; ++i ){
        assert(pool.exec([i](){return i;}).get() == i);
    }
    
    cout << "OK" << endl;
    return 0;
}
