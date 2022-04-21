#include <bits/stdc++.h>
#include <iostream>
#include <list>
#include <queue>
#include <fstream>
#include <string>

using namespace std;

#define INF 9999
enum Color {WHITE, GRAY, BLACK};

class Vertex{
    int idx;
    vector<int> neighbours;
public:
    Vertex(int idx){
        this->idx=idx;
        neighbours={0};

    }
    Vertex(int idx, vector<int> neighbours){
        this->idx=idx;
        this->neighbours=neighbours;
    }
    bool hasNeighbours(){

        if(neighbours.size()==0){
            return false;
        }
        return true;

    }
    int numberOfNeighbours(){
        return neighbours.size();
    }

    void addNeighbour(int idx){
        this->neighbours.push_back(idx);
    }

};

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
        E++;
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
                int v = i->source;

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


int main()
{
    test1();
    //test2();
    test3();
    test4();
    return 0;
}
