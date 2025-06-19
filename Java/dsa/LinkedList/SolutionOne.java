package LinkedList;
import LinkedList.MyLinkedList.Node;

class Practice {
    public void printList(MyLinkedList<Integer> list) {
        Node<Integer> current = list.head;
        while (current != null) {
            System.out.print(current.data + " -> ");
            current = current.next;
        }
        System.out.println("null");
    }
    Node<Integer> addTail(MyLinkedList.Node<Integer> head, int data)
    {
        MyLinkedList.Node<Integer> newTail = new MyLinkedList.Node<Integer>(data);
        if(head == null)
        {
            return newTail;
        }
        
        MyLinkedList.Node<Integer> current = head;

        while(current.next != null)
        {
            current = current.next;
        }

        current.next = newTail;

        return head;
    }

    Node<Integer> addNodeAtPos(Node<Integer> head, int position, int data)
    {
        Node<Integer> pos = new Node<Integer>(data);
        int count = 0;

        if(position < 1)
        {
            return pos;
        }

        Node<Integer> current = head;

        while(current.next != null)
        {
            if(count == position -1)
            {
                break;
            }
            current = current.next;
            count++;
        }

        pos.next = current.next;
        current.next = pos;

        return head;

    }

    Node<Integer> addNodeAtHead(Node<Integer> headPointer, int data)
    {
        Node<Integer> newHead = new Node<Integer>(data);
        if(headPointer == null)
        {
            return newHead;
        }

        newHead.next = headPointer;
        headPointer = newHead;

        return headPointer;
    }

    Node<Integer> deleteNode(Node<Integer> headPointer, int pos)
    {
        Node<Integer> current = headPointer;

        if(current == null)
        {
            return null;
        }

        int count = 0; 

        //O(n) runtime
        while(current.next != null)
        {
            if(count == pos)
            {
                break;
            }
            current = current.next;
            count++;
        }

        current.data = current.next.data;
        current.next = current.next.next;

        return headPointer;

    }
}

public class SolutionOne {
    public static void main(String args[])
    {
        MyLinkedList<Integer> list = new MyLinkedList<>();

        Node<Integer> node1 = new Node<>(20);
        Node<Integer> node2 = new Node<>(20);
        Node<Integer> node3 = new Node<>(30);

        list.head = node1;

        node1.next = node2;
        node2.next = node3;

        Practice ob = new Practice();

        // output works as a log so you can see what happend compared to the last linked list
        ob.printList(list);

        //add tail
        ob.addTail(list.head, 0);
        ob.printList(list);

        //add a node at a given position
        ob.addNodeAtPos(list.head, 2, 11);
        ob.printList(list);

        //add node at head
        Node<Integer> llist = ob.addNodeAtHead(list.head, 21);

        list.head = llist;

        ob.printList(list);

        //delete a give node
        Node<Integer> lilist = ob.deleteNode(list.head, 2);

        list.head = lilist;

        ob.printList(list);

    }
    
}
