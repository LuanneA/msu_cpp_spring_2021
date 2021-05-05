#include "Vector.h"
#include <string>
#include <iostream>
using namespace std;

void Test1_operator(){
    Vector <int> vec1;
    vec1.push_back(1);
    vec1.push_back(1);
    vec1.push_back(1);
    vec1.push_back(1);
    vec1[0] = 0;
    vec1[2] = 0;
    assert (vec1.size() == 4);
    for (auto i = 0; i < vec1.size(); i ++){
        assert(vec1[i] == i%2);
    }
}

void Test2_pop_push(){
    Vector <string> vec2;
    vec2.push_back("Hello");
    vec2.push_back("world");
    assert (vec2.size() == 2);
    vec2.pop_back();
    vec2.pop_back();
    assert (vec2.empty() == true);
}

void Test3_clear(){
    Vector <bool> vec3(3);
    vec3[0] = true;
    vec3[1] = false;
    vec3[2] = true;
    vec3.clear();
    assert(vec3.size() == 0);
}

void Test4_begin_end(){
    Vector <float> vec4;
    vec4.push_back(1.2);
    vec4.push_back(0.8);
    vec4.push_back(3.6);
    vec4.push_back(1.4);
    float sum = 0;
    for (auto i = vec4.begin(); i != vec4.end(); ++i){
        sum += *i;
    }
    assert(sum == 7.0);
}

void Test5_rbegin_rend(){
    Vector <char> vec5;
    vec5.push_back('a');
    vec5.push_back('z');
    vec5.push_back('z');
    vec5.push_back('i');
    vec5.push_back('p');
    string answer;
    for (auto i = vec5.rbegin(); i != vec5.rend(); ++i){
        answer += *i;
    }
    assert(answer == "pizza");
}

void Test6_resize_reserve(){
    Vector <int> vec6;
    vec6.reserve(6);
    assert(vec6.capacity() == 6);
    vec6.push_back(6);
    assert(vec6.size() == 1);
    vec6.emplace_back(6);
    assert(vec6.size() == 2);
    vec6.resize(16);
    assert(vec6.size() == 16);
    for (auto i = vec6.begin(); i != vec6.end(); ++i){
        *i = 2;
    }
    vec6.resize(5);
    int s = 0;
    for (auto i = vec6.begin(); i != vec6.end(); ++i){
        s += *i;
    }
    assert(s ==  10);
}

int main(int argc, const char * argv[]) {
    Test1_operator();
    Test2_pop_push();
    Test3_clear();
    Test4_begin_end();
    Test5_rbegin_rend();
    Test6_resize_reserve();
    cout <<"OK" << endl;
    return 0;
}
