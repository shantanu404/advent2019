#include <bits/stdc++.h>

using namespace std;

vector<int> to_digits(int pass) {
    auto digits = vector<int>();
    while (pass > 0) {
        digits.push_back(pass % 10);
        pass /= 10;
    }
    reverse(digits.begin(), digits.end());
    return digits;
}

int main() {
    int start, end;
    char _del;
    cin >> start >> _del >> end;

    auto pass_counter = 0; // for part one
    auto real_pass_counter = 0; // for part two;

    for (int pass = start; pass <= end; pass ++) {
        auto digits = to_digits(pass);
        auto sorted = is_sorted(digits.cbegin(), digits.cend());

        if (!sorted)
            continue;

        // make a contigenous frequency map
        // as the digits are ensured to be non-decreasing from this point
        // we can easily count the length of contigenous equal digits

        auto freq = map<int, int>();
        auto prev = digits.cbegin();
        auto counter = 1;
        for (auto it = digits.cbegin() + 1; it != digits.cend(); it ++) {
            if (*prev == *it) {
                counter ++;
            } else {
                freq[*prev] = counter;
                prev = it;
                counter = 1;
            }
        }
        freq[*prev] = counter;

        // count the pairs even if they may have other neighbours
        auto paired = any_of(freq.cbegin(), freq.cend(),
                            [](pair<int, int> p) { return p.second >= 2; });
        if (paired)
            pass_counter ++;

        // only count the pairs who have no other neighbours except from themselves
        auto only_paired = any_of(freq.cbegin(), freq.cend(),
                            [](pair<int, int> p) { return p.second == 2; });
        if (only_paired)
            real_pass_counter ++;
    }

    cout << "[Part 1]\n";
    cout << "There are " << pass_counter << " possible passwords\n";

    cout << "[Part 2]\n";
    cout << "There are " << real_pass_counter << " possible passwords for sure!\n";

    return 0;
}
