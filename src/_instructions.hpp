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
            )
            INSTRUCTION(HALT, {
                byte exit = Pop();
                env->Halt();
                return exit;
            })
            INSTRUCTION(PUSHB, {
                byte val = NEXT;
                Push(val);
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