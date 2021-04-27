#include <iostream>
#include <sstream>
#include "Serializer.h"
using namespace std;

struct Data{
    uint64_t a;
    bool b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer){
        return serializer(a, b, c);
    }

    template <class Deserializer>
    Error deserialize(Deserializer & deserializer){
        return deserializer(a, b, c);
    }
};

struct Data2{
    uint64_t a;
    bool b;
    uint64_t c;
    bool d;
    uint64_t e;

    template <class Serializer>
    Error serialize(Serializer& serializer){
        return serializer(a, b, c, d, e);
    }

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer){
        return deserializer(a, b, c, d, e);
    }
};

struct Data3{
    uint64_t a;
    bool b;
    uint64_t c;
    string d;

    template <class Serializer>
    Error serialize(Serializer& serializer){
        return serializer(a, b, c, d);
    }

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer){
        return deserializer(a, b, c, d);
    }
};

void Test1(){
    Data x { 1, true, 2 };
    stringstream stream;
    Serializer serializer(stream);
    serializer.save(x);
    Data y { 0, false, 0 };
    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);
    assert(err == Error::NoError);
    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);
}

void Test2(){
    Data x { 1, true, 2 };
    stringstream stream;
    Serializer serializer(stream);
    serializer.save(x);
    Data2 y { 0, false, 0, true, 5};
    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);
    assert(err == Error::CorruptedArchive);
}

void Test3(){
    Data3 y { 0, false, 0, "hello"};
    stringstream stream;
    Serializer serializer(stream);
    Error err = serializer.save(y);
    assert(err == Error::CorruptedArchive);
}

void Test4(){
    Data x { 0, false, 0};
    stringstream stream;
    Serializer serializer(stream);
    serializer.save(x);
    stream << ' ' << false << ' ' << "hello";
    Deserializer deserializer(stream);
    Data2 y { 0, false, 0, true, 5};
    const Error err2 = deserializer.load(y);
    assert(err2 == Error::CorruptedArchive);
}

int main(int argc, const char * argv[]) {

    Test1();
    Test2();
    Test3();
    Test4();

    cout << "OK" << endl;

    return 0;
}


