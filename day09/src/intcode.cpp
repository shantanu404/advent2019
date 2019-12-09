#include "intcode.hpp"

int64_t get_data(const int64_t mode, const std::map<int64_t, int64_t>& opcodes,
                 const int64_t ipointer, const int64_t stack_pointer) {
    auto val = 0l;

    if (opcodes.count(ipointer))
        val = opcodes.at(ipointer);

    if (mode == 0) {
        if (opcodes.count(val))
            val = opcodes.at(val);
        else
            val = 0;
    } else if (mode == 2) {
        if (opcodes.count(val + stack_pointer))
            val = opcodes.at(val + stack_pointer);
        else
            val = 0;
    }

    return val;
}

void set_data(const int64_t mode, std::map<int64_t, int64_t>& opcodes,
              const int64_t stack_pointer, int64_t pos, const int64_t input) {
    if (mode == 2)
        pos += stack_pointer;
    opcodes[pos] = input;
}

bool run_program(std::shared_ptr<Program> program,
                    std::istream& input_stream, std::ostream& output_stream) {
    auto& opcodes = program->opcodes;
    auto& ipointer = program->instruction_pointer;
    auto& spointer = program->stack_pointer;
    while (1) {
        int64_t opcode = get_data(1, opcodes, ipointer++, spointer);
        auto op = opcode % 100;
        opcode /= 100;
        auto m0 = opcode % 10;
        opcode /= 10;
        auto m1 = opcode % 10;
        opcode /= 10;
        auto m2 = opcode % 10;

        if (op == 1) {
            auto a = get_data(m0, opcodes, ipointer++, spointer);
            auto b = get_data(m1, opcodes, ipointer++, spointer);

            auto pos = get_data(1, opcodes, ipointer++, spointer);
            set_data(m2, opcodes, spointer, pos, a + b);
        } else if (op == 2) {
            auto a = get_data(m0, opcodes, ipointer++, spointer);
            auto b = get_data(m1, opcodes, ipointer++, spointer);

            auto pos = get_data(1, opcodes, ipointer++, spointer);
            set_data(m2, opcodes, spointer, pos, a * b);
        } else if (op == 3) {
            int64_t input;
            if (input_stream >> input) {
                auto pos = get_data(1, opcodes, ipointer++, spointer);
                set_data(m0, opcodes, spointer, pos, input);
            } else {
                ipointer --;
                return true;
            }
        } else if (op == 4) {
            auto pos = get_data(m0, opcodes, ipointer++, spointer);
            output_stream << pos << std::endl;
        } else if (op == 5) {
            auto cond = get_data(m0, opcodes, ipointer++, spointer);
            auto val = get_data(m1, opcodes, ipointer++, spointer);

            if (cond != 0)
                ipointer = val;
        } else if (op == 6) {
            auto cond = get_data(m0, opcodes, ipointer++, spointer);
            auto val = get_data(m1, opcodes, ipointer++, spointer);

            if (cond == 0)
                ipointer = val;
        } else if (op == 7) {
            auto a = get_data(m0, opcodes, ipointer++, spointer);
            auto b = get_data(m1, opcodes, ipointer++, spointer);

            auto pos = get_data(1, opcodes, ipointer++, spointer);
            auto val = (a < b) ? 1l : 0l;
            set_data(m2, opcodes, spointer, pos, val);
        } else if (op == 8) {
            auto a = get_data(m0, opcodes, ipointer++, spointer);
            auto b = get_data(m1, opcodes, ipointer++, spointer);

            auto pos = get_data(1, opcodes, ipointer++, spointer);
            auto val = (a == b) ? 1l : 0l;
            set_data(m2, opcodes, spointer, pos, val);
        } else if (op == 9) {
            auto x = get_data(m0, opcodes, ipointer++, spointer);
            spointer += x;
        } else if (op == 99) {
            return false;
        } else {
            std::cerr << "Unexpected halt @ " << ipointer << '\n';
            return false;
        }
    }
}
