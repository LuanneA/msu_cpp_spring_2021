#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class MyException{
private:
    std::string m_error;
public:
    MyException(std::string error){
        m_error = error;
    }
    const char* getError() { return m_error.c_str(); }
};

template <class T>
string to_string(T &&s){
    stringstream st;
    st << s;
    return st.str();
}

template<class... Args>
std::string format(const string &str, Args &&... args) {
    string result;
    vector<string> vec = {to_string(forward<Args>(args))...};
    int i = 0;
    bool inside = false;
    string index = "";
    while(i < str.length()){
        if (not inside){
            while (str[i] != '{'){
                if (str[i] == '}'){
                    throw MyException("unbalanced brackets");
                }
                result += str[i];
                i++;
            }
            if (i >= str.length()){
                break;
            }
            inside = true;
        } else {
            if (isdigit(str[i])){
                index += str[i];
            } else {
                if(str[i] == '}'){
                    if (index.length() > 0){
                        int j = atoi(index.c_str());
                        if (j >= vec.size()){
                            throw MyException("insufficient number of arguments");
                        }
                        result += vec[j];
                    }
                    inside = false;
                    index = "";
                } else {
                    throw MyException("error in {}");
                }
            }
        }
        i++;
    }
    return result;
}
