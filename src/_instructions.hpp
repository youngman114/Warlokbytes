#pragma once

#include "src/Environment.hpp"
#include "_defines.h"   

#define NEXT env->GetCode()[++(env->GetCounter())]

#define Push(x) env->GetByteStack().Push(x)
#define Pop() env->GetByteStack().Pop()
#define INSTRUCTION(OP, CODE)  {OP, Warlokbytes::Instruction([](Environment* env) -> byte {CODE; return 0x00;})},

namespace Warlokbytes {
    namespace Hardcoded {
        const std::map<byte, Instruction> ops = {
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
            INSTRUCTION(MUL, {
                byte a = Pop();
                byte b = Pop();
                Push(a * b);
            })
            INSTRUCTION(DIV, {
                byte a = Pop();
                byte b = Pop();
                Push(a / b);
            })
        };
    }
}