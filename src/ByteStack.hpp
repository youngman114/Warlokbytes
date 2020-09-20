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
            this->size = size;
            this->counter = -1;
            data = new byte[size];
        }

        ~ByteStack() {
            for (int i = 0; i < size; i++) {
                delete (byte*)((std::size_t)(data) + i);
            }
        }
    };
}