// PLIK NAGLOWKOWY DLA KLASY ZBIORU
// Implementacja zbioru operta o tablice




#ifndef SET_ARR_H
#define SET_ARR_H


#include <iostream>

class Set{

    public:

        static const int universeSize = 100;
        Set();
        const int size();
        const bool isEmpty();
        const bool contains(int d);
        bool equal(const Set& s1, const Set& s2);
        const isSubsetOf(const Set& otherSet);
        const void DumpData(std::ostream& out);
        Set unionWith(const Set& otherSet);
        Set intersect(const Set& otherSet);
        Set substract(const Set& otherSet);
        void clearSet();
        void printSet();
        bool add(int d);
        bool remove(int num);

    private:
        int data[universeSize];
        int used;

};
/*

#pragma once
#include <iostream>
class setArr
{
int size;
const int universeSize = 100;
bool* table;
bool checkRangeCorrectness(int x);
public:
	setArr();
	void insert(int x);
	void withdraw(int x);
	bool isInSet(int i);
	int getSize();
	void clearSet();
	void printSet();
	setArr operator+(setArr& object);
	setArr operator*(setArr& object);
	setArr operator-(setArr& object);
	bool operator==(setArr& object);
	bool operator <= (setArr& object);
};










*/









#endif // SET_ARR_H



