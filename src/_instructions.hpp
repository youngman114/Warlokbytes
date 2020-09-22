#pragma once

#include "src/Environment.hpp"
#include "_defines.h"   

#define NEXT env->code[++(env->counter)]

#define Push(x) env->bstack.Push(x)
#define Pop() env->bstack.Pop()

namespace Warlokbytes {
    namespace Hardcoded {
        const std::map<byte, Environment::instruction> ops = {
            INSTRUCTION(PASS, 
                Log("PASSED")
            )
            INSTRUCTION(HALT, {
                byte exit = Pop();
                env->Halt();
                return exit;
                Log("HALTED");
            })
            INSTRUCTION(PUSHB, {
                byte val = NEXT;
                Push(val);
                Log("PUSHED");
            })
            INSTRUCTION(ADD, {
                byte a = Pop();
                byte b = Pop();
                Push(a + b);
            })
            INSTRUCTION(SUB, {
                byte a = Pop();
                byte b = Pop();
                Push(a - b);
            })
            INSTRUCTION(PUSHN, {
                Log("PUSHED NULL TERMINATED");
                Push(0x00); // Push null terminator for the string
                while(char current = NEXT) {
                    Push(current);
                }
            })
            INSTRUCTION(PRINT, {
                while(char current = Pop()) {
                    std::cout << current;
                }
            })
        };
    }
}