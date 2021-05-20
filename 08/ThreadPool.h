#pragma once
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <functional>
#include <future>

using namespace std;

class ThreadPool{
private:
    bool available;
    vector<thread> threads;
    queue<function<void()>> task_queue;
    mutex mut;
    condition_variable v;
    
public:
    void process(){
        while(available) {
            unique_lock<mutex> lock(mut);
            if(!task_queue.empty()) {
                auto task = move(task_queue.front());
                task_queue.pop();
                lock.unlock();
                task();
            } else {
                v.wait(lock);
            }
        }
    }
    
    explicit ThreadPool(size_t poolSize){
        available = true;
        for(int i = 0; i < poolSize; i++){
            threads.push_back(thread([this](){process();}));
        }
    }
    
    ~ThreadPool() {
        available = false;
        v.notify_all();
        for(auto &i: threads){
            i.join();
        }
    }
    
    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> future<decltype(func(args...))>{
        auto task = std::make_shared<packaged_task<decltype(func(args...))()> >([func, args...](){
            return func(args...);
        });
        unique_lock<mutex> lock(mut);
        task_queue.push([task]() { (*task)(); });
        v.notify_one();
        return task->get_future();
    }
};
