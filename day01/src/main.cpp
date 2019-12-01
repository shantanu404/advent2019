#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<int64_t> mods;

    int64_t mod;
    while (cin >> mod) {
        mods.push_back(mod);
    }

    auto fuel = 0L;
    for (auto mod : mods) {
        fuel += (mod / 3) - 2;
    }

    cout << "[Part 1]\nTotal fuel: ";
    cout << fuel << endl;

    auto actual_fuel = 0L;
    for (auto mod: mods) {
        auto f = (mod / 3) - 2;
        while (f > 0) {
            actual_fuel += f;
            f = (f / 3) - 2;
        }
    }

    cout << "[Part 2]\nActual fuel: ";
    cout << actual_fuel << endl;

    return 0;
}

