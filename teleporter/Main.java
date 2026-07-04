// AGC 004 D 
// 遍历贪心 + 基环树的深度优先搜索（DFS）
// 有一个 n 个点 n 条边的有向连通图，请你修改一些边的终点，使得对于任何一个点，都存在一条长度为 k 的到达点 1 的路径。

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

@SuppressWarnings("unchecked")
public class Main {
    static int n, K;
    static int[] a;
    static List<Integer>[] children; // 创建一个数组，数组的元素类型是可以存放整数的列表
    static int ans = 0;
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        ans = 0;
        n = sc.nextInt();
        K = sc.nextInt();
        a = new int[n + 1]; // 让数组索引、数组长度与城市编号对应
        children = new ArrayList[n + 1]; // 使用数组 + ArrayList

        for (int i = 1; i <= n; i++) {
            a[i] = sc.nextInt();
            children[i] = new ArrayList<>(); // 菱形语法
        }
            
        if (a[1] != 1) {
            ans++;
            a[1] = 1;
        }
        for (int i = 2; i <= n; i++)
            children[a[i]].add(i); // 连接到父节点

        dfs(1);
        System.out.println(ans);
    }
    
    static int dfs(int currentCity) {
        int maxDepth = 0;

        for (int child : children[currentCity]) { // 遍历所有子城市，是否存在根节点
            int childDepth = dfs(child); 
            maxDepth = Math.max(maxDepth, childDepth + 1);
        }

        if (currentCity != 1 && maxDepth == K - 1 && a[currentCity] != 1) {
            ans++;
            return -1; // 标记当前城市被切断，父节点忽略这个子树
        }
        return maxDepth;
    }
}