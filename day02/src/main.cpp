#include <bits/stdc++.h>

using namespace std;

int64_t run_program(vector<int64_t> opcodes, int64_t noun, int64_t verb) {
    opcodes[1] = noun;
    opcodes[2] = verb;

    size_t ipointer = 0;
    while (1) {
        int op = opcodes[ipointer++];
        if (op == 1) {
            auto a = opcodes[ipointer++];
            auto b = opcodes[ipointer++];
            auto pos = opcodes[ipointer++];

            opcodes[pos] = opcodes[a] + opcodes[b];
        } else if (op == 2) {
            auto a = opcodes[ipointer++];
            auto b = opcodes[ipointer++];
            auto pos = opcodes[ipointer++];

            opcodes[pos] = opcodes[a] * opcodes[b];
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

    cout << "[Part 1]\n";
    cout << "Opcode @ 0: " << run_program(opcodes, 12, 2) << endl;

    cout << "[Part 2]\n";

    int verb = 0;
    int noun = 0;
    while(run_program(opcodes, 0, ++verb) % 1000 != 720);
    while(run_program(opcodes, ++noun, verb) != 19690720);

    cout << "(" << noun << ", " << verb << "): " << 100 * noun + verb << endl;

    return 0;
}

