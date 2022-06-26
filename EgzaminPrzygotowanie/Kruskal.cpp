#include <bits/stdc++.h>
#include <fstream>
#include <string>

using namespace std;


// Struktura Danych Disjoint Set Union
// kompresja sciezek oraz rank by uinion


class DSU {
    int* parent;
    int* rank;
public:
    DSU(int n)
    {
        parent = new int[n];
        rank = new int[n];

        for (int i = 0; i < n; i++) {
            parent[i] = -1;
            rank[i] = 1;
        }
    }
	// Funkcja znajdujaca po indeksie
    int find(int i)
    {
        if (parent[i] == -1)
            return i;

        return parent[i] = find(parent[i]);
    }
    //
	// funkcja union
    void unite(int x, int y)
    {
        int s1 = find(x);
        int s2 = find(y);

        if (s1 != s2) {
            if (rank[s1] < rank[s2]) {
                parent[s1] = s2;
                rank[s2] += rank[s1];
            }
            else {
                parent[s2] = s1;
                rank[s1] += rank[s2];
            }
        }
    }
};

class Graph {
    vector<vector<int> > edgelist;
    int V;

public:
    Graph(int V) { this->V = V; }

    void addEdge(int x, int y, int w)
    {
        edgelist.push_back({ w, x, y });
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


            }
            file >> a >> b >> c;
            addEdge(a, b, c);
            i++;
        }

    }

    void kruskals_mst()
    {
        // 1. Sortuj wszystkie krawedzie
        sort(edgelist.begin(), edgelist.end());

        //
		// Inicjalizuj DSU
        DSU s(V);
        int ans = 0;
        cout << "Nastepujace krawdzie tworza MST tego Grafu "<< endl;
        for (auto edge : edgelist) {
            int w = edge[0];
            int x = edge[1];
            int y = edge[2];

            //
			// Wez te krawedz do MST jezeli formuje cykl
            if (s.find(x) != s.find(y)) {
                s.unite(x, y);
                ans += w;
                cout << x << " -- " << y << ", waga == " << w
                     << endl;
            }
        }
        cout << "Minimum Cost Spanning Tree: " << ans;
    }
};



void test1(){
	Graph g(18);
	g.readFromFile("GrafMST_JawneKrawedzie3.txt");

    g.kruskals_mst();

}


int main()
{

    // int n, m;
    // cin >> n >> m;

    // Graph g(n);
    // for (int i = 0; i < m; i++)
    // {
    //     int x, y, w;
    //     cin >> x >> y >> w;
    //     g.addEdge(x, y, w);
    // }
    test1();
    return 0;
}
