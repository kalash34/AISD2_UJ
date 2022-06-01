#include <bits/stdc++.h>
#include "CzyCykliczny.h"

#define INF 9999

using namespace std;

vector<int> getNeighbours(vector< vector< int > > adj, int idx){
    int V = adj.size();
    vector<int> sasiedzi;           //Wektor sasiadow wierzcholka o nr idx

    for (int i=0; i<V; i++)
    {
        if(adj[idx][i]!=INF){
            sasiedzi.push_back(i);
        }
    }
    return sasiedzi;
}

void printMatrix(vector < vector<int> > matrix) {
        int V=matrix.size();
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

vector< vector<int> > ConvertToMatrix(list<pair<int, int>> lista_sasiedztwa[], int s){
    int V = s;
    vector< vector <int> > matrix(V, vector<int>(V, INF));
    list<pair<int, int>> :: iterator it;
    for(int i =0; i < V; i++){
        for(it = lista_sasiedztwa[i].begin(); it != lista_sasiedztwa[i].end(); it++){
        matrix[i][it->first - 1] = it->second;
        }
    }
    return matrix;
}


void HierHolzerPrintCircuit(vector< vector <int> > adjList, int n)
{
    int V=n;
    vector< vector<int> > adj;
    adj.resize(V);

    for(int i=0;i<V;i++){
        vector<int> sasiedzi= getNeighbours(adjList, i);
        for(int j=0;j<sasiedzi.size();j++){
            adj[i].push_back(sasiedzi[j]);
        }
    }

    for (int i = 0; i < V; i++) {
        cout<<i<<" : ";
        for (int j = 0; j < V; j++) {
          cout<<adj[i][j]<<" ";
        }
        printf("\n");
    }

    unordered_map<int, int> edge_count;  //licznik krawedzi wychodzacych z kazdego wierzcholka

    for (int i=0; i<adj.size(); i++)
    {
        edge_count[i] = adj[i].size();
    }

    stack<int> current_path;        // stos wierzcholkow
    vector<int> circuit;            // wektor wierzcholkow w cyklu

    current_path.push(0);           // start z pierwszego wierzcholka
    int current_vertex = 0;         // Aktualny Wierzcholek

    while (!current_path.empty())
    {
        // Jesli pozostala krawedz
        if (edge_count[current_vertex])
        {
            current_path.push(current_vertex);               // Wloz Wierzcholek na stos
            int next_vertex = adj[current_vertex].back();    // Znajdz nastepny wierzcholek uzywajac krawedzi
            edge_count[current_vertex]--;                    // usuwamy te krawedz
            adj[current_vertex].pop_back();
            current_vertex = next_vertex;                   // Idz do nastepnego wierzcholka
        }
        // nawrot zeby znalezc pozostale okrazenie
        else
        {
            circuit.push_back(current_vertex);
            current_vertex = current_path.top(); //Nawroty
            current_path.pop();
        }
    }
    int circuit_weight=0;                       // Mamy okrazenie, wypisujemy je od tylu
    for (int i=circuit.size()-1; i>=0; i--)
    {
        if(i>=1){
            int a = circuit[i];
            int b = circuit[i-1];
            if(adjList[a][b]!=INF){
            circuit_weight+=adjList[a][b];
            }
        }

        cout << circuit[i] ;
        if (i){
           cout<<" -> ";
        }
    }
    cout<<endl;

    cout<<"Waga Cyklu Przemian= "<<circuit_weight<<endl;

}

void printPath(int parent[], int j)
{

    if (parent[j] == -1){
        return;
    }
    printPath(parent, parent[j]);
    cout << j << " ";
}

int printSolution(int dist[], int n, int parent[])
{
    int src = 0;
    cout << "Wierzcholek\t Dystans\t Sciezka";
    for (int i = 0; i < n; i++) {
        printf("\n%d -> %d \t\t %d\t\t%d ", src, i, dist[i], src);
        printPath(parent, i);
    }
    cout<<endl;
}

void Dijkstra(list< pair<int, int>> adjList[], int n, int start, int koniec){

   int V = n;
   int dist[V];   //Nie znamy dlugosci tablic wynikowych
   int prev[V];   // ustawiamy jakies wartosci

   for(int u = 0; u<V; u++) {
      dist[u] = INF;
      prev[u] = -1;
   }

   dist[start] = 0;

   set<int> S;
   list<int> Q;
   for(int u = 0; u<V; u++){
        Q.push_back(u);
   }

   while(!Q.empty()) {
      list<int> :: iterator i;
      i = min_element(Q.begin(), Q.end());
      int u = *i;                           // Element Minimalny Z Kolejki
      Q.remove(u);
      S.insert(u);                          // dodaj u do zbioru
      list<pair< int, int>> :: iterator it;

      for(it = adjList[u].begin(); it != adjList[u].end();it++) {
         if((dist[u]+(it->second)) < dist[it->first]) {                        // relax krawedzi (u, v)
            dist[it->first] = (dist[u]+(it->second));
            prev[it->first] = u;

         }
      }
   }
    cout<<"Distance Array: "<<endl;

    for(int i=0;i<V;i++){
        printf("%d ",dist[i]);
    }
    cout<<endl;
    cout<<"Shortest Path Array: "<<endl;
    printSolution(dist, V, prev);

    cout<<"Najkrotsza sciezka, lista wierzcholkow: "<<endl<<endl;
    for(int i = 0;i<n;i++){
        int node = i;
        int pre = prev[i];
        cout<<i<<" : ";
        while(pre!=start){
            cout<<pre<<" ";
            node = pre;
            pre = prev[node];
        }
        cout<<start<<endl;
    }
    cout<<"Waga Najkrotszej Sciezki do mety = "<<dist[koniec]<<endl;


    cout<<"Waga Najkrotszego Cyklu= "<<dist[koniec]+dist[start]<<endl;

}


// Rekurencyjna Funkcja wypisujaca sciezke z wierzcholka 'v' do wierzcholka 'u';
//
void printFloydPath(vector<vector<int>> const &path, int v, int u)
{
    if (path[v][u] == v) {
        return;
    }
    printFloydPath(path, v, path[v][u]);
    cout << path[v][u] << ", ";
}

// Funkcja wypisujca najmniejsze koszty z informacjami o sciezce
// miedzy wszystkimi parami wierzcholkow

void printFloydSolution(vector<vector<int>> const &cost, vector<vector<int>> const &path)
{
    int n = cost.size();
    bool flaga=false;
    int cycle_cost=0;
    for (int v = 0; v < n; v++)
    {
        for (int u = 0; u < n; u++)
        {
            if (u != v && path[v][u] != -1)
            {
                cout << "Najkrotsza Sciezka z Miedzy Wierzcholkami : " << v << " = > " << u << " to ["
                    << v << ", ";
                printFloydPath(path, v, u);
                cout << u << "]" << endl;

                cycle_cost=cost[v][u]+cost[u][v];
                flaga=true;

            }
            if(flaga){
            cout<<"Koszt Cyklu Dla Pary <u,v>="<<cycle_cost<<endl;
            flaga=false;
            }
        }
    }
}


int FloydWarshallSolution(vector<vector<int>> const &cost, vector<vector<int>> const &path, int start){
    int n = cost.size();
    bool flaga=false;
    int cycle_cost=0;
    int minimalny_cykl=0;
    map<int, int> koszty_cykli; // slownik wartosci cykli wychodzacych z wierzcholkow < indeks, wielkosc_cyklu >

    for (int v = 0; v < n; v++)
    {
        for (int u = 0; u < n; u++)
        {
            if (u != v && path[v][u] != -1)         // Sprawdzamy Tylko Cykle Zaczynajace Sie Od Zera
            {
                if(path[v][u]>0){                   //usuwamy zerowe sciezki
                cycle_cost=cost[v][u]+cost[u][v];
                flaga=true;
                }
            }if(flaga){
            std::map<int, int>::iterator it = koszty_cykli.find(v);
            if (it != koszty_cykli.end()){
                if( cycle_cost < it-> second){
                it->second = cycle_cost;
                }
            }else{
                koszty_cykli.insert({ v, cycle_cost });
            }
            }
            flaga=false;
        }
    }

    std::map<int, int>::iterator it = koszty_cykli.find(start);
    if (it != koszty_cykli.end()){
        minimalny_cykl= it->second;
    }else{                                          // Kod Bledu
        minimalny_cykl= -1;
     }
     return minimalny_cykl;

}


void FloydWarshall(list<pair<int,int>> adjList[], int n)
{
    int V=n;
    vector<vector<int> > matrix(V, vector<int>(V, INF));


    for (int i = 0; i < V; i++) {
        for (auto it = adjList[i].begin(); it != adjList[i].end();it++){
            if(i==it->first){
                    matrix[i][i] = 0;
            }
            matrix[i][it->first] = it->second;
        }
    }

    if (V == 0) {
        return;
    }
    // cost[] oraz path[] (najmniejszy koszt / najkrotsza sciezka)
    vector<vector<int>> cost(n, vector<int>(n));
    vector<vector<int>> path(n, vector<int>(n));

    // inicjalizujemy cost[] oraz path[]
    for (int v = 0; v < V; v++)
    {
        for (int u = 0; u < V; u++)
        {
            cost[v][u] = matrix[v][u];

            if (v == u) {
                path[v][u] = 0;
            }
            else if (cost[v][u] != INF) {
                path[v][u] = v;
            }
            else {
                path[v][u] = -1;
            }
        }
    }

    for (int k = 0; k < n; k++)
    {
        for (int v = 0; v < n; v++)
        {
            for (int u = 0; u < n; u++)
            {
                // Jesli wierzcholek 'k' jest na najkrotszej sciezce z 'v' do 'u'
                // to aktualizuj wartosc cost[v][u] oraz path[v][u]
                if (cost[v][k] != INT_MAX && cost[k][u] != INF && cost[v][k] + cost[k][u] < cost[v][u])
                {
                    cost[v][u] = cost[v][k] + cost[k][u];
                    path[v][u] = path[k][u];
                }
            }
            // Jesli Przekatne staja sie ujemne,
            // graf zawiera ujemny cykl.
            if (cost[v][v] < 0)
            {
                cout << "Znaleziono Ujemny Cykl";
                return;
            }
        }
    }
    //printFloydSolution(cost, path);
   // cout<<endl;
    cout<<FloydWarshallSolution(cost, path, 0);
}


void FloydWarshall2(list< pair<int, int>> adjList[], int V){
    //konwertujemy liste sasiedztwa na macierz
    vector<vector<int> > matrix(V, vector<int>(V, INF));
    for (int i = 0; i < V; i++) {
        for (auto it = adjList[i].begin(); it != adjList[i].end();it++){
            if(i==it->first){
                matrix[i][i] = 0;
            }
            matrix[i][it->first] = it->second;
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
    int suma_cykl=matrix[0][3] + matrix[3][0];
    cout<<"Wartosc Cyklu="<<suma_cykl;

}



void TestFloydWarshallSolution(list<pair<int, int>> adjList[], int n){

    FloydWarshall(adjList, n);

}


void Solve(){

    int n, k, m, pk;
    vector<int> k_cena; // Tabela Cen Metali
    int a, b, c;        // Format Przemiany Oferowanej Przez Alchemikow

    k=0;
    m=0;
    pk=0;
    cin>>n;
    if((n < 1) || (n > 5000)){
        throw std::invalid_argument("Liczba n jest poza zakresem [1, 5000]");
    }

    for(int i=1;i<=n;i++){
        cin >>k ;
        if((k >= 0) && (k <= 1000000000 )){
            pk=k;                                   // cena pk-tego metalu
            k_cena.push_back(pk);                   // liczby pk dodajemy do wektora
        }else{
            throw std::invalid_argument("Cena pk-tego metalu jest poza zakresem [0, 10^9 ]");
        }
    }

    cin >> m;                                       // Liczba Procesow Przemiany, czyli liczba krawedzi w naszym Grafie
    if((m<0) || (m > 100000)){
        throw std::invalid_argument("Liczba m nie jest w zakresie [0, 100000]");
    }


    list<pair<int,int>> *adjList;
    adjList=new list<pair<int,int>>[m];

    for(int i=0;i<m;i++){
        cin >> a >> b >> c;
        if((a >= 1 && b >=1) && (a<=n && b<=n) && (c>= 0 && c<= 10000)){
        adjList[a-1].push_back(make_pair(b-1,c));
        }else{
        throw std::invalid_argument("Zle opisana Przemiana!");
        }
    }
    int gold_price=k_cena[0];

    vector<int> koszty_przemian;
    int koszt_przemiany=0;

    for(int i=0;i<n;i++){
        koszt_przemiany=0;
        for(auto it=adjList[i].begin();it!=adjList[i].end();it++){
            koszt_przemiany = it->second;
            koszty_przemian.push_back(koszt_przemiany);
        }

    }

    //cout<<"Koszty Wszystkich Wczytanych Przemian = "<<endl;
    //for(int val : koszty_przemian){
    //    cout<< val << ' ';
    //}

    //cout<<endl<<endl;
    // Clo to polowa ceny 1 kg metalu, czyli czytamy minimumu z tablicy cen metali
    int clo = *min_element(k_cena.begin(), k_cena.end());
    clo = clo/2 ;
    //cout<<"Obliczone Clo Dla Ladunku[bajto_dolarow] =  "<<clo<<endl<<endl;

    vector<int> koszty_przemian_metali;             // koszty calych krawedzi metali uwzgledniajac ceny metali z ktorych
                                                    // rozpoczynamy przemiane
    int przemiana=0;
    for(int i=0;i<n;i++){
        for(auto it=adjList[i].begin();it!=adjList[i].end();it++){

            przemiana = k_cena[i] - k_cena[it->first];    // przemiana metalu (danej krawedzi to roznica cen (a - b)
            przemiana = przemiana + it->second;           // do przemiany dodajemy clo
            koszty_przemian.push_back(przemiana);
        }

    }


    vector< vector <int> > matrix = ConvertToMatrix(adjList, n);
    // TestGraf(adjList, n);

    //cout<<"Rozwiazanie przez Dijkstra= "<<endl;
    //Dijkstra(adjList, n, 0, 3);

    TestFloydWarshallSolution(adjList, n);


}


void TestGraf(list<pair <int, int>> adjList[], int n){
    vector< vector <int> > matrix = ConvertToMatrix(adjList, n);
    HierHolzerPrintCircuit(matrix, n);

    Graph g(adjList, n);
    // Testy Danych Wejsciowych
    cout<<"Czy Graf jest Cykliczny : "<<g.isCyclic()<<endl;
    cout<<"Czy Graf jest Eulerowski: "<<g.isEulerian()<<endl;
    cout<<"Silnie Spojne Skladowe Grafu Wejsciowego: "<<endl;
    g.SCC();
    g.printAllPaths(3,2);     // wypiszmy sobie probne sciezki


    //cout<<"Rozwiazanie przez Dijkstra= "<<endl;
    //Dijkstra(adjList, n, 0, 3);
    TestFloydWarshallSolution(adjList, n);


}

int main(){

Solve();

}
