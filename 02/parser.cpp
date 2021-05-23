#include <iostream>
#include "parser.h"
using namespace std;

TokenParser::TokenParser(){
    start_Callback = nullptr;
    end_Callback = nullptr;
    digit_Callback = nullptr;
    string_Callback = nullptr;
}

TokenParser:: ~TokenParser(){}

void TokenParser::SetStartCallback(const StartEnd & start){
    start_Callback = start;
}

void TokenParser::SetEndCallback(const StartEnd & end){
    end_Callback = end;
}

void TokenParser::SetDigitTokenCallback(const Digit & digit){
    digit_Callback = digit;
}

void TokenParser::SetStringTokenCallback(const Str & string){
    string_Callback = string;
}

void TokenParser::Function_For_Token(string &temp_text, bool digit_vs_str, vector<string> &output){
    if (digit_vs_str) {
        if(digit_Callback != nullptr){
            output.push_back(digit_Callback(stoull(temp_text)));
        }
    } else {
        if(string_Callback != nullptr){
            output.push_back(string_Callback(temp_text));
        }
    }
}

vector<string> TokenParser::parser(const string & text){
    vector<string> output;
    bool digit_vs_str = true;
    string temp_text = "";
    if (start_Callback != nullptr){
        output.push_back(start_Callback());
    }
    int c;
    for (int i = 0; i < text.length(); ++i){
        c = text[i];
        if (!isspace(c)){
            if (!isdigit(c)){
                digit_vs_str = false;
            }
            temp_text += c;
        } else {
            if (!temp_text.empty()){
                if (digit_vs_str){
                    try{
                        stoull(temp_text);
                    } catch(out_of_range){
                        digit_vs_str = false;
                    }
                }
                Function_For_Token(temp_text, digit_vs_str, output);
                temp_text.clear();
                digit_vs_str = true;
            }
        }
    }
    if (!temp_text.empty()){
        Function_For_Token(temp_text, digit_vs_str, output);
    }
    if (end_Callback != nullptr){
        output.push_back(end_Callback());
    }
    return output;
}




