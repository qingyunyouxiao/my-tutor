// 双链表

import java.util.Scanner;

public class ListNode {
    public static void main(String[] args) {
        try (Scanner sc = new Scanner(System.in)) {
            int ans = sc.nextInt();
            
            System.out.println(ans);
        }
    }
}

class Node<E> {
    E val;
    Node<E> next;
    Node<E> prev;

    Node(Node<E> prev, E element, Node<E> next) {
        this.val = element;
        this.next = next;
        this.prev = prev;
    }
}