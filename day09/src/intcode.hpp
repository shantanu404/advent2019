#ifndef _intcode_h
#define _intcode_h

#include <cstdlib>
#include <map>
#include <iostream>
#include <memory>

struct Program {
    std::map<int64_t, int64_t> opcodes;
    int64_t instruction_pointer;
    int64_t stack_pointer;

    Program()
        :instruction_pointer(0), stack_pointer(0) {};
};

bool run_program(std::shared_ptr<Program> program,
        std::istream& input_stream, std::ostream& output_stream);

#endif
