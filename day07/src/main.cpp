#include <bits/stdc++.h>

using namespace std;

struct Program {
    vector<int64_t> opcodes;
    size_t ip;

    Program():ip(0) {};
};

bool run_program(vector<int64_t>& opcodes, size_t &ipointer,
                    stringstream& input_stream, stringstream& output_stream) {
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
            output_stream << pos << endl;
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


int main() {
    vector<int64_t> opcodes;

    int64_t opcode;
    char comma;
    do {
        cin >> opcode;
        opcodes.push_back(opcode);
    } while (cin >> comma);

    auto programs = array<shared_ptr<Program>, 5>();

    auto ampconfigs = array<int, 5>({0, 1, 2, 3, 4});
    auto max_rc = -1l;

    do {
        for (auto x = 0u; x < programs.size(); x ++) {
            programs[x] = make_shared<Program>();
            programs[x]->opcodes = opcodes;
        }

        auto rc = 0l;
        for (auto x = 0u; x < programs.size(); x ++) {
            auto cfg = ampconfigs[x];
            auto prog = programs[x];
            stringstream os;
            stringstream is;

            is << cfg << endl;
            run_program(prog->opcodes, prog->ip, is, os);
        }

        for (auto x = 0u; x < programs.size(); x ++) {
            stringstream is;
            stringstream os;

            auto prog = programs[x];
            is << rc;
            run_program(prog->opcodes, prog->ip, is, os);
            os >> rc;
        }

        max_rc = max(max_rc, rc);
    } while(next_permutation(ampconfigs.begin(), ampconfigs.end()));

    cout << "[Part 1]\n";
    cout << max_rc << endl;

    auto max_fd = -1l;
    auto fconfigs = array<int, 5>({5, 6, 7, 8, 9});
    do {
        for (auto x = 0u; x < programs.size(); x ++) {
            programs[x] = make_shared<Program>();
            programs[x]->opcodes = opcodes;
        }

        for (int x = 0; x < 5; x ++) {
            stringstream is;
            stringstream os;
            is << fconfigs[x];
            run_program(programs[x]->opcodes, programs[x]->ip, is, os);
        }

        auto rc = 0L;
        auto running = true;
        while (running) {
            for (int x = 0; x < 5; x ++) {
                auto program = programs[x];
                stringstream is;
                stringstream os;
                is << rc;
                running = run_program(program->opcodes, program->ip, is, os);
                os >> rc;
            }
            max_fd = max(max_fd, rc);
        }
    } while (next_permutation(fconfigs.begin(), fconfigs.end()));

    cout << "[Part 2]\n";
    cout << max_fd << endl;

    return 0;
}

