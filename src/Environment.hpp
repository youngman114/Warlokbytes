#pragma once

#include <map>
#include <string>
#include <vector>
#include <cstring>

#include "_defines.h"

#include "Logger.hpp"

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

    public:
        /// Fetch, decode and execute the next instruction
        void Step() {
            byte fetched = code[++counter];
            if(Environment::instruction operation = this->ops.operator[](fetched)) {
                this->state = operation(this);
            } else { // undefined function, do something!!
                Error("Undefined function ");
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

        Environment(const byte* const code, const std::map<byte, instruction> ops) : code(code), ops(ops) {}
    };
}