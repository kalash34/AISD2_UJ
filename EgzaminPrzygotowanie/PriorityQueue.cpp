#include <iostream>
#include <string>
#include "priorityqueue.h"
#include <vector>

using namespace std;


PriorityQueue::PriorityQueue(std::vector<Item> elements, int length){
			//Bierze wskaznik do tablicy z obiektami Item i tworzy z tego kopiec
	if(elements.empty()){
		return;
	}
	int firstParent = (length - 2)/2;

	aheap = vector<Item>(length);
	keys = vector<int>(length);
	size = length;
	capacity = length;
	totalKeys = length;

	for(int i = 0; i < length; i++){
		aheap[i] = elements[i];
		int ind = aheap[i].key;
		keys[ind] = i;
	}
	for(int j = firstParent; j >= 0; j--)
		reheapifyDown(j);

}
PriorityQueue::PriorityQueue(const PriorityQueue &another){

	int length = another.size;
	aheap = vector<Item>(length);
	keys = vector<int>(length);
	size = length;
	capacity = length;
	totalKeys = length;
	for(int i = 0; i < length; i++){
		aheap[i] = another.aheap[i];
		int ind = another.aheap[i].key;
		keys[ind] = i;
	}
}
PriorityQueue& PriorityQueue::operator=(const PriorityQueue &another){

	int length = another.size;
	aheap = vector<Item>(length);
	keys = vector<int>(length);
	size = length;
	capacity = length;
	totalKeys = length;
	for(int i = 0; i < length; i++){
		aheap[i] = another.aheap[i];
		int ind = another.aheap[i].key;
		keys[ind] = i;
	}
	return *this;
}


//Funkcje skladowe klasy

void PriorityQueue::print(){
	for(int i = 0; i < (getSize()); i++){
		cout << aheap[i].priority << " ";
	}
	cout << endl;
	for(int i = 0; i < (getSize()); i++){
		cout << aheap[i].key << " ";
	}
	cout << endl;
	for(int i = 0; i < (totalKeys); i++){
		cout << keys[i] << " ";
	}
	cout << endl;
}

//	Kopcowanie w Gore bierze indeks tablicy reprezentujacej kopiec wedlug ktorego
//  kopcuje w gore
void PriorityQueue::reheapifyUp(int i){
	if(i != 0){
		int parent = (i-1)/2;
		if(aheap[parent].priority > aheap[i].priority){
			swap(keys[aheap[parent].key], keys[aheap[i].key]);
			swap(aheap[i], aheap[parent]);
			reheapifyUp(parent);
		}
	}
}


// Kopcowanie w Dol bierze indeks tablicy reprezentujacej kopiec wedlug ktorego
// kopcuje w gore

void PriorityQueue::reheapifyDown(int i){
    int l = 2*i+1;
    int r = 2*i+2;
    int min = i;
    if(l < size && aheap[l].priority < aheap[i].priority){
    	min = l;
    }
    if(r < size && aheap[r].priority < aheap[min].priority){
    	min = r;
    }
    if(min !=i){
    	swap(keys[aheap[min].key], keys[aheap[i].key]);
    	swap(aheap[i], aheap[min]);
        reheapifyDown(min);
     }
}

void PriorityQueue::pop(){
	keys[aheap[size-1].key] = keys[aheap[0].key];
	keys[aheap[0].key] = -1;
	aheap[0] = aheap[size - 1];
	size--;
	if(getSize() > 0){
		reheapifyDown(0);
	}
}
//Kolejka Na kopcu minimalnym, wiec minimum znajduje sie w korzeniu

//
Item PriorityQueue::getMin(){
	return aheap[0];
}

bool PriorityQueue::push(int akey, int apr){
	if(akey == totalKeys){
		if(getSize() == getCapacity()){
			capacity *= 2;
			vector<Item> temp= vector<Item>(capacity);
			vector<int> tempKey=vector<int>(capacity);
			for(int i = 0; i < getSize(); i++){
				//kopiuj dalej
				temp[i]= aheap[i];
				tempKey[i] = keys[i];
			}

			aheap = temp;
			keys = tempKey;
      temp.clear();
      tempKey.clear();
			}
		aheap[size] = Item(akey, apr);
		keys[aheap[size].key] = size;
		reheapifyUp(size);
		size++;
		totalKeys++;
		return true;
		}
	return false;
}


bool PriorityQueue::updatePriority(int akey, int apr){
	if(aheap[keys[akey]].priority < apr){
		return false;
	}
	else if(keys[akey] == -1){
		return false;
	}
	aheap[keys[akey]].priority = apr;
	reheapifyUp(keys[akey]);
	return true;
}


int PriorityQueue::getSize(){
	return size;

}


int PriorityQueue::getCapacity(){
	return capacity;

}







int main(){
    //tablica abstrakcyjnych obiektow
    cout<<"Poszlo"<<endl;
    vector<Item> elementy = vector<Item>(100);
    for(int i=0;i<100;i++){
        elementy[i].key=i*i;
        elementy[i].priority=i;
    }



    PriorityQueue kolejka = PriorityQueue(elementy, 100);
    for(int i=0;i<100;i++){
       kolejka.push(i,i*i);
    }
    kolejka.print();





}
