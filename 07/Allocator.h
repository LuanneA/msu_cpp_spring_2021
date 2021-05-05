#pragma once
#include <iostream>
#include <sstream>
using namespace std;

template <class T>
struct Allocator{
  typedef T value_type;
  Allocator () = default;
  
  T* allocate(size_t n) {
      if (n > numeric_limits<std::size_t>::max() / sizeof(T))
          throw std::bad_array_new_length();
      if (auto p = static_cast<T*>(std::malloc(n*sizeof(T)))) {
          return p;
      }
      throw bad_alloc();
  }
 
  void deallocate(T* p, std::size_t n) noexcept {
        free(p);
  }
    
  template <class... Args>
  void construct(T* p, Args&&... args){
      new(p) T(forward<Args>(args)...);
  }

  void destroy(T* p){
      p->~T();
  }
};


