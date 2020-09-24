#pragma once

#include <cstring>
#include <stack>

#include "_defines.h"

namespace Warlokbytes {
    class ByteStack {
    private:
        std::vector<byte> data;

    public: 
        void Push(byte val) {
            data.push_back(val);
        }

        byte Pop() {
            byte val = data.back();
            data.pop_back();
            return val;
        }

        byte Peek() {
            return data.back();
        }

        ByteStack(std::size_t size) : data(size) {}
    };
}