#include <iostream>
#include <sstream>
#include "serializer.h"
using namespace std;

struct Data01{
    uint64_t a;

    template <class Serializer>
    Error serialize(Serializer& serializer){
        return serializer(a);
    }

    template <class Deserializer>
    Error deserialize(Deserializer & deserializer){
        return deserializer(a);
    }
};

struct Data10{
    bool a;

    template <class Serializer>
    Error serialize(Serializer& serializer){
        return serializer(a);
    }

    template <class Deserializer>
    Error deserialize(Deserializer & deserializer){
        return deserializer(a);
    }
};


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

void TestOneInt(){
    Data01 x {17};
    stringstream stream;
    Serializer serializer(stream);
    const Error er =serializer.save(x);
    assert(er == Error::NoError);
    Data01 y {1};
    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);
    assert(err == Error::NoError);
    assert(x.a == y.a);
    assert(x.a == 17);
}

void TestOneBool(){
    Data10 x {true};
    stringstream stream;
    Serializer serializer(stream);
    const Error er =serializer.save(x);
    assert(er == Error::NoError);
    Data10 y {false};
    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);
    assert(err == Error::NoError);
    assert(x.a == y.a);
    assert(x.a == true);
}

void TestSaveLoad(){
    Data x { 1, true, 2 };
    stringstream stream;
    Serializer serializer(stream);
    const Error er =serializer.save(x);
    assert(er == Error::NoError);
    Data y { 0, false, 0 };
    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);
    assert(err == Error::NoError);
    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);
    assert(x.a == 1);
    assert(x.b == true);
    assert(x.c == 2);
}


void TestSave(){
    Data2 x { 1, true, 2 , false, 3};
    stringstream stream;
    Serializer serializer(stream);
    const Error er = serializer.save(x);
    assert(er == Error::NoError);
    assert(stream.str() == "1 true 2 false 3");
}

void TestLoad(){
    Data2 x;
    stringstream stream( "1 true 2 false 3");
    Deserializer deserializer(stream);
    const Error er = deserializer.load(x);
    assert(er == Error::NoError);
    assert(x.a == 1);
    assert(x.b == true);
    assert(x.c == 2);
    assert(x.d == false);
    assert(x.e == 3);
}

void TestLoadNotEnoughData(){
    Data2 x;
    stringstream stream( "1 true 2");
    Deserializer deserializer(stream);
    const Error err = deserializer.load(x);
    assert(err == Error::CorruptedArchive);
}

void TestLoadMoreData(){
    Data x;
    stringstream stream( "1 true 2 5");
    Deserializer deserializer(stream);
    const Error err = deserializer.load(x);
    assert(err == Error::CorruptedArchive);
}

void TestErrorAmount(){
    Data x { 1, true, 2 };
    stringstream stream;
    Serializer serializer(stream);
    serializer.save(x);
    Data2 y { 0, false, 0, true, 5};
    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);
    assert(err == Error::CorruptedArchive);
}

void TestErrorDataType(){
    Data3 y { 0, false, 0, "hello"};
    stringstream stream;
    Serializer serializer(stream);
    Error err = serializer.save(y);
    assert(err == Error::CorruptedArchive);
}

void TestErrorDataType2(){
    Data x { 0, false, 0};
    stringstream stream;
    Serializer serializer(stream);
    const Error er = serializer.save(x);
    assert(er == Error::NoError);
    stream << ' ' << false << ' ' << "hello";
    Deserializer deserializer(stream);
    Data2 y { 0, false, 0, true, 5};
    const Error err2 = deserializer.load(y);
    assert(err2 == Error::CorruptedArchive);
}

void CorrectTestBool(){
    Data x{ 0, 1, 0 };
    stringstream stream;
    Serializer serializer(stream);
    const Error er = serializer.save(x);
    assert(er == Error::NoError);
    assert(stream.str() == "0 true 0");
}


void IncorrectTestBigInt(){
    Data x;
    stringstream stream("0 true 18446744073709551616");
    Deserializer serializer(stream);
    const Error er = serializer.load(x);
    assert(er == Error::CorruptedArchive);
}

void IncorrectTestStr(){
    Data x;
    stringstream stream("42str true 17");
    Deserializer serializer(stream);
    const Error er = serializer.load(x);
    assert(er == Error::CorruptedArchive);
}


int main(int argc, const char * argv[]) {
    TestSaveLoad();
    TestErrorAmount();
    TestErrorDataType();
    TestErrorDataType2();
    TestSave();
    TestLoad();
    TestLoadNotEnoughData();
    TestLoadMoreData();
    TestOneInt();
    TestOneBool();
    CorrectTestBool();
    IncorrectTestBigInt();
    IncorrectTestStr();
    
    cout << "OK" << endl;

    return 0;
}


