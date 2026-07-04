// 题意是挪动机器人使得更多机器人从出口获救。
// 问题：运行时发生段错误。

#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>
#include <algorithm>

using namespace std;
#define MAXN 100

// 前缀和
int row[MAXN][MAXN], col[MAXN][MAXN];
char mp[MAXN][MAXN];
int n, m, ex, ey;

// up, down, left, right, dp
int dfs(int l, int r, int u, int d, vector<vector<vector<vector<short>>>>& dp) {
    if (dp[l][r][u][d] != -1) return dp[l][r][u][d];
        // 当前黄色存活矩形边界
        int up = ex + u;
        int down = ex - d;
        int left = ey + l;
        int right = ey - r;
        int res = 0;
        // 1. 向上拓展一层
        if (up - 1 >= 1) {
            int add = row[up - 1][right] - row[up - 1][left - 1];
            res = max(res, dfs(l, r, u + 1, d, dp) + add);
        }
        // 2. 向下拓展一层
        if (down + 1 <= n) {
            int add = row[down + 1][right] - row[down + 1][left - 1];
            res = max(res, dfs(l, r, u, d + 1, dp) + add);
        }
        // 3. 向左拓展一层
        if (left - 1 >= 1) {
            int add = col[left - 1][down] - col[left - 1][up - 1];
            res = max(res, dfs(l + 1, r, u, d, dp) + add);
        }
        // 4. 向右拓展一层
        if (right + 1 <= m) {
            int add = col[right + 1][down] - col[right + 1][up - 1];
            res = max(res, dfs(l, r + 1, u, d, dp) + add);
        }
    return dp[l][r][u][d] = res;
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // 整个四维 DP 数组所有元素统一初始化为 -1
    vector<vector<vector<vector<short>>>> dp(MAXN, vector<vector<vector<short>>>
        (MAXN, vector<vector<short>>(MAXN, vector<short>(MAXN, -1))));
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        char buf[MAXN]; // 设置缓冲区
        cin >> buf;   
        for(int j = 1; j <= m; j++) {
            mp[i][j] = buf[j - 1];
            if(mp[i][j] == 'E') {
                ex = i;
                ey = j;
            }
        }
    }

    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            row[i][j] = row[i][j-1] + (mp[i][j] == 'o' ? 1 : 0);
            col[j][i] = col[j][i-1] + (mp[i][j] == 'o' ? 1 : 0);
        }
    }
    int ans = dfs(0, 0, 0, 0, dp);
    cout << ans << endl;

    fclose(stdin);
    return 0;
}
