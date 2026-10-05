import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        try(Scanner sc = new Scanner(System.in)) {
            int N = sc.nextInt();
            int x = sc.nextInt();
            int[] arr = new int[N];
            for (int i = 0; i < N; i++) arr[i] = sc.nextInt();

            int[] best = new int[N];
            System.arraycopy(arr, 0, best, 0, N);

            long ans = Long.MAX_VALUE;
            for (int i = 0; i < N; i++) {
                long sum = 0;
                for (int j = 0; j < N; j++) {
                    int from = (j - i + N) % N;
                    best[j] = Math.min(best[j], arr[from]);
                    sum += best[j];
                }
                ans = Math.min(ans, sum + (long)x * i);
            }

            System.out.println(ans);
        }
    }
}
