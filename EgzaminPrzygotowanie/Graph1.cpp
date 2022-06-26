#include <bits/stdc++.h>
#include <iostream>
#include <list>
#include <queue>
#include <set>
#include <fstream>
#include <string>


using namespace std;

#define INF 9999

typedef pair<int, int> iPair;

enum Color {WHITE, GRAY, BLACK};
// White color - not visited nodes
// Gray color - about to be visited (keeping them in FIFO queue)
// Black color - visited nodes


class Edge{
    public:
    int source, destination, weight;
    Edge():source(0), destination(0),weight(0){}
    Edge(int s, int d, int w): source(s), destination(d), weight(w){
        source=s;
        destination=d;
        weight=w;
    }

    int getWeight() const {
        return weight;
    }
    int getDest() const {
        return destination;
    }

    friend bool operator>(const Edge& krawedz1, const Edge& krawedz2);
    friend bool operator<(const Edge& krawedz1, const Edge& krawedz2);
    friend bool operator==(const Edge& krawedz1, const Edge& krawedz2);
    friend bool operator!=(const Edge& krawedz1, const Edge& krawedz2);

};


bool operator>(const Edge& krawedz1, const Edge& krawedz2){
    return krawedz1.getWeight() > krawedz2.getWeight();
}
bool operator<(const Edge& krawedz1, const Edge& krawedz2){
    return krawedz1.getWeight() < krawedz2.getWeight();
}
bool operator==(const Edge& krawedz1, const Edge& krawedz2){
    return krawedz1.getWeight() == krawedz2.getWeight();
}
bool operator!=(const Edge& krawedz1, const Edge& krawedz2)
{
    return krawedz1.getWeight() != krawedz2.getWeight();
}


class Graph{

    int V;
    int E;
    list<Edge> *adjList;

public:

    Graph(int numberOfVertices){
        V=numberOfVertices;
        E=0;
        adjList=new list< Edge >[V];

    }


    void addEdge(int u, int v, int wt){
        adjList[u].push_back( Edge(u, v, wt) );
       // adjList[u].push_back( Edge(v, u, wt) );
        E++;
       // E+=2;
    }
    int sumOfEdgesWeights(){
        int suma=0;
        list< Edge > :: iterator it;

        for(int idx=0;idx<V;idx++){
        for(it = adjList[idx].begin(); it != adjList[idx].end();it++) {

        suma+= it->weight;

        }
        }
        return suma;
    }


    void readFromFile(string path){

        ifstream file;
        file.open(path);

        int a, b,c, first;
        int i=0;
        while (!file.eof()){
            if(i==0){
                file>>first;
                this->V = first;
                adjList = new list< Edge >[V];

            }
            file >> a >> b >> c;
            addEdge(a, b, c);
            i++;
        }

    }

    int getNumberOfVertices(){
        return V;
    }


    int getNumberOfEdges(){
        return E;
    }



    vector<int> getNeighbourIndices(int idx){
        vector<int> indeksy_sasiadow;
        list< Edge > :: iterator it;

        for(it = adjList[idx].begin(); it != adjList[idx].end();it++) {

        indeksy_sasiadow.push_back(it->destination);

        }



        return indeksy_sasiadow;	//zwracamy wektor z sasiadami
    }


    void printGraph(){

        cout<<" G = (V, E) :  |V|= "<<V<<" |E|= "<<E<<endl<<endl;

        cout<<"V = { ";
        for(int v=0;v<V;v++){
            cout<<" v_nr= "<<v<<", "<<endl;
        }
        cout<<" }"<<endl;

        cout<<"E = { ";

        for(int i=0;i<V;i++){
            for(auto it=adjList[i].begin();it!=adjList[i].end();it++){
                cout<<"("<<it->source<<", "<<it->destination<<"), "<<endl;
            }
        }


        cout<<" } "<<endl;


    }

    /*
    Dowod Zlozonosci BFS oraz DFS
    (v1 + v2 + ... + vn) + [(incident_edges v1) + (incident_edges v2) + ... + (incident_edges vn)]
    =>
                  O(V)   +   O(E)
    =>
                    O(V) + O(E) = O( V + E )
    */




    // O( V + E )
    void BFS(int idx){

        queue<int> Queue;
        bool visited[V] = {false};
        cout<<"BFS : "<<endl;
        vector<int> sasiedzi;
        visited[idx] = true;
        Queue.push(idx);

        // Odwiedzamy zawsze sasiadow pierwszego elementu w kolejce
        //
        while(!Queue.empty()){

             int v = Queue.front();
             sasiedzi = getNeighbourIndices(v);
             Queue.pop();
             cout<<" "<<v<<" ";
             for(int i=0;i<sasiedzi.size();i++){
                 if( visited[sasiedzi[i]] == false ){
                    Queue.push(sasiedzi[i]);
                    visited[sasiedzi[i]]=true;
                 }
            }
        }

        cout<<endl;
    }

    // O( V + E )
    void DFS(int idx){

        stack<int> Stack;
        bool visited[V]={false};
        cout<<"DFS : "<<endl;
        vector<int> sasiedzi;
        visited[idx]=true;
        Stack.push(idx);

        while(!Stack.empty()){                  //
             int v= Stack.top();
             sasiedzi = getNeighbourIndices(v);
             Stack.pop();
             cout<<" "<<v<<" ";

             for(int i=0;i<sasiedzi.size();i++){
                 if( visited[sasiedzi[i]] == false ){
                    Stack.push(sasiedzi[i]);
                    visited[sasiedzi[i]]=true;

                 }

            }
        }

        cout<<endl;
    }



    // Algorytm przechodzi Graf identycznie jak BFS
    // => zloznosc czasowa O ( V + E )
    void TopologicalSort(){
        cout<<"Sortowanie Topologiczne: "<<endl;
        int *indegree=new int[V]{0};
        //
        for(int i=0;i<V;i++){
            for(auto it=adjList[i].begin();it!=adjList[i].end();it++){
                indegree[it->source]++;
            }
        }
        queue< int > q;
        for(int i=0;i<V;i++){
            if(indegree[i]==0){
                q.push(i);
            }
        }
        while(!q.empty()){
            int f=q.front();
            cout<<f<<" ";
            q.pop();
            for(auto it=adjList[f].begin();it!=adjList[f].end();it++){
                indegree[it->source]--;
                if(indegree[it->source]==0){
                    q.push(it->source);
                }
            }
        }
        cout<<endl;
        }


        bool DFSUtil(int u, int color[])
        {
            color[u] = GRAY;
            for (auto i = adjList[u].begin(); i != adjList[u].end(); ++i)
            {

                int v = i->destination;

                if (color[v] == GRAY){
                  return true;
                }
                if (color[v] == WHITE && DFSUtil(v, color)){
                  return true;
                }
            }
            color[u] = BLACK;

            return false;
        }
        void PrintDFSUtil(int u, int color[]){
            //aktualny wierzcholek w trakcie odwiedzania
            color[u] = GRAY;
            cout<< u << " ";
            for (auto i = adjList[u].begin(); i != adjList[u].end(); ++i)
            {

                int v = i->destination;
                if (color[v] == WHITE){
                    PrintDFSUtil(v, color);
                }
            }
            color[u] = BLACK;

        }

        bool isCyclic()
        {
            int *color = new int[V];
            for (int i = 0; i < V; i++){
                color[i] = WHITE;
            }

            for (int i = 0; i < V; i++)
                if (color[i] == WHITE)
                   if (DFSUtil(i, color) == true)
                      return true;

            return false;
        }

        void printPath(int parent[], int j)
        {
        if (parent[j] == - 1 || j<0){
                return;
        }
        printPath(parent, parent[j]);
        printf("-> %d", j);
        }
        // Zlozonosc czasowa O ( E log V )
        void Dijkstra(int s, int d){

               int dist[V], prev[V];
               int start = s;
               int docelowy=d;

               prev[s]=-1;
               for(int u = 0; u<V; u++) {
                  dist[u] = INF;

               }

               dist[start] = 0;
               set<int> S;
               list<int> Q;

               for(int u = 0; u<V; u++) {
                  Q.push_back(u);
               }

               while(!Q.empty()) {
                  list<int> :: iterator i;
                  i = min_element(Q.begin(), Q.end());
                  int u = *i;
                  Q.remove(u);
                  S.insert(u);
                  list< Edge > :: iterator it;

                  for(it = adjList[u].begin(); it != adjList[u].end();it++) {
                     if((dist[u]+(it->weight)) < dist[it->destination]) {
                        dist[it->destination] = (dist[u]+(it->weight));
                        prev[it->destination] = u;
                     }
                  }
           }


           for(int i = 0; i<V; i++){
              if(i != start){
                 cout<<start<<" -> "<<i<<", Koszt: "<<dist[i]<<" Poprzedni: "<<prev[i]<<endl;
              }
           }

           cout<<endl<<"Najkrotsza sciezka dla miedzy "<<start<<" oraz "<<docelowy<<" : "<<endl;
           cout<<start;
           printPath(prev, docelowy);
           cout<<endl;
        }

        void printMatrix(vector < vector<int> > matrix) {

            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                if (matrix[i][j] == INF){
                printf("%4s", "INF");
                }
                else{
                printf("%4d", matrix[i][j]);
                }
            }
            printf("\n");
        }
        }
        // Zlozonosc czasowa dla 3 petli O ( V ^ 3 )
        //

        void FloydWarshall(){
        //konwertujemy liste sasiedztwa na macierz
        vector<vector<int> > matrix(V, vector<int>(V, INF));
        list< Edge > :: iterator it;

        for (int i = 0; i < V; i++) {

            for (it = adjList[i].begin(); it != adjList[i].end();it++){

                if(i==it->source){
                    matrix[i][i] = 0;

                }
                matrix[i][it->destination] = it->weight;

            }

        }
        cout<<"Macierz Wejsciowa Floyda Warshalla : "<<endl;
        printMatrix(matrix);

        for(int k=0;k< V;k++){
            for(int i=0;i< V; i++){
                for(int j=0;j<V;j++){
                    if(matrix[i][k] + matrix[k][j] < matrix[i][j]){
                        matrix[i][j] = matrix[i][k] + matrix[k][j];
                    }

                }
            }
        }

    cout<<"Macierz Wyjsciowa Floyda Warshalla : "<<endl;
        printMatrix(matrix);

    }


    void PrimMST()
    {
    // kolejka priorytetowa za pomoca kopca, zeby to zrobic w stl mozna uzyc takiego przejscia
    // operator greater sluzy do zwracania operatora porownania

    priority_queue< iPair, vector <iPair> , greater<iPair> > pq;
    Graph tree(V);                                                  //Obiekt drzewa MST

    int src = 5;                                                    // Wierzcholek zrodlowy

    // Stworz wektor kluczy i inicjalizuj wszystkie klucze
    // jako INF
    vector<int> key(V, INF);

    //tablica rodzicow
    vector<int> parent(V, -1);

    // wierzcholki zawarte w MST
    vector<bool> inMST(V, false);

    // zbior wierzcholkow MST
    set<int> B;

    B.insert(src);

    // Wloz wierzcholek zrodlowy do kolejki priorytetowej
    // i zainnicjalizuj klucz jako zero
    pq.push(make_pair(0, src));
    key[src] = 0;

    int cr=0;           //waga drzewa MST

    // Iteruj dopoki kolejka priorytetowa nie bedzie pusta
    while (!pq.empty())
    {

        int v, par, minimum;
        // Pierwszy wierzcholek w parze to klucz minimum,
        // Opuszcza on kolejke priorytetowa.
        // Id wierzcholka przechowywane jest w drugim elemencie pary.
        // (Musi byc to tak zrobione zeby utrzymac posortowane klucze wierzcholkow.
        // (klucz, musi byc pierwszym elementem w parze)


        int u = pq.top().second;
        pq.pop();


          // Rozne wartosci kluczy dla tego samego wierzcholka moga byc w kolejce priortetowej.
          // Ten z najmniejsza wartoscia klucza jest przetwarzany najpierw.
          // Dlatego ignorujemy reszte



        if(inMST[u] == true){
            continue;
        }

        inMST[u] = true;  // dodaj wierzcholek do MST

        //  iterator po liscie sasiedzwta
        list< Edge >::iterator it;
        for (it = adjList[u].begin(); it != adjList[u].end(); ++it)
        {

            // Pobierz indeks wierzcholka i wage krawedzi z Listy Sasiedztwa
            //
            int v = it->destination;
            int weight = it->weight;

            // Jezeli v nie jest w MST oraz waga (u,v) jest mniejsza
            // niz aktualny klucz v
            if (inMST[v] == false && key[v] > weight)
            {
                // zmieniamy klucz dla wierzcholka v
                key[v] = weight;
                minimum=weight;

                pq.push(make_pair(key[v], v));
                parent[v] = u;
                par = u ;
            }
        }
        cr+=minimum;
        B.insert(v);    // do zbioru dodajemy wierzcholki docelowe
        tree.addEdge(par, v, minimum);

    }


    // Wypisz krawedzie MST uzywajac tablicy rodzicow

    cout<<"Krawedzie Drzewa MST: "<<endl;
    for (int i = 1; i < V; ++i){
        printf("(%d , %d) \n", parent[i], i);
    }
    cout<<"Waga drzewa MST: "<<tree.sumOfEdgesWeights();

    cout<<"Waga 2 drzewa MST: "<<cr<<endl;

    }



    void ConnectedComponents(){

        int *color = new int[V];
        for (int i = 0; i < V; i++){
            color[i] = WHITE;
        }

        for (int v = 0; v < V; v++){
            if (color[v] == WHITE){
                PrintDFSUtil(v, color);
                    cout<<endl;
            }
        }

    }

    int NumberOfconnectedComponents()
    {

        int liczbaSpojnychSkladowych=0;
        int *color = new int[V];
        for (int v = 0; v < V; v++){
            color[v] = WHITE;
        }
        for(int v=0;v<V;v++){
            if(color[v] == WHITE ){
                DFSUtil(v, color);
                liczbaSpojnychSkladowych++;
            }
        }
        return liczbaSpojnychSkladowych;

    }




};


void test1(){
    Graph g(100);
    cout<<"Graf z pliku"<<endl;
    g.readFromFile("Graf1.txt");

    cout<<"Test Na Obecnosc Cyklu: "<<endl;
    cout<<g.isCyclic();
    cout<<endl;

}

void test2(){

    cout<<"Graf z pliku"<<endl;
    Graph g(100);

    //chcemy sciezke z wierzcholka 5 do 8

    g.readFromFile("Graf3.txt");
    g.Dijkstra(8,5);
    //g.displayEdges();
}
void test3(){
    Graph g(100);

    g.readFromFile("Graf2.txt");
    g.TopologicalSort();
    //g.readFromFile("Graf3.txt");
    //g.topologicalSort();

}


void test4(){
    Graph g(100);
    g.readFromFile("GrafTest23.txt");
    g.FloydWarshall();
    g.BFS(0);
    g.DFS(0);
    //g.readFromFile("Graf3.txt");
    //g.topologicalSort();
}


void test5(){
    Graph g(100);
    g.readFromFile("GrafMST_JawneKrawedzie4.txt");
    g.PrimMST();



}

void test6(){
    Graph g(100);
    g.readFromFile("GrafG6.txt");
    cout<<"Spojne Skladowe Grafu= "<<endl;

    g.ConnectedComponents();

    cout<<"Liczba Spojnych Skladowych= "<<g.NumberOfconnectedComponents()<<endl;

}

int main()
{
    //test5();
    test6();


    return 0;
}