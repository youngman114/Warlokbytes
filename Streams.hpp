#include <iostream>

template < typename T >
void Print(T object, bool flush = false) {
    std::cout << object;
    if(flush) std::cout << std::endl;
}

template < typename T >
void Log(T object, bool flush = true) {
    std::clog << object;
    if(flush) std::clog << std::endl;   
}

template < typename T >
void Error(T object, bool flush = true) {
    std::cerr << object;
    if(flush) std::cerr << std::endl;
}