#pragma once

#include <map>
#include <string>
#include <vector>
#include <cstring>

#include "_defines.h"

#include "Logger.hpp"
#include "ByteStack.hpp"

#define INSTRUCTION(OP, CODE) {OP, [](Environment* env) -> byte {CODE; return 0x00;}},
namespace Warlokbytes {
    /**
     * @brief Object for executing bytecodes
     */
    class Environment {
    public:
        typedef byte(*instruction)(Environment* env);

        /// Displays code counter
        unsigned long long counter = -1;
        /// All the executable code
        mutable byte const* code = nullptr;
        /// Is machine currently running? 
        bool isRunning = true;
        /// Instructions and their method
        std::map<byte, instruction> ops = {};
        /// State based on the last operation
        byte state = 0;
        // Bitwise stack
        ByteStack bstack = 0;

        /// Fetch, decode and execute the next instruction
        void Step() {
            byte fetched = code[++counter];
            if(Environment::instruction operation = this->ops.operator[](fetched)) {
                this->state = operation(this);
            } else { // undefined function, do something!!
                Error("Undefined function 0x", false);
                Error(std::hex, false);
                Error((int)fetched);
                Halt(); 
            }
        }
        
        Environment(const std::initializer_list<byte> code, const std::map<byte, instruction> ops)  {
            memcpy((void*)this->code, code.begin(), code.size());
            this->ops = ops;
        }

        /// Set isRunning to "false"
        void Halt() {
            this->isRunning = false;
        }

        /// Check virtual environment state
        bool IsRunning() {
            return this->isRunning;
        }

        Environment(const byte* const code, const std::map<byte, instruction> ops, std::size_t stackSize) : code(code), ops(ops), bstack(stackSize) {}
        Environment(const Environment& other) = delete;
        Environment& operator=(const Environment& other) = delete;
    };
}