#include <bits/stdc++.h>

using namespace std;

int64_t run_program(vector<int64_t> opcodes, stringstream input_stream) {
    size_t ipointer = 0;
    while (1) {
        int opcode = opcodes[ipointer++];
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
            auto pos = opcodes[ipointer++];
            int input;
            input_stream >> input;
            opcodes[pos] = input;
        } else if (op == 4) {
            auto pos = opcodes[ipointer++];
            if (m0 == 0) {
                pos = opcodes[pos];
            }
            cout << "[+] " << pos << endl;
            if (pos != 0) {
                cerr << "Program halted: ";
                cerr << "non-zero return value @ " << ipointer << endl;
                return 0;
            }
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
            opcodes[pos] = (a < b) ? 1 : 0;
        } else if (op == 8) {
            auto a = opcodes[ipointer++];
            auto b = opcodes[ipointer++];
            auto pos = opcodes[ipointer++];
            if (m0 == 0)
                a = opcodes[a];
            if (m1 == 0)
                b = opcodes[b];
            opcodes[pos] = (a == b) ? 1 : 0;
        } else if (op == 99) {
            return opcodes[0];
        } else {
            return -1;
        }
    }
}

int main() {
    vector<int64_t> opcodes;

    int64_t opcode;
    char comma;
    do {
        cin >> opcode;
        opcodes.push_back(opcode);
    } while (cin >> comma);

    // part one
    run_program(opcodes, stringstream("1"));
    // part two
    run_program(opcodes, stringstream("5"));

    return 0;
}

