// 题意是要求最少总时间，使得通过直接购买缺失颜色或整体循环变色，最终同时拥有全部N种颜色的史莱姆。

import java.util.Scanner;

public class Solution {
public static void main(String[] args) {
        try (Scanner sc = new Scanner(System.in)) {
            int N = sc.nextInt();
            int x = sc.nextInt();
            int[] arr = new int[N];
            for (int i = 0; i < N; i++) {
                arr[i] = sc.nextInt();
            }
            
            // best[j] 表示最终颜色 j 在施法不超过 k 次的前提下，能获得每个颜色的最小捕捉代价
            // 随着 k 增大，best[j] 会不断取更小值
            int[] best = new int[N];
            System.arraycopy(arr, 0, best, 0, N);

            long ans = Long.MAX_VALUE;
            // 枚举施法次数
            for (int k = 0; k < N; k++) {
                long sum = 0;
                for (int j = 0; j < N; j++) {
                // 对每个颜色 j，它可以通过施法 k 次，从原始颜色 (j-k+N)%N 处获得史莱姆
                int from = (j - k + N) % N;
                best[j] = Math.min(best[j], arr[from]);
                sum += best[j];
                }
                // 总代价 = 捕捉代价之和 + 施法代价
                ans = Math.min(ans, sum + (long) x * k);
            }
        
            System.out.println(ans);
        }
    }
}
