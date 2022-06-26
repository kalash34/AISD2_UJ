#pragma once

#include <iostream>
#include <vector>

using namespace std;


class Item{
    public:         //kazdy element klasy item ma klucz i priorytet wedlug ktorego
    int key;        // jest umieszczany w kolejce
    int priority;
    Item(){
        priority =0;
        key=0;
    }
    Item(int p, int k){
        priority = p;
        key = k;
    }
    Item(const Item& other){
     key = other.key;
     priority = other.priority;
    }
};


class PriorityQueue{
    public:


    void print();
    void reheapifyUp(int i);
    void reheapifyDown(int i);
    void pop();                 // wyjmij z kolejki
    void push();                // wloz do kolejki
    Item getMin();              // zdejmij i zwroc minimum z kopca
    int getSize();              // pobierz rozmiar kolejki
    int getCapacity();          // pobierz pojemnosc kolejki
    bool push(int akey, int apr);
    bool updatePriority(int akey, int apr);

    vector<Item> aheap;    //kopiec z danymi
   // int* keys;      //klucze w wezlach kopca
    vector<int> keys;
    int size;       //aktualny rozmiar
    int capacity;   //pojemnosc maksymalna
    int totalKeys;  //calkowita liczba kluczy
    PriorityQueue();
    PriorityQueue(vector<Item> elements, int length);
    PriorityQueue(const PriorityQueue &another);
    PriorityQueue& operator=(const PriorityQueue &another);





};
