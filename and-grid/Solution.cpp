#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 重定向标准输入到 input.txt
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());

    int H, W;
    cin >> H >> W;
    vector<string> a(H);
    for (int i = 0; i < H; ++i) {
        cin >> a[i];
    }

    // 输出红色网格
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            if (i % 2 == 0 || a[i][j] == '#')
                cout << '#';
            else
                cout << '.';
        }
        cout << '\n';
    }
    cout << "----------Divider----------\n";
    // 输出蓝色网格
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            if (j % 2 == 1 || a[i][j] == '#')
                cout << '#';
            else
                cout << '.';
        }
        cout << '\n';
    }

    fin.close();
    return 0;
}