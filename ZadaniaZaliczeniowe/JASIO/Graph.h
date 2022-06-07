#include <iostream>
#include <list>
#include <stack>

using namespace std;

enum Color {WHITE, GRAY, BLACK};

class Graph {
  int V;
  list<int> *adj;
  void fillOrder(int s, int color[], stack<int> &Stack);
  void DFS(int s, int color[]);

  public:
      void changeGraph(int w);
      int SCCcount;
      int getSCCnumber();
      Graph(int V);
      void addEdge(int s, int d);
      void printSCC();
      Graph transpose();
};

Graph::Graph(int V) {
  this->V = V;
  SCCcount=0;
  adj = new list<int>[V];
}

void Graph::DFS(int s, int color[]) {
  color[s] = GRAY;
  cout << s << " ";

  list<int>::iterator i;
  for (i = adj[s].begin(); i != adj[s].end(); ++i){
    if (color[*i ]== WHITE){
      DFS(*i, color);
    }
  }
}

Graph Graph::transpose() {
  Graph g(V);
  for (int s = 0; s < V; s++) {
    list<int>::iterator i;
    for (i = adj[s].begin(); i != adj[s].end(); ++i) {
      //g.adj[*i].push_back(s);
      g.addEdge(*i, s);
    }
  }
  return g;
}

void Graph::addEdge(int s, int d) {
  adj[s].push_back(d);
  adj[d].push_back(s);
}


void Graph::changeGraph(int w){
    this->V = w;
    SCCcount=0;
    adj = new list<int>[V];
}

void Graph::fillOrder(int s, int color[], stack<int> &Stack) {
  color[s] = GRAY;

  list<int>::iterator i;
  for (i = adj[s].begin(); i != adj[s].end(); ++i)
    if (color[*i] == WHITE)
      fillOrder(*i, color, Stack);

  color[s] = BLACK;
  Stack.push(s);
}

void Graph::printSCC() {
  stack<int> Stack;

  int *color = new int[V];
  for (int i = 0; i < V; i++){
    color[i] = WHITE;
  }

  for (int i = 0; i < V; i++){
    if (color[i] == WHITE){
      fillOrder(i, color, Stack);
    }
  }
  Graph gr = transpose();

  for (int i = 0; i < V; i++){
    color[i] = WHITE;
  }

  while (Stack.empty() == false) {
    int s = Stack.top();
    Stack.pop();

    if (color[s] == WHITE) {
      gr.DFS(s, color);
      SCCcount++;
      cout << endl;
    }
  }
}

int Graph::getSCCnumber(){
    return SCCcount;
}

