#ifndef _intcode_h
#define _intcode_h

#include <cstdlib>
#include <vector>
#include <iostream>
#include <memory>

struct Program {
    std::vector<int64_t> opcodes;
    size_t ip;

    Program():ip(0) {};
};

bool run_program(std::shared_ptr<Program> program,
        std::istream& input_stream, std::ostream& output_stream);

#endif
