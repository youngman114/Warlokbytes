#include <cstring>
#include <fstream>

#include "src/Environment.hpp"

#include "src/_defines.h"
#include "src/_instructions.hpp"


int main(const int argc, const char** argv) {
    using namespace Warlokbytes;

    std::vector<byte> code = {};

    if(argc > 1) {
        /* https://stackoverflow.com/questions/18816126/c-read-the-whole-file-in-buffer */
        std::ifstream file;
        file.open(std::string(argv[1]), std::ios::binary | std::ios::ate); // Open file at the end
        if(!file.is_open()) {
            Error("Couldn't open \"" + std::string(argv[1]) + "\"");
            return 1;
        }
        std::size_t size = file.tellg(); // Record eof position
        code.resize(size);
        file.seekg(0, std::ios::beg); // Revert to the beginning
        file.read((char*)(code.data()), size);
    } else {
        Error("No files to execute.");
        return 1;
    }

    const std::map<byte, Instruction> ops = Hardcoded::ops;
    Environment* env = new Environment {code, ops, 16};

    while(env->IsRunning()) {
        env->Step();
    }

    return env->GetState();
}