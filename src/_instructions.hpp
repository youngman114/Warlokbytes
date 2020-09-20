#pragma once

#include "src/Environment.hpp"
#include "_defines.h"   

#define NEXT env->code[++(env->counter)]

namespace Warlokbytes {
    namespace Hardcoded {
        const std::map<byte, Environment::instruction> ops = {
            INSTRUCTION(PASS, 
                Log("PASSED")
            )
            INSTRUCTION(HALT, {
                byte exit = NEXT;
                env->Halt();
                Log("HALTED");
                return NEXT;
            })
            INSTRUCTION(PUSH, {
                byte val = NEXT;
                Log("PUSHED");
                env->bstack.Push(val);
            })
        };
    }
}