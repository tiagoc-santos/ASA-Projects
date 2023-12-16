#include <cstdio>
#include <vector>
#include <iostream>
#include <stack>

#define WHITE 0
#define BLACK -1
#define GREY 1
using namespace std;

int I,R,first;
vector<vector<int> > adj;
vector<vector<int> > rev_adj;
vector<int> colors;
vector<int> times;
stack<int> stack_DFS;

void buildGraph() {
  int oi = scanf("%d %d", &I, &R);
  if(oi){}
  adj = vector<vector<int> >(I + 1, vector<int>());
  rev_adj = vector<vector<int> > (I + 1, vector<int>());
  times = vector<int> (I + 1, 0);
  colors.resize(I+1);
  for (int i = 0; i < R; i++) { 
    int u, v;
    int lol = scanf("%d %d", &u, &v);
    if(lol && !first){
      first = u;
    }
    adj[u].push_back(v);
    rev_adj[v].push_back(u);
    colors[u] = WHITE;
    colors[v] = WHITE;
  }
}

int DFSVisit(vector<vector<int>>& graph, int time){
  bool visited = false;
  int v = stack_DFS.top();
  if(colors[v] == BLACK){
    stack_DFS.pop();
  }
  time++;
  for(int i = 0; i < (int) graph[v].size(); i++){
    if(colors[graph[v][i]] == WHITE){
      stack_DFS.push(graph[v][i]);
      visited = true;
    }
  }
  if(!visited && colors[v] == GREY){
    colors[v] = BLACK;
    stack_DFS.pop();
    times[v] = time;
    return time;
  }
  colors[v] = GREY;
  return time;
}


void DFS(vector<vector<int>>& graph, int source){ 
  int time = 0, i = 0;
  stack_DFS.push(source);
  while(!stack_DFS.empty()){
    time = DFSVisit(graph, time);
    i++;
  }
}

int main(){
    buildGraph();
    DFS(adj, first);
    for(int i = 1; i <= I; i++){
      printf("%d: %d\n", i, times[i]);
    }

    colors.assign(I + 1, WHITE);
    times.assign(I + 1, -1);
    stack_DFS = stack<int>();
    DFS(rev_adj, first);

    for (int i = I; i > 0; i--) {
      DFS(rev_adj, i);
      printf("%d: %d\n", i, times[i]);
    }
    return 0;
}