// 通过数组创建单链表

import java.util.ArrayList;
import java.util.Scanner;

class ListNode {
    int val;
    ListNode next;
    ListNode(int x) {
        val = x;
    }
}
class ListUtil {
    public static ListNode createLinkedList(int[] arr) {
        if (arr == null || arr.length == 0) return null;

        ListNode head = new ListNode(arr[0]);
        ListNode cur = head;
        for (int i = 1; i < arr.length; i++) {
            cur.next = new ListNode(arr[i]);
            cur = cur.next;
        }
        return head;
    }
}

public class SimpleNode {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
            ArrayList<Integer> list = new ArrayList<>();
            while (sc.hasNextInt()) {
                list.add(sc.nextInt());
            }
    }
}



        