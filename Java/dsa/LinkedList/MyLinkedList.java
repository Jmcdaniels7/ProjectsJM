package LinkedList;

// MyLinkedList.java
public class MyLinkedList<T> {
    public Node<T> head;

    public static class Node<T> {
        T data;
        Node<T> next;
        
        Node(T data) {
            this.data = data;
            this.next = null;
        }
    }

}

