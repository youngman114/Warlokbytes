#include <vector>
#include <string>

#include "_defines.h"

namespace Warlokbytes {
    /// Expresses a scope with all underlying stack and locals
    struct Frame {
        std::vector<byte> stack;
        std::vector<byte> locals;
        
        Frame(u32 sstack = 0, u32 slocals = 0) : stack(sstack), locals(slocals) {}
    };

    typedef std::vector<Frame> FrameStack;
}