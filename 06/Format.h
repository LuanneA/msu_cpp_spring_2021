#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class MyException1: public out_of_range{
private:
    std::string m_error;
public:
    explicit MyException1(const string &error):
        out_of_range(error), m_error(error){}
    const char* getError() { return m_error.c_str(); }
};

class MyException2: public logic_error{
private:
    std::string m_error;
public:
    explicit MyException2(const string &error):
        logic_error(error), m_error(error){}
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
    vector<int> vec1(vec.size(), 0);
    int i = 0;
    int count_arg = 0;
    bool inside = false;
    string index = "";
    while(i < str.length()){
        if (not inside){
            while (str[i] != '{'){
                if (str[i] == '}'){
                    throw MyException2("unbalanced brackets");
                }
                result += str[i];
                i++;
                if (i >= str.length()){
                    break;
                }
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
                        int j;
                        try{
                            j = stoi(index.c_str());
                        } catch(const out_of_range & e) {
                            throw MyException2("error in {}");
                        }
                        if (j >= vec.size()){
                            throw MyException1("insufficient number of arguments");
                        }
                        vec1[j] = 1;
                        result += vec[j];
                    } else {
                        throw MyException2("empty {}");
                    }
                    inside = false;
                    index = "";
                } else {
                    throw MyException2("error in {}");
                }
            }
        }
        i++;
    }
    if (index != ""){
        throw MyException2("unbalanced brackets");
    }
    if (find(vec1.begin(), vec1.end(),0) != vec1.end()){
        throw MyException1("extra arguments");
    }
    return result;
}
