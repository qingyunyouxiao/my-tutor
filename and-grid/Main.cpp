#include <iostream>
#include <vector>
#include <string>
#include <ranges>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int H, W;
    cin >> H >> W;
    vector<string> a(H);
    for (int i = 0; i < H; ++i) cin >> a[i];
    
    // 输出红色网格
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            // 奇数行(i从0开始则i%2==0) 或者 是#
            if (i % 2 == 0 || a[i][j] == '#') cout << '#';
            else cout << '.';
        }
        cout << '\n';
    }
    // 输出蓝色网格
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            // 偶数列(j从0开始则j%2==1) 或者 是#
            if (j % 2 == 1 || a[i][j] == '#') cout << '#';
            else cout << '.';
        }
        cout << '\n';
    }
    return 0;
}