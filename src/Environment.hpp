#pragma once

#include <map>
#include <string>
#include <vector>
#include <cstring>
#include <memory>

#include "_defines.h"

#include "Logger.hpp"
#include "FrameStack.hpp"

namespace Warlokbytes {
    typedef class Environment;

    struct Instruction
    {
        friend Environment;

    private:
        typedef byte(*instruction)(Environment* env);

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

    private:
        /// Displays code counter
        unsigned long long counter = -1;
        /// All the executable code
        mutable std::vector<byte> code = {0xFF};
        /// Is machine currently running? 
        bool isRunning = true;
        /// Instructions and their method
        std::map<byte, Instruction> ops = {};
        /// State based on the last operation
        byte state = 0;
        FrameStack callstack = {};



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
        

        /// Set isRunning to "false"
        void Halt() {
            this->isRunning = false;
        }

        /// Check virtual environment state
        const bool& IsRunning() const {
            return this->isRunning;
        }

        FrameStack& GetCallStack() {
            return this->callstack;
        }

        const byte GetState() const {
            return this->state;
        }

        const std::vector<byte>& GetCode() {
            return this->code;
        }

        unsigned long long& GetCounter() {
            return this->counter;
        }

        std::vector<byte> currLocals {GetCallStack().back().locals};
        std::vector<byte> currStack {GetCallStack().back().stack};
        Frame currFrame {GetCallStack().back()};

        Environment(const std::vector<byte> code, const std::map<byte, Instruction> ops) : code(code), ops(ops), callstack(1) {}
        Environment(const std::vector<byte> code, const std::map<byte, Instruction> ops, std::size_t stackSize) : code(code), ops(ops), callstack(1) {}
        Environment(const Environment& other) = delete;
        Environment& operator=(const Environment& other) = delete;
    };
}