// 取反操作最多只会使用两次，并且必定发生在操作的开头或结尾。
// 因此，我们可以直接枚举取反操作的次数和位置，计算所有可能的情况并取最小值即可。

#include <bits/stdc++.h>
#define int long long
#define rep(i, l, r) for (int i = l; i <= r; i++)
using namespace std;

signed main() {
    cin.tie(0) -> ios::sync_with_stdio(false);
    int x, y;
    cin >> x >> y;
    
    int ans = 0x3f3f3f3f3f3f3f3f;
    // 枚举 i, j 取值 -1, 0, 1
    // i 表示开头是否取反，j 表示结尾是否取反
    rep (i, -1, 1) {
        rep (j, -1, 1) {
            if (!i || !j) continue;
            // 满足条件：x * i <= y * j
            if (x * i <= y * j) {
                // 计算代价：差值 + 开头取反代价 + 结尾取反代价
                ans = min(ans, (y * j - x * i) + (i == -1) + (j == -1));
            }
        }
    }
    cout << ans << "\n";
    return 0;
}