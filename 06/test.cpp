#include"Format.h"
#include <iostream>


void Correct_Tests(){
    auto text1 = format("{1}+{1} = {0}", 2, "one");
    assert(text1 == "one+one = 2");
    auto text2 = format("hello {0}", "world");
    assert(text2 == "hello world");
    auto text3 = format("{5},{4},{3},{2},{1},{0}", 0,1,2,3,4,5);
    assert(text3 == "5,4,3,2,1,0");
    auto text4 = format(""); //пустая строка
    assert(text4 == "");
    auto text5 = format("{0}", "hello"); // случай единичного аргумента
    assert(text5 == "hello");
    auto text6 = format("{0}{1}{2}", "hello",", ","world"); //аргументы подряд
    assert(text6 == "hello, world");
    auto text7 = format("{0}{1}{2}{0}{1}{2}{0}{1}{2}{0}{1}{2}", "one ","two ","three ");
    assert(text7 == "one two three one two three one two three one two three ");
    auto text8 = format("x1{0}x2{1}x3", "|","&");
    assert(text8 == "x1|x2&x3");
    auto text9 = format("[1]+{0}={1}","one", "two");
    assert(text9 == "[1]+one=two");
}

void Incorrect_Tests(){
    try{
        auto text = format("{0} {1} {2}", 0, 1);
        throw 1;
    }catch(MyException1 &exception) {
        string s = exception.getError();
        assert(s == "insufficient number of arguments");
    }
    try{
        auto text = format("{0} {one} {2}", 0, 1, 2);
        throw 1;
    }catch(MyException2 &exception) {
        string s = exception.getError();
        assert(s == "error in {}");
    }
    try{
        auto text = format("w}{1}+{1} = {0}", 2, "one");
        throw 1;
    }catch(MyException2 &exception) {
        string s = exception.getError();
        assert(s == "unbalanced brackets");
    }
    try{
        auto text = format("{1}+{1} = {0", 2, "one");
        throw 1;
    }catch(MyException2 &exception) {
        string s = exception.getError();
        assert(s == "unbalanced brackets");
    }
    try{
        auto text = format("no_args", 1) ;
        throw 1;
    }catch(MyException1 &exception) {
        string s = exception.getError();
        assert(s == "extra arguments");
    }
    try{
        auto text = format("{0}{hello{0}}", 1); //ошибка в скобках
        throw 1;
    }catch(MyException2 &exception) {
        string s = exception.getError();
        assert(s == "error in {}");
    }
    try{
        auto text = format("{}{}{}"); //только скобки
        throw 1;
    }catch(MyException2 &exception) {
        string s = exception.getError();
        assert(s == "empty {}");
    }
    try{
        auto text = format("{0}+{0}={}","one"); //отсутствие числа в {}
        throw 1;
    }catch(MyException2 &exception) {
        string s = exception.getError();
        assert(s == "empty {}");
    }
    try{
        auto text = format("{0}+{0}={one}","one", "two"); //строка в {}
        throw 1;
    }catch(MyException2 &exception) {
        string s = exception.getError();
        assert(s == "error in {}");
    }
    try{
        auto text = format("{0}+{0}={214748364800}","one", "two"); //большое число
        throw 1;
    }catch(MyException2 &exception) {
        string s = exception.getError();
        assert(s == "error in {}");
    }
    try{
        auto text = format("{0}+{0}={1str}","one", "two"); //смешанная строка
        throw 1;
    }catch(MyException2 &exception) {
        string s = exception.getError();
        assert(s == "error in {}");
    }
    try{
        auto text = format("{{0}}+{0}={1}","one", "two");
        throw 1;
    }catch(MyException2 &exception) {
        string s = exception.getError();
        assert(s == "error in {}");
    }
}

int main(int argc, const char * argv[]) {
    Correct_Tests();
    Incorrect_Tests();
    cout<<"OK"<<"\n";
    return 0;
}
