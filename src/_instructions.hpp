#pragma once

#include "src/Environment.hpp"
#include "_defines.h"   

#define NEXT env->code[++(env->counter)]

#define Push(x) env->bstack.Push(x)
#define Pop() env->bstack.Pop()

namespace Warlokbytes {
    namespace Hardcoded {
        const std::map<byte, Environment::Instruction> ops = {
            INSTRUCTION(PASS, "PASS",
                Log("PASSED")
            )
            INSTRUCTION(HALT, "HALT", {
                byte exit = Pop();
                env->Halt();
                return exit;
                Log("HALTED");
            })
            INSTRUCTION(PUSHB, "PUSHB", {
                byte val = NEXT;
                Push(val);
                Log("PUSHED");
            })
            INSTRUCTION(ADD, "ADD", {
                byte a = Pop();
                byte b = Pop();
                Push(a + b);
            })
            INSTRUCTION(SUB, "SUB", {
                byte a = Pop();
                byte b = Pop();
                Push(a - b);
            })
            INSTRUCTION(PUSHN, "PUSHN", {
                Log("PUSHED NULL TERMINATED");
                Push(0x00); // Push null terminator for the string
                while(char current = NEXT) {
                    Push(current);
                }
            })
            INSTRUCTION(PRINT, "PRINT", {
                while(char current = Pop()) {
                    std::cout << current;
                }
            })
        };
    }
}