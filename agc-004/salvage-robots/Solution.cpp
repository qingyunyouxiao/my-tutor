// 题意是挪动机器人使得更多机器人从出口获救，机器人不能越界，找到全局最优最大值。
// 针对运行时发生段错误，对代码进行性能优化。
// 针对答案错误，弄清楚行前缀和与列前缀和的定义，行号在前列号在后。

#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
#define MAXN 100

// 前缀和
int row[MAXN][MAXN], col[MAXN][MAXN];
char mp[MAXN][MAXN];
int n, m, ex, ey;
// 全局数组分配在静态存储区
short dp[MAXN][MAXN][MAXN][MAXN]; 

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // 整个四维 DP 数组所有元素统一初始化为 -1
    memset(dp, -1, sizeof(dp));
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        char buf[MAXN + 1]; // 设置缓冲区
        cin >> buf;   
        for(int j = 1; j <= m; j++) {
            mp[i][j] = buf[j - 1];
            if(mp[i][j] == 'E') {
                ex = i;
                ey = j;
            }
        }
    }

    // 预处理前缀和
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            row[i][j] = row[i][j-1] + (mp[i][j] == 'o' ? 1 : 0);
            col[j][i] = col[j][i-1] + (mp[i][j] == 'o' ? 1 : 0);
        }
    }

    int ans = 0;
    // 四重循环纯递推
    for (int l = 0; l <= ey - 1; ++l) {
        for (int r = 0; r <= m - ey; ++r) {
            for (int u = 0; u <= ex - 1; ++u) {
                for (int d = 0; d <= n - ex; ++d) {
                    // 1. 更新全局答案
                    ans = max(ans, (int)dp[l][r][u][d]);
                    
                    // 当前矩形的绝对边界
                    int up = ex - u;
                    int down = ex + d;
                    int left = ey - l;
                    int right = ey + r;
                    
                    // 2. 向左扩展 (l -> l + 1)
                    if (l + 1 <= ey - 1) {
                        // 新增的是 left - 1 这一列，范围是 [up, down]
                        int add = col[left - 1][min(down, n)] - col[left - 1][max(up, 1) - 1];
                        dp[l + 1][r][u][d] = max(dp[l + 1][r][u][d], (short)(dp[l][r][u][d] + add));
                    }
                    
                    // 3. 向右扩展 (r -> r + 1)
                    if (r + 1 <= m - ey) {
                        // 新增的是 right + 1 这一列，范围是 [up, down]
                        int add = col[right + 1][min(down, n)] - col[right + 1][max(up, 1) - 1];
                        dp[l][r + 1][u][d] = max(dp[l][r + 1][u][d], (short)(dp[l][r][u][d] + add));
                    }
                    
                    // 4. 向上扩展 (u -> u + 1)
                    if (u + 1 <= ex - 1) {
                        // 新增的是 up - 1 这一行，范围是 [left, right]
                        int add = row[up - 1][min(right, m)] - row[up - 1][max(left, 1) - 1];
                        dp[l][r][u + 1][d] = max(dp[l][r][u + 1][d], (short)(dp[l][r][u][d] + add));
                    }
                    
                    // 5. 向下扩展 (d -> d + 1)
                    if (d + 1 <= n - ex) {
                        // 新增的是 down + 1 这一行，范围是 [left, right]
                        int add = row[down + 1][min(right, m)] - row[down + 1][max(left, 1) - 1];
                        dp[l][r][u][d + 1] = max(dp[l][r][u][d + 1], (short)(dp[l][r][u][d] + add));
                    }
                }
            }
        }
    }

    cout << ans << endl;
    fclose(stdin);
    return 0;
}