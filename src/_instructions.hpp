#pragma once

#include "src/Environment.hpp"
#include "_defines.h"   


/* BASIC INSTRUCTIONS*/
// Do nothing
#define PASS 0x00
// Print NULL terminated string from stack
#define PRINT 0x01

/* STACK INSTRUCTIONS */
// But next byte onto the stack
#define PUSHB 0x10
// Push NULL terminated string onto the stack
#define PUSHN 0x11

/* ARITHMETIC INSTRUCTIONS */
// Add two numbers at stack and push result back
#define ADD 0x20
// Subtract two numbers at stack and push result back
#define SUB 0x21
// Multiply two numbers at the stack
#define MUL 0x22
// Divide two numbers
#define DIV 0x23

/* MISC INSTRUCTIONS */
// End the program execution with TOS exit code
#define HALT 0xFF



#define NEXT env->GetCode()[++(env->GetCounter())]

#define Push(x) env->currStack.push_back(x)
#define Pop() env->currStack.back(); env->currStack.pop_back()
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
                /// Works like that because of std::vector::pop_back not returning popped value
                char current = Pop();
                while(true) {
                    std::cout << current;
                    current = Pop();
                    if(!current) break;
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