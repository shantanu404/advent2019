#include <bits/stdc++.h>

using namespace std;

struct Point {
    size_t x, y;
    Point(size_t x, size_t y):
        x(x), y(y) {};
};

const auto WIDTH = 25u;
const auto HEIGHT = 6u;

typedef array<array<int, WIDTH>, HEIGHT> Layer;

size_t count(const Layer& layer, int val) {
    auto counter = 0u;
    for (const auto& row: layer)
        for (const auto& cell: row)
            if (cell == val)
                counter ++;
    return counter;
}

int main() {
    auto layers = vector<Layer>();
    auto cursor = Point(0, 0);

    char byte;
    auto cur_layer = Layer();
    while (cin >> byte) {
        auto val = byte - static_cast<int>('0');
        cur_layer[cursor.y][cursor.x++] = val;

        if (cursor.x == WIDTH) {
            cursor.x = 0;
            cursor.y++;
        }

        if (cursor.y == HEIGHT) {
            layers.push_back(cur_layer);
            cursor = Point(0, 0);
        }
    }

    auto min_num_zeros = 1e9;
    auto min_layer = layers.front();
    for (const auto& layer: layers) {
        auto num_of_zeros = count(layer, 0);

        if (num_of_zeros < min_num_zeros) {
            min_num_zeros = num_of_zeros;
            min_layer = layer;
        }
    }

    cout << "[Part 1]\n";
    cout << "Checksum: ";
    cout << count(min_layer, 1) * count(min_layer, 2) << endl;

    cout << "[Part 2]\n";
    auto image = Layer();

    auto accumulate = [](int bot, int top) {
        if (top == 2)
            return bot;
        else
            return top;
    };

    reverse(begin(layers), end(layers));

    for (const auto& layer : layers)
        for (auto y = 0u; y < HEIGHT; y ++)
            for (auto x = 0u; x < WIDTH; x ++)
                image[y][x] = accumulate(image[y][x], layer[y][x]);

    for (const auto& row : image) {
        for (const auto& cell : row)
            if (cell == 1)
                cout << "\u2592"; // unicode medium shade
            else
                cout << ' ';
        cout << '\n';
    }

    return 0;
}

