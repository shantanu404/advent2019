#include <bits/stdc++.h>
#include "intcode.hpp"

using namespace std;

int main() {
    map<int64_t, int64_t> opcodes;

    int64_t opcode;
    char comma;

    int64_t idx = 0;
    do {
        cin >> opcode;
        opcodes[idx++] = opcode;
    } while (cin >> comma);

    auto program = make_shared<Program>();
    program->opcodes = opcodes;

    for (int x = 1; x <= 2; x ++) {
        stringstream is;
        is << x;

        cout << "[Part " << x << "]\n";
        run_program(program, is, cout);
    }

    return 0;
}

