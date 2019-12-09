#include <bits/stdc++.h>
#include "intcode.hpp"

using namespace std;

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
        for (auto& program : programs) {
            program = make_shared<Program>();
            program->opcodes = opcodes;
        }

        auto rc = 0l;
        for (auto x = 0u; x < programs.size(); x ++) {
            auto cfg = ampconfigs[x];
            auto prog = programs[x];
            stringstream os;
            stringstream is;

            is << cfg << endl;
            run_program(prog, is, os);
        }

        for (const auto& prog : programs) {
            stringstream is;
            stringstream os;
            is << rc;
            run_program(prog, is, os);
            os >> rc;
        }

        max_rc = max(max_rc, rc);
    } while(next_permutation(ampconfigs.begin(), ampconfigs.end()));

    cout << "[Part 1]\n";
    cout << max_rc << endl;

    auto max_fd = -1l;
    auto fconfigs = array<int, 5>({5, 6, 7, 8, 9});
    do {
        for (auto& program : programs) {
            program = make_shared<Program>();
            program->opcodes = opcodes;
        }

        for (auto x = 0u; x < programs.size(); x ++) {
            stringstream is;
            stringstream os;
            is << fconfigs[x];
            run_program(programs[x], is, os);
        }

        auto rc = 0L;
        auto running = true;
        while (running) {
            for (auto& prog : programs) {
                stringstream is;
                stringstream os;
                is << rc;
                running = run_program(prog, is, os);
                os >> rc;
            }
            max_fd = max(max_fd, rc);
        }
    } while (next_permutation(fconfigs.begin(), fconfigs.end()));

    cout << "[Part 2]\n";
    cout << max_fd << endl;

    return 0;
}

