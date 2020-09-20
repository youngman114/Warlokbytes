#pragma once

#include <cstring>
#include <stack>

#include "_defines.h"

namespace Warlokbytes {
    class ByteStack {
    private:
        std::size_t size;
        std::size_t counter;
        byte* data = nullptr;

    public: 
        void Push(byte val) {
            data[++counter] = val; 
        }

        byte Pop() {
            return data[counter--];
        }

        byte Peek() {
            return data[counter];
        }

        ByteStack(std::size_t size) {
            data = new byte[size];
        }

        ~ByteStack() {
            delete[] data;
        }
    };
}