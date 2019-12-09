#include "intcode.hpp"

bool run_program(std::shared_ptr<Program> program,
                    std::istream& input_stream, std::ostream& output_stream) {
    auto& opcodes = program->opcodes;
    auto& ipointer = program->ip;
    while (1) {
        int64_t opcode = opcodes[ipointer++];
        auto op = opcode % 100;
        opcode /= 100;
        auto m0 = opcode % 10;
        opcode /= 10;
        auto m1 = opcode % 10;

        if (op == 1) {
            auto a = opcodes[ipointer++];
            auto b = opcodes[ipointer++];
            auto pos = opcodes[ipointer++];

            if (m0 == 0)
                a = opcodes[a];
            if (m1 == 0)
                b = opcodes[b];

            opcodes[pos] = a + b;
        } else if (op == 2) {
            auto a = opcodes[ipointer++];
            auto b = opcodes[ipointer++];
            auto pos = opcodes[ipointer++];

            if (m0 == 0)
                a = opcodes[a];
            if (m1 == 0)
                b = opcodes[b];

            opcodes[pos] = a * b;
        } else if (op == 3) {
            int64_t input;
            if (input_stream >> input) {
                auto pos = opcodes[ipointer++];
                opcodes[pos] = input;
            } else {
                ipointer --;
                return true;
            }
        } else if (op == 4) {
            auto pos = opcodes[ipointer++];
            if (m0 == 0) {
                pos = opcodes[pos];
            }
            output_stream << pos;
        } else if (op == 5) {
            auto cond = opcodes[ipointer++];
            auto val = opcodes[ipointer++];
            if (m0 == 0)
                cond = opcodes[cond];
            if (m1 == 0)
                val = opcodes[val];
            if (cond != 0)
                ipointer = val;
        } else if (op == 6) {
            auto cond = opcodes[ipointer++];
            auto val = opcodes[ipointer++];
            if (m0 == 0)
                cond = opcodes[cond];
            if (m1 == 0)
                val = opcodes[val];
            if (cond == 0)
                ipointer = val;
        } else if (op == 7) {
            auto a = opcodes[ipointer++];
            auto b = opcodes[ipointer++];
            auto pos = opcodes[ipointer++];
            if (m0 == 0)
                a = opcodes[a];
            if (m1 == 0)
                b = opcodes[b];
            opcodes[pos] = (a < b) ? 1l : 0l;
        } else if (op == 8) {
            auto a = opcodes[ipointer++];
            auto b = opcodes[ipointer++];
            auto pos = opcodes[ipointer++];
            if (m0 == 0)
                a = opcodes[a];
            if (m1 == 0)
                b = opcodes[b];
            opcodes[pos] = (a == b) ? 1l : 0l;
        } else {
            return false;
        }
    }
}
