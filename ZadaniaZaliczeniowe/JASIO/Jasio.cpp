#include <bits/stdc++.h>
#include "Graph.h"

#define INF 9999

using namespace std;

void Solve(){

    int n, k;
    vector<int> skarbonki;              // wczytane skarbonki
    int a, b;

    string path;
    k=0;
    cin>>n;
    if((n < 1) || (n > 1000000)){
        throw std::invalid_argument("Liczba n jest poza zakresem [1, 100000]");
    }

    Graph g(n);

    for(int i=0;i<n;i++){
        cin >>k ;
        if((k >= 1) && (k <= n )){
            skarbonki.push_back(k-1);
            g.addEdge(i, k-1);
        }else{
            throw std::invalid_argument("Zla Numeracja Skarbonek!");
        }
    }

    cout<<"Silnie Spojne Skladowe Grafu Wejsciowego : "<<endl;
    g.printSCC();

    cout<<"Liczba Spojnych Skladowych : "<<endl;
    cout<<g.getSCCnumber();


}



void Testy(string path){
    ifstream file;
    file.open(path);

    int a, b, first;
    int i=0;
    Graph g(100);
    while (!file.eof()){
        if(i==0){
            file>>first;
            g.changeGraph(first);
        }
        file >> a ;
        g.addEdge(i, a-1);
        i++;
    }
    cout<<"Silnie Spojne Skladowe Grafu Wejsciowego: "<<endl;
    g.printSCC();

    cout<<"Liczba Spojnych Skladowych= "<<endl;
    cout<<g.getSCCnumber();


}



int main(){

//Testy("test2.txt");
//Testy("test3.txt");
//Solve();

}
