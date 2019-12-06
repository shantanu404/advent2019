#include <bits/stdc++.h>

using namespace std;

int64_t bfs(const map<string, vector<string>>& graph, const string& start, const string& target)  {
    auto Q = queue<string>();
    auto dist_map = map<string, int64_t>();

    dist_map[start] = 0;
    Q.push(start);

    while (!Q.empty()) {
        auto node = Q.front();
        Q.pop();

        for (auto child : graph.at(node)) {
            if (dist_map.count(child) == 0) {
                dist_map[child] = dist_map[node] + 1;
                if (child == target)
                    return dist_map[child];
                Q.push(child);
            }
        }
    }

    return -1;
};

int main() {
    auto parent_map = map<string, string>();
    auto graph = map<string, vector<string>>();

    string line;
    while (cin >> line) {
        istringstream iss(line);
        string parent, child;
        getline(iss, parent, ')');
        getline(iss, child, ')');

        parent_map[child] = parent;

        if (graph.count(parent) == 0)
            graph[parent] = vector<string>();
        if (graph.count(child) == 0)
            graph[child] = vector<string>();

        graph[parent].push_back(child);
        graph[child].push_back(parent);
    }

    auto sum = 0L;
    for (auto p : parent_map) {
        auto node = p.first;
        while (node != "COM") {
            sum ++;
            node = parent_map[node];
        }
    }

    cout << "[Part 1]\n";
    cout << "Validating checksum: ";
    cout << sum << endl;

    auto distance = bfs(graph, parent_map["YOU"], parent_map["SAN"]);
    cout << "[Part 2]\n";
    cout << distance << " orbital jumps needed!\n";

    return 0;
}

