#include <bits/stdc++.h>

using namespace std;

typedef pair<long, long> Point;

enum Orientation {
    HORIZONTAL,
    VERTICAL,
};

struct Line {
    Point start, end;
    long step;
    Orientation orientation;

    Line(Point start, Point end, long step)
        :start(start), end(end), step(step) {
        if (start.first == end.first)
            orientation = VERTICAL;
        else
            orientation = HORIZONTAL;
    }
};

vector<Point> intersection(Line a, Line b) {
    auto rc = vector<Point>();

    if (a.orientation != b.orientation) {
        if (a.orientation != HORIZONTAL)
            swap(a, b);

        Point p = make_pair(b.start.first, a.start.second);

        auto a_min = min(a.start.first, a.end.first);
        auto a_max = max(a.start.first, a.end.first);

        auto b_min = min(b.start.second, b.end.second);
        auto b_max = max(b.start.second, b.end.second);

        if (a_min <= p.first && p.first <= a_max &&
            b_min <= p.second && p.second <= b_max)
                rc.push_back(p);
    } else {
        if (a.orientation == VERTICAL) {
            // case 1: both are vertical and on the same ordinate
            if  (a.start.first == b.start.first) {
                auto a_low = min(a.start.second, a.end.second);
                auto a_high = max(a.start.second, a.end.second);

                auto b_low = min(b.start.second, b.end.second);
                auto b_high = max(b.start.second, b.end.second);

                for (int y = max(a_low, b_low); y <= min(a_high, b_high); y ++)
                    rc.push_back({a.start.first, y});
            }
        } else {
            // case 2: both are horizontal and on the same abcissa
            if (a.start.second == b.start.second) {
                auto a_low = min(a.start.first, a.end.first);
                auto a_high = max(a.start.first, a.end.first);

                auto b_low = min(b.start.first, b.end.first);
                auto b_high = max(b.start.first, b.end.first);

                for (int x = max(a_low, b_low); x <= min(a_high, b_high); x ++)
                    rc.push_back({x, a.start.second});
            }
        }
    }

    return rc;
}

int main() {
    auto wires = vector<vector<Line>>();

    string line;
    while(getline(cin, line)) {
        auto wire = vector<Line>();

        Point start = {0, 0};
        Point end = {0, 0};
        long step_count = 0;

        istringstream iss(line);
        string path;
        while(getline(iss, path, ',')) {
            char dir = path.front();
            long steps = stol(path.substr(1));

            if (dir == 'L' || dir == 'D')
                steps =  0 - steps;

            if (dir == 'U' || dir == 'D')
                end.second += steps;
            else
                end.first += steps;

            wire.push_back(Line(start, end, step_count));
            start = end;
            step_count += abs(steps);
        }

        wires.push_back(wire);
    }

    long min_dist = 1e9; // for part 1
    long min_steps = 1e9; // for part 2
    auto col_steps = set<Point>();

    for (auto line : wires[0]) {
        for (auto other_line : wires[1]) {
            auto cols = intersection(line, other_line);
            for (auto col : cols) {
                if (col.first == 0 && col.second == 0)
                    continue;

                // part one
                auto dist = abs(col.first) + abs(col.second);
                min_dist = min(min_dist, dist);

                // part two
                auto steps_one = line.step
                                + abs(line.start.first - col.first)
                                + abs(line.start.second - col.second);
                auto steps_two = other_line.step
                                + abs(other_line.start.first - col.first)
                                + abs(other_line.start.second - col.second);

                if (col_steps.count(col) == 0) {
                    col_steps.insert(col);
                    min_steps = min(min_steps, steps_one + steps_two);
                }
            }
        }
    }

    cout << "[Part 1]\n";
    cout << "Minimum manhattan distance: ";
    cout << min_dist << endl;

    cout << "[Part 2]\n";
    cout << "Minimum steps needed: ";
    cout << min_steps << endl;

    return 0;
}

