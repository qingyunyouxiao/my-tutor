// 题意是构造连通的红色和蓝色格子布局，并且它们重叠的部分正好等于输入的 # 部分，同时保证最外圈不是紫色。

#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int H, W;
    // H 行 W 列
    cin >> H >> W;
    vector<string> s(H);
    for (int i = 0; i < H; ++i) cin >> s[i];

    // 输出红色
    // 第一行：全部涂红（#）
    // 中间行：在紫色位置（#）或者偶数列位置涂红
    // 最后一行：全部不涂（.）
    cout << string(W, '#') << endl;  // 第一行全是 '#'
    for (int i = 1; i < H - 1; ++i) {
        for (int j = 0; j < W; ++j) {
            cout << (s[i][j] == '#' || j % 2 == 0 ? '#' : '.');
        }
        cout << endl;
    }
    cout << string(W, '.') << endl;  // 最后一行全是 '.'

    // 单独一空行
    cout << endl;

    // 蓝色布局
    // 第一行：全部不涂（.）
    // 中间行：在紫色位置（#）或者奇数列位置涂蓝
    // 最后一行：全部涂蓝（#）
    cout << string(W, '.') << endl;
    for (int i = 1; i < H - 1; ++i) {
        for (int j = 0; j < W; ++j) {
            cout << (s[i][j] == '#' || j % 2 == 1 ? '#' : '.');
        }
        cout << endl;
    }
    cout << string(W, '#') << endl;
    return 0;
}

