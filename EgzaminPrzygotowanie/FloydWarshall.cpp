
#include<iostream>
#include<iomanip>

#define INF 9999
using namespace std;


void floydWarshal(int matrix[V][V], int V) {
   int cost[V][V];    //defind to store shortest distance from any node to any node
   for(int i = 0; i<V; i++)
      for(int j = 0; j<V; j++)
         cost[i][j] = matrix[i][j];     //copy costMatrix to new matrix

   for(int k = 0; k<V; k++) {
      for(int i = 0; i<V; i++)
         for(int j = 0; j<V; j++)
            if(cost[i][k]+cost[k][j] < cost[i][j])
               cost[i][j] = cost[i][k]+cost[k][j];
   }

   cout << "Macierz Wyjsciowa:" << endl;
   for(int i = 0; i<V; i++) {
      for(int j = 0; j<V; j++)
         cout << " " << cost[i][j];
      cout << endl;
   }
}

int main() {

    int V =7;
    //Cost matrix of the graph
    int costMat[V][V] = {
       {0, 3, 6, INF, INF, INF, INF},
       {3, 0, 2, 1, INF, INF, INF},
       {6, 2, 0, 1, 4, 2, INF},
       {INF, 1, 1, 0, 2, INF, 4},
       {INF, INF, 4, 2, 0, 2, 1},
       {INF, INF, 2, INF, 2, 0, 1},
       {INF, INF, INF, 4, 1, 1, 0}
    };


   floydWarshal(costMat, 7);
}
