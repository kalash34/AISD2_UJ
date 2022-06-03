#include <bits/stdc++.h>

using namespace std;


class DSU{
    int* parent;
    int* rank;

    public:
        DSU(int n){
            parent - new int[n];
            rank = new int[n];

            for(int i = 0; i < n; i++){
                parent[i] = -1;
                rank[i] = 1;
            }
        }

        int find(int i){
            if (parent[i] == -1){
                return i;
            }
            return parent[i] = find(parent[i]);
        }
        void unite(int x, int y){

            int s1 = find(x);
            int s2 = find(y);

            if(s1 != s2){
                if(rank[s1] < rank[s2]){
                    parent[s1] = s2;
                    rank[s2] += rank[s1];
                }
                else{
                    parent[s2] = s1;
                    rank[s1] += rank[s2];
                }
            }
        }


};

class Graph {
    vector< pair<int, int> > adjList;
    int V;
public:
    Graph(int V){
        this->V = V;
    }
    void addEdge(int u, int v, int wt){

        adjList[u].push_back(make_pair(v, wt));
        printf("Dodano krawedz (%d, %d, %d).\n",u, v, wt);
    }

    void printAdjList(){
        vector< pair < int, int> > :: iterator it;

        for(int i=0;i<V;i++){
            for(it=adjList[i].begin();it!=adjList[i].end();it++){
                cout<<"("<<i<<")---("<<it->first<<"|"<<it->second<<") "<<endl;
            }
            cout<<endl;
        }



    }



    void Kruskal(){
        sort(adjList.begin(), adjList.end());
        cout<<"Posortowano Liste!: "<<endl;


        DSU s(V);
        int ans = 0;

        cout<<" Nastepujace Krawedzie Tworza MST: "<<endl;

        for(auto edge : adjList){
           int u = edge[0];
           int v = edge[1];
           int weight = edge[2];
         // Dodaj Krawedz do MST jesli nie tworzy cyklu z krawedziami budujacymi aktualne drzewo
           if(s.find(u) != s.find(v)){
               s.unite(u, v);
               ans += weight;
               cout << u << " -- " << v << " == " << weight << endl;
           }

        }
        cout << "Waga MST: " << ans;

    }

};


void testGraph(){

    int n, m;
    cin >> n >> m;

    Graph g(n);
    for(int i = 0; i < m; i++ ){

        int x, y, w;
        cin >> x >> y >> w;
        g.addEdge(x, y, w);
    }
    g.Kruskal();


}


int main(){


    Graph g(4);
    g.addEdge(0, 1, 10);
    g.addEdge(1, 3, 15);
    g.addEdge(2, 3, 4);
    g.addEdge(2, 0, 6);
    g.addEdge(0, 3, 5);

    g.Kruskal();



}

