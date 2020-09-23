#pragma once

#include <map>
#include <string>
#include <vector>
#include <cstring>

#include "_defines.h"

#include "Logger.hpp"
#include "ByteStack.hpp"

namespace Warlokbytes {
    typedef class Environment;
    typedef byte(*instruction)(Environment* env);

    struct Instruction
    {
        friend Environment;

    public:
        instruction op;

        Instruction() {}
        Instruction(instruction op) : op(op) {}
    };

    /**
     * @brief Object for executing bytecodes
     */
    class Environment {
        friend Instruction;
        friend instruction;

    private:
        /// Displays code counter
        unsigned long long counter = -1;
        /// All the executable code
        mutable byte const* code = nullptr;
        /// Is machine currently running? 
        bool isRunning = true;
        /// Instructions and their method
        std::map<byte, Instruction> ops = {};
        /// State based on the last operation
        byte state = 0;
        // Bitwise stack
        ByteStack bstack = 0;

    public:
        /// Fetch, decode and execute the next instruction
        void Step() {
            byte fetched = code[++counter];
            if(ops.find(fetched) != ops.end()) { // Found
                this->state = ops[fetched].op(this);
            } else { // Function not found
                Error("Undefined function 0x", false);
                Error(std::hex, false);
                Error((int)fetched);
                Halt(); 
            }
        }
        
        Environment(const std::initializer_list<byte> code, const std::map<byte, Instruction> ops)  {
            memcpy((void*)this->code, code.begin(), code.size());
            this->ops = ops;
        }

        /// Set isRunning to "false"
        void Halt() {
            this->isRunning = false;
        }

        /// Check virtual environment state
        const bool& IsRunning() const {
            return this->isRunning;
        }

        ByteStack& GetByteStack() {
            return this->bstack;
        }

        const byte GetState() const {
            return this->state;
        }

        const byte* const & GetCode() {
            return this->code;
        }

        unsigned long long& GetCounter() {
            return this->counter;
        }

        Environment(const byte* const code, const std::map<byte, Instruction> ops, std::size_t stackSize) : code(code), ops(ops), bstack(stackSize) {}
        Environment(const Environment& other) = delete;
        Environment& operator=(const Environment& other) = delete;
    };
}