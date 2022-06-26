#include <bits/stdc++.h>
#include <iostream>
#include <list>
#include <queue>
#include <fstream>
#include <string>

using namespace std;

#define INF 9999
enum Color {WHITE, GRAY, BLACK};

class Graph{
    int V;
    int E;
    list<pair<int,int>> *adjList;
public:
    Graph(int v){
        V=v;
        adjList=new list<pair<int,int>>[V];
        E=0;
    }
    void addEdge(int u,int v,int wt,bool bidir=true){
        adjList[u].push_back(make_pair(v,wt));
        if(bidir){
            adjList[v].push_back(make_pair(u,wt));
        }
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
            adjList = new list<pair<int,int>>[V];

        }
        file >> a >> b >> c;
        addEdge(a, b, c, false);
        i++;

    }
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
                cout<<"("<<i<<", "<<it->first<<"), "<<endl;
            }
        }


        cout<<" } "<<endl;


    }


    int getNumberOfVertices(){
        return V;
    }

    void topologicalSort(){
        cout<<"Sortowanie Topologiczne: "<<endl;
        int *indegree=new int[V]{0};
        //
        for(int i=0;i<V;i++){
            for(auto it=adjList[i].begin();it!=adjList[i].end();it++){
                indegree[it->first]++;
            }
        }
        queue<int >q;
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
                indegree[it->first]--;
                if(indegree[it->first]==0){
                    q.push(it->first);
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
                int v = i->first;

                if (color[v] == GRAY)
                  return true;

                if (color[v] == WHITE && DFSUtil(v, color))
                  return true;
            }

            color[u] = BLACK;
            return false;
        }

        bool isCyclic()
        {
            int *color = new int[V];
            for (int i = 0; i < V; i++)
                color[i] = WHITE;

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


        void dijkstra(int start, int docelowy){
                int vertices_count = getNumberOfVertices();
                int dist[vertices_count], prev[vertices_count];

               prev[start]=-1;
               for(int u = 0; u<vertices_count; u++) {
                  dist[u] = INF;
               }

               dist[start] = 0;    // tablica dlugosci sciezek
               set<int> S;         // zbior na dane
               list<int> Q;

               for(int u = 0; u<vertices_count; u++) {
                  Q.push_back(u);                                       //dodajemy wszystkie wierzcholki do kolejki
               }

               while(!Q.empty()) {
                  list<int> :: iterator i;
                  i = min_element(Q.begin(), Q.end());
                  int u = *i;                                           //element minimalny z kolejki
                  Q.remove(u);
                  S.insert(u);                                          //dodaj u do zbioru
                  list<pair<int, int>> :: iterator it;

                  for(it = adjList[u].begin(); it != adjList[u].end();it++) {
                     if((dist[u]+(it->second)) < dist[it->first]) {                    //porownujemy dystans (u,v)
                        dist[it->first] = (dist[u]+(it->second));
                        prev[it->first] = u;
                     }
                  }
                }


           for(int i = 0; i<vertices_count; i++){
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
            int nV = getNumberOfVertices();
            for (int i = 0; i < nV; i++) {
                for (int j = 0; j < nV; j++) {
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

        void FloydWarshall(){

        int VertexNumber = getNumberOfVertices();
        vector<vector<int> > matrix(VertexNumber, vector<int>(VertexNumber, INF));
        list<pair<int, int>> :: iterator it;

        for (int i = 0; i < VertexNumber; i++) {

            for (it = adjList[i].begin(); it != adjList[i].end();it++){

                matrix[i][it->first] = it->second;
                if(i==it->first){
                    matrix[i][it->first] = 0;

                }
            }

        }

        for (int i = 0; i < VertexNumber; i++) {
        for (int j = 0; j < VertexNumber; j++) {

            if (i == j){
                matrix[i][j] = 0;

            }
        }
        }
        cout<<"Macierz Wejsciowa Floyda Warshalla : "<<endl;
        printMatrix(matrix);

        for(int k=0;k< VertexNumber;k++){
            for(int i=0;i< VertexNumber; i++){
                for(int j=0;j<VertexNumber;j++){
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
    g.dijkstra(8,5);
    //g.displayEdges();
}
void test3(){
    Graph g(100);

    g.readFromFile("Graf2.txt");
    g.topologicalSort();

    //g.readFromFile("Graf3.txt");
    //g.topologicalSort();

}


void test5(){
    Graph g(100);

    g.readFromFile("GrafMST_JawneKrawedzie4.txt");
    g.printGraph();
    //g.FloydWarshall();

    //g.readFromFile("Graf3.txt");
    //g.topologicalSort();



}

void test4(){
    Graph g(100);

    g.readFromFile("GrafTest23.txt");
    g.FloydWarshall();

    //g.readFromFile("Graf3.txt");
    //g.topologicalSort();



}



int main()
{
    //test1();
    //test2();
    //test3();
    //test4();
    test5();
    return 0;
}
