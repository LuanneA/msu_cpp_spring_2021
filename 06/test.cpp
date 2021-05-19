#include"Format.h"
#include <iostream>


void Correct_Tests(){
    auto text1 = format("{1}+{1} = {0}", 2, "one");
    assert(text1 == "one+one = 2");
    auto text2 = format("hello {0}", "world");
    assert(text2 == "hello world");
    auto text3 = format("{5},{4},{3},{2},{1},{0}", 0,1,2,3,4,5);
    assert(text3 == "5,4,3,2,1,0");
    auto text4 = format("{5} + {5} = {10}", 0,1,2,3,4,"five",6,7,8,9,"ten");
    assert(text4 == "five + five = ten");
}

void Incorrect_Tests(){
    try{
        auto text = format("{0} {1} {2}", 0, 1);
    }catch(MyException &exception) {
        string s = exception.getError();
        assert(s == "insufficient number of arguments");
    }
    try{
        auto text = format("{0} {one} {2}", 0, 1, 2);
    }catch(MyException &exception) {
        string s = exception.getError();
        assert(s == "error in {}");
    }
    try{
        auto text = format("w}{1}+{1} = {0}", 2, "one");
    }catch(MyException &exception) {
        string s = exception.getError();
        assert(s == "unbalanced brackets");
    }
    try{
        auto text = format("{1}+{1} = {0", 2, "one");
    }catch(MyException &exception) {
        string s = exception.getError();
        assert(s == "unbalanced brackets");
    }
}

int main(int argc, const char * argv[]) {
    Correct_Tests();
    Incorrect_Tests();
    cout<<"OK"<<"\n";
    return 0;
}
