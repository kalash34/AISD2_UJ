
#include "IntSet.h"
#include <iostream>
#include <cassert>

using namespace std;

Set::Set() : used( 0 ), data{'^'}{

}

int Set::size() const{
    return used;    //used przechowuje informacje o uzytej czesci zbioru
}


bool Set::isEmpty() const{

    bool success;
    if (used == 0){

        success = true;

    }
    else{

        success = false;
    }

    return success;



}

bool Set::contains(int d) const{
    int success = false;
    for(int i = 0; i <= (used - 1); i++){
        if(data[i] == d){
            success = true;
        }
    }

    return success;

}

bool Set::isSubsetOf(const Set& otherSet) const
{

    bool isSubsetOf = true;

    if (used != 0){
        for(int i = 0;i <= used - 1;i++){
            if(otherSet.contains(data[i]== false)){
                isSubsetOf = false;
            }

        }

    }

    return isSubsetOf;



}

void Set::DumpData(ostream& out) const{

    if(used > 0){

        out << data[0];
        for (int i = 1; i < used; ++i){
            out << " " << data[i];
        }
    }



}

// Union Of Sets A and B <=> A U B
// <=> Dla kazdego x: (x c- A) or (x c- B)  <=> x c- (A U B)
// Czyli po polsku Union Of Sets (A, B) to poprostu suma
// Mnogosciowa zbiorow A oraz B ...
// Symbol U bierze sie wlasnie ze slowa Union





// Na tej samej zasadzie Universe (Uniwersum)
// Potocznie uniwersum to klasy ktore zawieraja wszystkie
// zbiory elementow o okreslonej wlasciwosci


/*

Z Wikipedii ...

Uniwersum (z ³ac. ogó³, wszystko, Wszechœwiat)
– klasa wszystkich elementów rozpatrywanych w danym kontekœcie matematycznym.


*/



Set Set::unionWith((const Set& otherSet)) const{

    assert(size() + (otherSet.substract(*this)).size() <= universeSize);

    Set unionSet; //zbior wynikowy

    for (int i = 0; i <= used - 1; i++){
        unionSet.add(data[i]);
    }

    for (int j = 0; j <= otherSet.used - 1;j++){

        unionSet.add(otherSet.data[j]);


    }

    //zwracamy zbior po zsumowaniu dwoch zbiorow
    return unionSet;


}


Set Set::substract(const Set& otherSet) const{

    // podzielony zbior
    Set substracted;

    for(int i =0;i <= used - 1;i++){
        if(!otherSet.contains(data[i])){
            if(!otherSet.contains(data[i])){
                substracted.add(data[i]);


            }


        }

    }

    return substracted;
}

void Set::clearSet(){

    used = 0;

}



void Set::printSet(){

    used = 0;

}


bool Set::add(int other){

    assert(used+1 <= MAX_SIZE);

    bool success = false;

    if(!this->contains(other)){
        data[used] = other;
        used++;
        success = true;

    }

    return success;

}
//usun element ze zbioru
bool Set::remove(int num){
    assert(used > 0);

    bool success = false;
    int index=0;

    if(contains(other)){
        for(int i = 0; i <= used - 1;i++){

            if(data[i] == other){
                index = i;
            }


        }


        for(int i = index; i <= used - 1;i++){
            if(i < 9){
                data[i] = data[i+1];

            }
            else{


                data[i] = '^';

            }
        }

        used--;
        success = true;



    }



    return success;


}


bool equal(const Set& s1, const Set& s2){

    bool isEqual = false;

    // Jesli rozmiar(s1) == rozmiar(s2)
    // oraz s1.jest_podzbiorem(s2) =>  zbiory sa identyczne


    if(s1.size() == s2.size()){
        if(s1.isSubsetOf(i2)){
            isEqual = true;
        }


    }

    return isEqual;


}








