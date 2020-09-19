#pragma once

#include "src/Environment.hpp"
#include "_defines.h"   

#define NEXT env->code[++(env->counter)]

namespace Warlokbytes {
    namespace Hardcoded {
        const std::map<byte, Environment::instruction> ops = {
            INSTRUCTION(PASS, Log("PASS"))
            INSTRUCTION(HALT, {
                Log("HALT");
                env->Halt();
                return NEXT;
            })
            INSTRUCTION(PUSH, {
                byte val = NEXT;
            })
        };
    }
}