#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

const int NH = 105, NW = 105;
int H, W, r0, c0;
char mp[NH][NW];
short dp[105][105][105][105];
int sum[NH][NW];

int GetSum(int r1, int c1, int r2, int c2) {
	return sum[r2][c2] - sum[r1 - 1][c2] - sum[r2][c1 - 1] + sum[r1 - 1][c1 - 1];
}
int max(int x, int y) { return (x > y) ? x : y; }
int min(int x, int y) { return (x < y) ? x : y; }

int main() {
	scanf("%d%d", &H, &W);
	for (int i = 1; i <= H; ++i) scanf("%s", mp[i] + 1);
	for (int i = 1; i <= H; ++i)
		for (int j = 1; j <= W; ++j)
			if (mp[i][j] == 'E') {
				r0 = i;
				c0 = j;
				break ;
			}
	for (int i = 1; i <= H; ++i)
		for (int j = 1; j <= W; ++j)
			sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + (mp[i][j] == 'o');
	memset(dp, 0x8f, sizeof(dp));
	dp[0][0][0][0] = 0;
	int ans = 0;
	for (int s = 0; s <= H - 1 + W - 1; ++s)
		for (int l = 0; l <= c0 - 1; ++l)
			for (int r = 0; r <= W - c0 && l + r <= s; ++r)
				for (int u = 0; u <= r0 - 1 && l + r + u <= s; ++u) {
					int d = s - l - r - u;
					if (r0 + d > H || d < 0) continue ;
					int lu, ld, ll, lr;
					lu = max((r0 + d) - (r0 - 1), 1);
					ld = min((r0 - u) + (H - r0), H);
					ll = max((c0 + r) - (c0 - 1), 1); //这开始写错了
					lr = min((c0 - l) + (W - c0), W);
					int r1, c1, r2, c2;
					r1 = r0 - u;
					c1 = c0 - l;
					r2 = r0 + d;
					c2 = c0 + r;
					if (r1-1 >= 1) {
						int u1 = u + 1;
						if (r1-1 >= lu) {
							dp[l][r][u1][d] = max(dp[l][r][u1][d], dp[l][r][u][d] + GetSum(r1-1, max(ll, c1), r1-1, min(lr, c2)));
						} else dp[l][r][u1][d] = max(dp[l][r][u1][d], dp[l][r][u][d]);
					}
					if (r2+1 <= H) { //这不是 else if
						int d1 = d + 1;
						if (r2+1 <= ld) {
							dp[l][r][u][d1] = max(dp[l][r][u][d1], dp[l][r][u][d] + GetSum(r2+1, max(ll, c1), r2+1, min(lr, c2)));
						} else dp[l][r][u][d1] = max(dp[l][r][u][d1], dp[l][r][u][d]);
					}
					if (c1-1 >= 1) {
						int l1 = l + 1;
						if (c1-1 >= ll) {
							dp[l1][r][u][d] = max(dp[l1][r][u][d], dp[l][r][u][d] + GetSum(max(lu, r1), c1-1, min(ld, r2), c1-1));
																						//这里的取 max要注意
						} else dp[l1][r][u][d] = max(dp[l1][r][u][d], dp[l][r][u][d]);
					}
					if (c2+1 <= W) {
						int rr1 = r + 1;
						if (c2+1 <= lr) {
							dp[l][rr1][u][d] = max(dp[l][rr1][u][d], dp[l][r][u][d] + GetSum(max(lu, r1), c2+1, min(ld, r2), c2+1));
						} else dp[l][rr1][u][d] = max(dp[l][rr1][u][d], dp[l][r][u][d]);
					}
					ans = max(dp[l][r][u][d], ans);
				}
	printf("%d\n", ans);
	return 0;
}