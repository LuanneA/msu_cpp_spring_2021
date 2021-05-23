#pragma once
#include <iostream>
#include <functional>
#include <vector>
using namespace std;

using StartEnd = function<string()>;
using Digit = function<string(uint64_t)>;
using Str = function<string(const string &)>;

class TokenParser{
private:
    StartEnd start_Callback;
    StartEnd end_Callback;
    Str string_Callback;
    Digit digit_Callback;
public:
    TokenParser();
    void SetStartCallback(const StartEnd & start);
    void SetEndCallback(const StartEnd & end);
    void SetDigitTokenCallback(const Digit & digit);
    void SetStringTokenCallback(const Str & string);
    void Function_For_Token(string &temp_text, bool digit_vs_str, vector<string> &output);
    vector<string> parser(const string & text);
    ~TokenParser();
};
