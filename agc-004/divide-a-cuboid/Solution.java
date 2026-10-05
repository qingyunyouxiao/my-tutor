// 题意是给出一个边长ABC的立方体，以一个面来切分成两部分，要求这两部分体积之差最小。

import java.util.Scanner;

public class Solution {
    public static void main(String[] args) {
        try (Scanner sc = new Scanner(System.in)) {
            long a = sc.nextLong();
            long b = sc.nextLong();
            long c = sc.nextLong();
            
            // 检查是否有偶数
            if (a % 2 == 0 || b % 2 == 0 || c % 2 == 0) 
                System.out.println(0);
            else {
                // 计算两两乘积的最小值
                long min = Math.min(Math.min(a * b, b * c), a * c);
                System.out.println(min);
            }
        }
    }
}