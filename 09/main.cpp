#include "sort.h"

int main(){
    try{
        create_file();
    }catch(const std::runtime_error &err){
        std::cerr << err.what() << std::endl;
        return 1;
    }
    try{
        sort();
    }catch(const std::runtime_error &err){
        std::cerr << err.what() << std::endl;
        return 1;
    }
    check();
    return 0;
}

