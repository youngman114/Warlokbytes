#include <cstring>
#include <fstream>

#include "src/Environment.hpp"

#include "_defines.h"
#include "_instructions.hpp"


int main(const int argc, const char** argv) {
    using namespace Warlokbytes;

    byte* code = new byte[2] {
        HALT,
        0x07
    };

    if(argc > 1) {
        /* https://stackoverflow.com/questions/18816126/c-read-the-whole-file-in-buffer */
        std::ifstream file;
        file.open(std::string(argv[1]), std::ios::binary | std::ios::ate); // Open file at the end
        if(!file.is_open()) {
            Error("Couldn't open \"" + std::string(argv[1]) + "\"");
            return 1;
        }
        auto size = file.tellg(); // Record eof position
        file.seekg(0, std::ios::beg); // Revert to the beginning
        // Clear code ptr, pretty sure there is  more elegant solution
        delete code; code = new byte[size]; 
        file.read((char*)code, size);
    } else {
        Error("No files to execute.");
        return 1;
    }

    const std::map<byte, Environment::instruction> ops = Hardcoded::ops;
    Environment* env = new Environment {code, ops};

    while(env->IsRunning()) {
        env->Step();
    }

    return env->state;
}