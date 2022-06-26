#include <bits/stdc++.h>
using namespace std;

struct QNode {
    int data;
    QNode* next;
    QNode(int d)
    {
        data = d;
        next = NULL;
    }
};

struct Queue {
    QNode *front, *rear;
    Queue()
    {
        front = rear = NULL;
    }

    void EnQueue(int x)
    {

        QNode* temp = new QNode(x);

        if (rear == NULL) {
            front = rear = temp;
            return;
        }

        rear->next = temp;
        rear = temp;
    }

    void DeQueue()
    {
        if (front == NULL){
            return;
        }
        QNode* temp = front;
        front = front->next;

        if (front == NULL){
            rear = NULL;
        }

        delete (temp);
    }

    void Reverse(){
      if(front == NULL || front->next == NULL){
        return;
      }
      // pomocnicze current, prev, next
      QNode* current = front;
      QNode* prev, next = NULL;

      while(current != NULL){
        // przechowaj next
        next = current->next;
        // odwracamy wskaznik
        current->next = prev;
        // przesuwamy o krok do przodu
        prev = current;
        current = next;

      }
      head = prev;

    }

};


// Roznica Miedzy Kolejka Na Liscie Wiazanej A Lista Wiazana Jest taka, ze
// W kolejce mamy dostep tylko do pierwszego i ostatniego elementu, i tylko na poczatek i koniec mozemy
// dodawac, usuwac elementy.

// Na zwyklej liscie mozemy dodawac w dowolnym miejscu. Kolejnosc wstawiania nie ma znaczenia.

int main()
{

    Queue q;
    q.EnQueue(10);
    q.EnQueue(20);
    q.DeQueue();
    q.DeQueue();
    q.EnQueue(30);
    q.EnQueue(40);
    q.EnQueue(50);
    q.DeQueue();
    cout << "Queue Front : " << (q.front)->data << endl;
    cout << "Queue Rear : " << (q.rear)->data;
}
