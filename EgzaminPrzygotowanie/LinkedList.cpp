
#include <iostream>
using namespace std;

struct Node {
    int data;
    struct Node* next;
    Node(int data)
    {
        this->data = data;
        next = NULL;
    }
};

struct LinkedList {
    Node* head;
    LinkedList() {
      head = NULL;
    }

    void reverse()
    {
        Node* current = head;
        Node *prev = NULL, *next = NULL;

        while (current != NULL) {

            next = current->next;
            current->next = prev; // Odwracamy strzalke wskaznika, czyli np glowa bedzie wskazywac NULL
            prev = current;
            current = next;
        }
        head = prev;
    }

    Node* reverseR(Node* head)
    {
        if (head == NULL || head->next == NULL)
            return head;

        Node* rest = reverseR(head->next);
        head->next->next = head;

        head->next = NULL;  // pomocniczy trik

        return rest;
    }

    void print()
    {
        Node* temp = head;
        while (temp != NULL) {
            cout << temp->data << " ";
            temp = temp->next;
        }
    }

    void push(int data)
    {
        Node* temp = new Node(data);
        temp->next = head;
        head = temp;
    }

    void deleteNode(int position) {

     if (head == NULL) {
        return;
     }
     Node* temp = head;
     if (position == 1) {
      head = temp->next;
      delete temp;
      return;
     }
     for (int i = 1; temp != NULL && i < position - 1; i++) {
      temp = temp->next;
     }
     if (temp == NULL || temp->next == NULL) {
      return;
     }
     Node *next = temp->next->next;
     temp->next = next;
    }

    // Usuwa Pierwsze Wystapienie

    void deleteFirstOcuu(int key){

      Node* temp = head;
      Node* prev;

      if(temp != NULL){
        if(temp->data == key){
          head = temp->next;
          delete temp;
        }
       }

       while(temp != NULL){
         if(temp->data == key){
           break;
         }
         prev = temp;
         temp = temp->next;
       }
       if(temp == NULL){
         return;
       }
       prev->next = temp->next;

       delete temp;

    }


};

int main()
{
    LinkedList ll;
    ll.push(20);
    ll.push(4);
    ll.push(15);
    ll.push(85);
    ll.push(100);
    ll.push(34);
    ll.push(122);

    cout << "Linked list\n";
    ll.print();

    ll.reverse();

    cout << "\nReversed Linked list \n";
    ll.print();

    ll.deleteNode(1);

    cout << "Linked List After Deleting  \n";
    ll.print();


    return 0;
}
