# include <vector>
# include <iostream>
# include <algorithm>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, K;
    cin >> N >> K;
    vector<ll> a(N);
    for (int i = 0; i < N; ++i) cin >> a[i];

    vector<ll> pre_pos(N+1, 0); // pre_pos[i]: [0,i-1]所有正数之和
    for (int i = 0; i < N; ++i) {
        pre_pos[i+1] = pre_pos[i] + max(0LL, a[i]);
    }
    ll total_pos = pre_pos[N];

    vector<ll> pre_sum(N+1,0);
    for(int i=0;i<N;i++) pre_sum[i+1]=pre_sum[i]+a[i];

    ll ans = 0;
    // i是窗口左端点0-based，窗口[i, i+K-1]
    for(int i=0; i+K <= N; i++){
        ll window_sum = pre_sum[i+K] - pre_sum[i];
        ll win_pos = pre_pos[i+K] - pre_pos[i]; //窗口内部正数总和
        ll cur = (total_pos - win_pos) + max(0LL, window_sum);
        ans = max(ans, cur);
    }
    cout << ans << endl;
    return 0;
}
