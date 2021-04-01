#include <iostream>
#include <functional>
#include <vector>
#include "parser.h"
using namespace std;

string Start(){
    return "Begin";
}

string End(){
    return "End";
}

string Digit1(int digit){
    return to_string(digit);
}

string Digit_square(int digit){
    return to_string(digit*digit);
}

string Str1(const string & str){
    return str;
}

string Str_double(const string & str){
    return str + str;
}

void defaultWorkTest(){
    TokenParser parserFirst;
    parserFirst.SetStartCallback(Start);
    parserFirst.SetEndCallback(End);
    parserFirst.SetDigitTokenCallback(Digit1);
    parserFirst.SetStringTokenCallback(Str1);
    string s = "first april  \t\nhello 7\r  10";
    vector<string> myVector = parserFirst.parser(s);
    //for(int i = 0; i < myVector.size(); i++)
     //   cout << myVector[i] << ' ';
    const std::vector<std::string> tokens =
    {"Begin", "first", "april", "hello", "7","10", "End"};
    assert(myVector == tokens);
}

void emptyTest(){
    TokenParser parserZero;
    string s = "";
    vector<string> myVector = parserZero.parser(s);
    const std::vector<std::string> tokens{};
    assert(myVector == tokens);
}

void anotherWorkTest(){
    TokenParser parserSecond;
    parserSecond.SetStartCallback(Start);
    parserSecond.SetEndCallback(End);
    parserSecond.SetDigitTokenCallback(Digit_square);
    parserSecond.SetStringTokenCallback(Str_double);
    string s = "first april  \t\nhello 7\r  10";
    vector<string> myVector = parserSecond.parser(s);
    //for(int i = 0; i < myVector.size(); i++)
    //    cout << myVector[i] << ' ';
    const std::vector<std::string> tokens =
    {"Begin", "firstfirst", "aprilapril", "hellohello", "49","100", "End"};
    assert(myVector == tokens);
}

int main(){
    defaultWorkTest();
    emptyTest();
    anotherWorkTest();
    cout << "OK"<< '\n';
    return 0;
}

