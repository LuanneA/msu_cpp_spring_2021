#include "sort.h"

using namespace std;

constexpr size_t SIZE = 1024*1024;
constexpr size_t CHUNK_SIZE = 1024;

void create_file(){
    ofstream f("file", ios::binary | ios::out);
    if (!f){
        throw runtime_error("No such file: file");
    }
    for (int i = 0; i < SIZE; ++i){
        uint64_t num = rand() % 100;
        f.write((char *) &num, sizeof(uint64_t));
    }
    f.close();
}

void merge(vector <string> &names){
    size_t k = names.size();
    for(int i = 1; i < k; i++){
        uint64_t *num = new uint64_t[1];
        uint64_t *buf = new uint64_t[CHUNK_SIZE/2];
        ifstream file1;
        file1.open(names[i],ios::binary| ios::in);
        file1.read((char *)(buf), CHUNK_SIZE/2 * sizeof(uint64_t));
        auto size_read = file1.gcount()/ sizeof(uint64_t);
        file1.close();
        ifstream file2;
        file2.open(names[i-1],ios::binary| ios::in);
        file2.read((char *)(num), sizeof(uint64_t));
        size_t j = 0;

        if(i == k - 1){
            names[i] = "output.bin";
        }
        ofstream res(names[i], ios::binary| ios::out);
        while(!file2.eof() && j<size_read){
            if (num[0]<=buf[j]){
                res.write((char *)(&num[0]), sizeof(uint64_t));
                file2.read((char *)(&num[0]), sizeof(uint64_t));
            } else{
                res.write((char *)(&buf[j]), sizeof(uint64_t));
                j++;
            }
        }
        if(file2.eof()){
            res.write((char *)(&buf[j]), sizeof(uint64_t) * (CHUNK_SIZE/2 - j));
        }
        while(!file2.eof()){
            res.write((char *)(&num[0]), sizeof(uint64_t));
            file2.read((char *)(&num[0]), sizeof(uint64_t));
        }
        file2.close();
        res.close();
        if(i == k - 1){
            names[i] = to_string(k - 1);
        }
        delete[] buf;
        delete[] num;
    }
}

void sort() {
    ifstream f("file", ios::binary | ios::in);
    if (!f){
        throw runtime_error("No such file: file");
    }
    vector<string> names;
    int k;
    uint64_t* buf = new uint64_t [CHUNK_SIZE];
    
    for (k = 0; !f.eof(); ++k){
        f.read((char*)buf, CHUNK_SIZE * sizeof(uint64_t));
        auto size_= f.gcount()/sizeof(uint64_t);
        if(size_ > 0){
            string name1 = to_string(k);
            names.push_back(name1);
            k++;
            string name2 = to_string(k);
            names.push_back(name2);

            thread thread1([buf, size_](){
                sort(buf, buf + size_ / 2 );
            });

            thread thread2([buf, size_](){
                sort(buf + size_ / 2, buf + size_);
            });

            thread1.join();
            thread2.join();
            
            ofstream f1(names[k-1],ios::binary);
            if (!f1){
                throw runtime_error("No such file: " + name2);
            }
            for (size_t i = 0; i < size_ / (2); i++) {
                f1.write((char *)(&buf[i]), sizeof(uint64_t));
            }
            f1.close();
            
            ofstream f2(names[k],ios::binary);
            if (!f2){
                throw runtime_error("No such file: " + name1);
            }
            for (size_t i = size_ / 2; i < size_ ; i++)  {
                f2.write((char *)(&buf[i]), sizeof(uint64_t));
            }
            f2.close();
        }
    }
    delete[] buf;
    f.close();
    merge(names);
    for (size_t i = 0; i < names.size() - 1; ++i) {
        remove(names[i].c_str());
    }
}


void check(){
    ifstream file("output.bin", std::ios::binary);
    if (file){
        file.seekg (0, file.end);
        uint64_t length = file.tellg() / sizeof(uint64_t);
        file.seekg(0, file.beg);
        uint64_t * buffer = new uint64_t [length];
        file.read((char*)buffer, length *sizeof(uint64_t));
        if (is_sorted(buffer, buffer + length)) {
            cout << "Successful sorting" << endl;
        } else {
            cout << "Failed sorting" << endl;
        }
        delete [] buffer;
        file.close();
    } else {
        throw runtime_error("Can't find final file");
    }
}
