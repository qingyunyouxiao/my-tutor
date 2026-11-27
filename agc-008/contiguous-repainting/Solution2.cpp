# include <vector>
# include <iostream>
# include <algorithm>
using namespace std;

int main() {
    int N, K;
    cin >> N >> K;
    vector <long long> a(N);
    for (int i = 0; i < N; ++i) cin >> a[i];

    // pre_pos：前i个里面所有正数的和
    vector<long long> pre_pos(N + 1, 0);
    for (int i = 0; i < N; ++i) {
        // 前缀和
        pre_pos[i+1] = pre_pos[i] + max(0LL, a[i]);
    }
    long long all_pos = pre_pos[N];
    
    long long ans = 0;
    // pre_sum：普通前缀和，算区间总和
    vector<long long> pre_sum(N + 1, 0);
    for (int i = 0; i < N; i++) {
        pre_sum[i+1] = pre_sum[i] + a[i];
    }

    long
}