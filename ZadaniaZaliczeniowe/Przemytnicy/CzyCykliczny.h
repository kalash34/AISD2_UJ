#include<bits/stdc++.h>

using namespace std;

enum Color {WHITE, GRAY, BLACK};

class Graph
{
    public:
	int V;
	int E;
	list<pair<int,int>> *adjList;
    int *in;

	Graph(int V);
	Graph(list< pair<int, int> > adj[], int n);
	void addEdge(int v, int w, int wt);
	int getNumberOfVertices();
	int getNumberOfEdges();
    vector<int> getNeighbourIndices(int idx);

	void printGraph();

	bool DFSUtil(int v, int color[]);                                               // Sprawdzamy Cyklicznosc DFS'em
	bool isCyclic();
    bool isEulerian();
    bool isSC();                                                                    // Sprawdzamy Silna Spojnosc - do sprawdzenia, czy graf jest Eulerowski

    void SCC();                                                                     // Strongly Connected Components przez DFS'a
    void SCCUtil(int u, int discovered[], int low[], stack<int> *st, bool stackMember[]);

    void printAllPathsUtil(int, int, int[], int[], int&);
    void printAllPaths(int s, int d);

    Graph getTranspose();
};



Graph::Graph(int v){
    this->V=v;
    adjList=new list<pair<int,int>>[V];
    E=0;
    in = new int[V];
    for (int i = 0; i < V; i++){
       in[i] = 0;
    }
}

Graph::Graph(list<pair<int, int>> adj[], int n){
    this->adjList=adj;
    this->V=n;
    this->adjList=adj;

    in = new int[V];

    int edges_counter=0;
    for(int i=0;i<V;i++){
        for(auto it=adjList[i].begin();it != adjList[i].end();it++){
            (in[i])++;
            edges_counter++;
        }
    }
    E=edges_counter;

}
void Graph::addEdge(int v, int w, int c)
{
	adjList[v].push_back(make_pair(w, c));
    (in[w])++;
    E++;
}

int Graph::getNumberOfVertices(){
    return V;
}

int Graph::getNumberOfEdges(){
    return E;
}

vector<int> Graph::getNeighbourIndices(int idx){
    vector<int> indeksy_sasiadow;

    for(auto it = adjList[idx].begin(); it != adjList[idx].end();it++) {
        indeksy_sasiadow.push_back(it->first);
    }

    return indeksy_sasiadow;	//zwracamy wektor z sasiadami
}

void Graph::printGraph(){
    int n=getNumberOfVertices();
    int m=getNumberOfEdges();

    cout<<" G = (V, E) :  |V| = "<<n<<" |E| = "<<m<<endl<<endl;

    cout<<"V = { ";
    for(int v=0;v<n;v++){
        cout<<" v_nr= "<<v<<", "<<endl;
    }
    cout<<" }"<<endl;

    cout<<"E = { ";

    for(int i=0;i<m;i++){
        for(auto it=adjList[i].begin();it!=adjList[i].end();it++){
            cout<<"("<<i<<", "<<it->first<<", "<<it->second<<"), ";
        }
    }

    cout<<" } "<<endl;

}

// Modyfikujemy rekurencyjnego DFS'a
bool Graph::DFSUtil(int u, int color[])
{
    // GRAY: Wierzcholek jest przetwarzany (rozpoczeto DFS
    // dla tego wierzcholka, ale nie zakonczono, czyli ten wierzcholek
    // znajduje sie w aktualnym stosie wywolan funkcji).

    color[u] = GRAY;

    for(auto it = adjList[u].begin(); it != adjList[u].end();it++){
        int v = it->first;

        if(color[v] == GRAY){
            return true;
        }
        // Jesli v nie jest przetworzony i istnieje
        // krawedz tylna w poddrzewie o korzeniu v
        if(color[v] == WHITE && DFSUtil(v, color)){
            return true;
        }


    }
    // Oznaczamy odwiedzenie
    color[u] = BLACK;

    return false;
}

// Zwraca prawde jezeli graf zawiera Cykl, wpp. falsz
// Zmodyfikowany Zwykly DFS
bool Graph::isCyclic()
{
	// Oznacz wszystkie wierzcholki jako nieodwiedzone
	// i nie bedace czescia stosu rekurencji
    int *color = new int[V];
    for(int i = 0; i < V; i++){
        color[i] = WHITE;
    }

    // Uruchamiamy DFS'a z kazdego wierzcholka
    for(int i=0;i < V;i++){
        if(color[i] == WHITE){
            if(DFSUtil(i, color) == true){
                return true;
            }
        }
    }
    return false;

}


// Rekurencyjny DFS ktory znajduje i wypisuje Silnie Spojne Skladowe
// u                        - wierzcholek ktory ma byc odwiedzony nastepnie
// discovered[]             - punty odwiedzenia wierzcholkow
// low[]                    - wierzcholek ktory moze byc najszybciej odwiedzony z poddrzewa o korzeniu z aktualnym wierzcholkeim
// *st                      - Wszyscy spojni przodkowie (moga byc czescia SSC)
// stackMember[]            - tablica indeksow do szybkiego sprawdzania czy wierzcholek jest na stosie
void Graph::SCCUtil(int u, int discovered[], int low[], stack<int> *st, bool stackMember[])
{
    static int time = 0;

    discovered[u] = low[u] = ++time;
    st->push(u);
    stackMember[u] = true;


    for (auto it = adjList[u].begin(); it != adjList[u].end(); ++it)
    {
        int v = it->first;
        if (discovered[v] == -1)
        {
            SCCUtil(v, discovered, low, st, stackMember);
            // Sprawdz czy poddrzewo o korzeniu 'v' posiada
            // polaczenie z jednym z przodkow 'u'
            // Przypadek 1
            low[u] = min(low[u], low[v]);
        }
        // Aktualizuj wartosc low 'u' tylko dla 'v' bedacego na stosie
        // (przykladowo jesli to krawedz tylna)

        else if (stackMember[v] == true){
            low[u] = min(low[u], discovered[v]);
        }
    }
    // wierzcholek startowy znaleziony
    // zdejmij ze stosu i wypisz SSC
    int w = 0;                                  // do przechowania wierzcholkow ze stosu
    if (low[u] == discovered[u])
    {
        while (st->top() != u)
        {
            w = (int) st->top();
            cout << w << " ";
            stackMember[w] = false;
            st->pop();
        }
        w = (int) st->top();
        cout << w << "\n";
        stackMember[w] = false;
        st->pop();
    }
}

void Graph::SCC()
{
    int *discovered = new int[V];
    int *low = new int[V];
    bool *stackMember = new bool[V];
    stack<int> *st = new stack<int>();

    // Inicjalizujemy tablice odwiedzonych oraz o najkrotszym czasie do odwiedzenia a takze, stackMember
    for (int i = 0; i < V; i++)
    {
        discovered[i] = -1;
        low[i] = -1;
        stackMember[i] = false;
    }
    // Wywolujemy jak DFS'a funkcje SSC dla kazdego wierzcholka w grafie
    for (int i = 0; i < V; i++){
        if (discovered[i] == -1){
            SCCUtil(i, discovered, low, st, stackMember);
        }
    }
}

/*
Transpozycja Grafu Skierowanego to Graf Skierowany,
ktory zawiera ten sam zbior wierzcholkow ze wszystkimi krawedziami,
odwroconymi zwrotem, w porownaniu do zwrotu grafu ktory bedziemy transponowac.

Przykladowo Graf G bedzie zawieral krawedz Edge(u, v), to nasz graf bedacy jego
Transpozycja: Gt, bedzie zawieral krawedz Edge(v, u).

Potrzebujemy Tej Funkcji Do sprawdzania czy graf jest Strongly Connected.
*/
Graph Graph::getTranspose()
{
    Graph g(V);
    for (int v = 0; v < V; v++)
    {
        // Rekurencja po sasiadach

        for(auto it = adjList[v].begin(); it != adjList[v].end(); ++it)
        {
            int u = it->first;
            int wt = it->second;
            g.addEdge(u, v, wt);
            (g.in[v])++;
        }
    }
    return g;
}
// zwraca prawde jesli wszystkie niezerowe stopnie wierzcholkow
// grafu sa Silnie Spojne (Strongly Connected)

bool Graph::isSC()
{

    int *color = new int[V];
    for(int i = 0; i < V; i++){
        color[i] = WHITE;
    }
    // Szukamy Wierzcholka z niezerowym stopniem
    // Chociaz Dla naszych danych nie powinno byc takiego wierzcholka
    int n;
    for (n = 0; n < V; n++){
        if (adjList[n].size() > 0){
          break;
        }
    }

    // Przejscie DFS startujace z wierzcholkow o niezerowych stopniach
    DFSUtil(n, color);
    // Jesli Przejscie DFS nie odwiedzi wszystkich wierzcholkow zwroc falsz.
    // (Brak Sciezki i spojnosci)

    for (int i = 0; i < V; i++){
        if(color[i]==WHITE && adjList[i].size() > 0){
              return false;
        }
    }

    // Odwrocony Graf
    Graph odwrocony = getTranspose();

    // Wszystkie Wierzcholki Jako Nieodwiedzone
    for (int i = 0; i < V; i++){
        color[i] = WHITE;
    }
    // DFS dla grafu odwroconego od pierwszego wierzcholka.
    // Wierzcholek startowy musi byc taki sam dla pierwszego DFS.

    odwrocony.DFSUtil(n, color);

    // Jesli drugi DFS nie odwiedzi wszystkich wierzcholkow,
    // zwroc falsz
    for (int i = 0; i < V; i++){
        if (adjList[i].size() > 0 && color[i] == WHITE){
             return false;
        }
    }
    return true;
}

bool Graph::isEulerian()
{
    // Sprawdz czy wierzcholki o niezerowych stopniach sa Strongly Connected
    if (isSC() == false){
        return false;
    }

    // Sprawdz czy in_degree(i) == out_degree(i) dla kazdego i nalezacego do V
    for (int i = 0; i < V; i++){
        if (adjList[i].size() != in[i]){
            return false;
        }
    }
    return true;
}

//
void Graph::printAllPaths(int s, int d)
{

    int* color = new int[V];
    int* path = new int[V];
    int path_index = 0;

    // Wszystkie wierzcholki jako nieodwiedzone
    for (int i = 0; i < V; i++){
        color[i] = WHITE;
    }

    printAllPathsUtil(s, d, color, path, path_index);
}

// funkcja bazujaca na DFS wypisujaca wszystkie sciezki od 'u' do 'd'
// color[] oznacza wierzcholki w sciezce.
// path[] przechowuje aktualne wierzcholki w sciezce a tablica path_index to tablica aktualnych indeksow w path[]
void Graph::printAllPathsUtil(int u, int d, int color[], int path[], int& path_index)
{
    color[u] = GRAY;
    path[path_index] = u;
    path_index++;

    // jesli aktualny wierzcholek == cel, wypisz current_path[]
    if (u == d) {
        for (int i = 0; i < path_index; i++){
            cout << path[i] << " ";
        }
        cout << endl;
    }
    else // Jesli aktualny wierzcholek nie jest celem
    {
        for (auto it = adjList[u].begin(); it != adjList[u].end(); ++it){
            int v = it->first;
            if (color[v]==WHITE){
                printAllPathsUtil(v, d, color, path, path_index);
            }
        }
    }

    // Usuwamy Aktualny wierzcholek ze sciezki path[] i oznaczamy jako nieodwiedzony
    path_index--;
    color[u] = BLACK;
}

