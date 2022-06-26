#include<iostream>
#include<list>
#include<set>
#include <fstream>
#include <string>

using namespace std;

typedef struct nodes {
   int dest;
   int cost;
}node;

class Graph {
   int n;
   list<node> *adjList;
   private:
      void showList(int src, list<node> lt) {
         list<node> :: iterator i;
         node tempNode;

         for(i = lt.begin(); i != lt.end(); i++) {
            tempNode = *i;
            cout << "( [ " << src << " , "<<tempNode.dest << "] waga= "<<tempNode.cost<<" ) ";
         }
         cout << endl;
      }

   public:
      Graph() {
         n = 0;
      }

      Graph(int nodeCount) {
         n = nodeCount;
         adjList = new list<node>[n];
      }

      void addEdge(int source, int dest, int cost) {
         node newNode;
         newNode.dest = dest;
         newNode.cost = cost;
         adjList[source].push_back(newNode);
         printf("Dodano krawedz (%d,%d,%d). \n",source , dest,cost);
      }

      void displayEdges() {

         for(int i = 0; i<n; i++) {

            list<node> tempList = adjList[i];
            showList(i, tempList);
         }
      }


      int sumOfEdgesWeights() {

         int sum=0;
         list<node> :: iterator it;
         node tempNode;


         for(int i = 0; i<n; i++) {
            list<node> tempList = adjList[i];
            for(it = tempList.begin(); it != tempList.end(); it++) {
            tempNode = *it;
            sum+=tempNode.cost;
            }
         }
         return sum;
      }



      friend Graph primsMST(Graph g, int start);


      void readFromFile(string path){

        ifstream file;
        file.open(path);

        int a, b,c, first;
        int i=0;
        while (!file.eof()){
            if(i==0){
                file>>first;
                this->n = first;
                adjList = new list<node>[n];

            }
            file >> a >> b >> c;
            addEdge(a, b, c);
            i++;
        }

     }
};

set<int> difference(set<int> first, set<int> second) {
   set<int> :: iterator it;
   set<int> res;

   for(it = first.begin(); it != first.end(); it++) {
      if(second.find(*it) == second.end())
         res.insert(*it);
   }                          // dodaj te elementy ktorych nie ma w drugim sbiorze

   return res;
                  // zbior (pierwszy - drugi )
}

Graph primsMST(Graph g, int start) {
   cout<<endl;
   cout<<"Algorytm Prima znajdowania MST Grafu "<<endl;
   cout<<"Wybrany wierzcholek startowy, start= "<<start<<endl;
   int n = g.n;
   set<int> B, N, diff;
   Graph tree(n);
   B.insert(start);
                        // Stworz drzewo przez obiekt klasy Graf
                        // dodaj wierzcholek startowy do zbioru B
   for(int u = 0; u<n; u++) {
      N.insert(u);
                    // dodaj wszystkie wierzcholki do zbioru N
   }

   while(B != N) {
      int min = 9999;             //ustaw nieskonczonosc
      int v, par;
      diff = difference(N, B);    //znajdz zbior N - B

      for(int u = 0; u < n; u++) {
         if(B.find(u) != B.end()) {
            list<node>::iterator it;
            for(it = g.adjList[u].begin(); it != g.adjList[u].end(); it++) {
               if(diff.find(it->dest) != diff.end()) {
                  if(min > it->cost) {
                     min = it->cost;    //aktualizuj koszt
                     par = u;
                     v = it->dest;
                  }
               }
            }
         }
      }

      B.insert(v);
      tree.addEdge(par, v, min);
      tree.addEdge(v, par, min);
   }
   return tree;
}

void test1(){

   Graph g(18), tree(18);
   g.readFromFile("GrafMST_JawneKrawedzie4.txt");
   tree = primsMST(g, 5);
   tree.displayEdges();
   cout<<"Waga drzewa MST = "<<tree.sumOfEdgesWeights();


}


int main() {

   test1();

}
