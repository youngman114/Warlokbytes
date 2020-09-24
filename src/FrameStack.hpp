#include <vector>
#include <string>

#include "_defines.h"

namespace Warlokbytes {
    /// Expresses a scope with all underlying stack and locals
    struct Frame {
        std::vector<byte> stack;
        std::vector<byte> locals;
        
        Frame() : stack(1), locals(1) {}
    };

    typedef std::vector<Frame> FrameStack;
}