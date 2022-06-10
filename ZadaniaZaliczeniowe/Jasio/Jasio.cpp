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

    int a, n;
    string wejscie;
    if (!file)
    {
    cerr << "Brak Znalezionego Pliku!";
    }
    else
    {
    getline(file, wejscie);
    file.close();
    }
    n = stoi(wejscie);
    if((n < 1) || (n > 1000000)){
        throw std::invalid_argument("Liczba n jest poza zakresem [1, 100000]");
    }
    Graph g(n);
    cout<<"jest"<<endl;
    file.open(path);

    int i=0;
    while (!file.eof()){

        if(i>0){

        file >> wejscie ;
        a=stoi(wejscie);

        if((a >= 1) && (a <= n )){

            g.addEdge(i-1, a-1);
            cout<<i-1<<" "<<a-1<<endl;
        }else{
            throw std::invalid_argument("Zla Numeracja Skarbonek!");
        }
        }

        i++;

    }

    g.printSCC();
    cout<<g.getSCCnumber();

}


void readFromFile(string path)
{
    ifstream myFile;
    myFile.open(path);
    string line;

    int n=0;
    int a=0;
    if (!myFile)
    {
    cerr << "Brak Znalezionego Pliku!";
    }
    else
    {
    getline(myFile, line);
    myFile.close();
    }
    n = stoi(line);
    if((n < 1) || (n > 1000000)){
        throw std::invalid_argument("Liczba n jest poza zakresem [1, 100000]");
    }
    Graph g(n);

    myFile.open(path);
    int i = 0;
    while (getline(myFile, line))
    {
        if(i!=0){
        istringstream iss(line);
        string skarbonka;
        iss>>skarbonka;
        a = stoi(skarbonka);
        if(a>=1 && a<=n){

            g.addEdge(i-1, a-1);
        }else{
            throw std::invalid_argument("Zla Numeracja Skarbonek!");
        }
        }


        i++;
    }
    g.printSCC();
    cout<<g.getSCCnumber()<<endl;
}

int main(){

//Solve();

readFromFile("test2.txt");
readFromFile("test3.txt");


}
