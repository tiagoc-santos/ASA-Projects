#include <cstdio>
#include <iostream>
#include <stack>
#include <vector>

#define WHITE 0
#define BLACK -1
#define GREY 1
using namespace std;

int I, R, first, last, DFStime, anterior = -1, maximo = 0;
vector<vector<int>> adj;
vector<vector<int>> rev_adj;
vector<int> colors;
vector<int> times;
vector<int> reach;
vector<int> nao_calcula;
vector<int> marked;
stack<int> stack_DFS;
stack<int> stack_inversa;

void buildGraph() {
  int oi = scanf("%d %d", &I, &R);
  if (oi) {
  }
  adj = vector<vector<int>>(I + 1, vector<int>());
  rev_adj = vector<vector<int>>(I + 1, vector<int>());
  times = vector<int>(I + 1, -1);
  colors.resize(I + 1);
  reach = vector<int>(I + 1, -1);
  nao_calcula = vector<int>(I + 1, -1);
  marked = vector<int>(I + 1, -1);
  for (int i = 0; i < R; i++) {
    int u, v;
    int lol = scanf("%d %d", &u, &v);
    if (lol && !first) {
      first = u;
    }
    if (u != v){
      adj[u].push_back(v);
      rev_adj[v].push_back(u);
    }
  }
}

void DFSVisit(vector<vector<int>> &graph, stack<int> &stack, int source) {
  stack.push(source);
  while (!stack.empty()) {
    bool visited = false;
    int v = stack.top();
    if (colors[v] == BLACK) {
      stack.pop();
      continue;
    }
    DFStime++;
    for (int i = 0; i < (int)graph[v].size(); i++) {
      if (colors[graph[v][i]] == WHITE) {
        stack.push(graph[v][i]);
        visited = true;
      }
    }
    if (!visited && colors[v] == GREY) {
      colors[v] = BLACK;
      stack.pop();
      times[v] = DFStime;
      stack_inversa.push(v);
      continue;
    }
    colors[v] = GREY;
  }
}

void DFSVisitReverse(vector<vector<int>> &graph, stack<int> &stack,
                     int source) {
  stack.push(source);
  while (!stack.empty()) {
    bool visited = false, vizinhos = false;
    int v = stack.top();
    if (colors[v] == BLACK) {
      stack.pop();
      continue;
    }
    for (int i = 0; i < (int)rev_adj[v].size(); i++) {
      vizinhos = true;
      if (colors[rev_adj[v][i]] == WHITE) {
        stack.push(rev_adj[v][i]);
        visited = true;
        if (nao_calcula[v] == 1) {
          marked[rev_adj[v][i]] = 1;
          continue;
        } 
        else if (v != rev_adj[v][i]) {
          nao_calcula[rev_adj[v][i]] = 1;
          nao_calcula[v] = 1;
          continue;
        }
      }
      if (nao_calcula[rev_adj[v][i]] == 1 && marked[v] == 1 && nao_calcula[v] == -1){
        nao_calcula[v] = 1;
      }
      if (reach[rev_adj[v][i]] != -1 && (nao_calcula[v] == -1 || (nao_calcula[v] == 1 && nao_calcula[rev_adj[v][i]] == -1 && colors[rev_adj[v][i]] != WHITE)) && v != rev_adj[v][i]) {
        reach[v] = max(reach[rev_adj[v][i]] + 1, reach[v]);
      }
      else if (nao_calcula[v] == 1){
        reach[v] = max(reach[rev_adj[v][i]], reach[v]);
      }
    }
    if (!vizinhos || ((int)rev_adj[v].size() == 1 && v == rev_adj[v][0])) {
      reach[v] = 0;
    }
    maximo = max(maximo, reach[v]);
    if (!visited && colors[v] == GREY) {
      colors[v] = BLACK;
      stack.pop();
      continue;
    }
    colors[v] = GREY;
  }
}

void DFS(vector<vector<int>> &graph, stack<int> stack, int source) {
  for (int i = 0; i < (int)colors.size(); i++) {
    colors[i] = WHITE;
  }
  for (int i = 1; i <= I; i++) {
    if (colors[i] == WHITE)
      DFSVisit(graph, stack, i);
  }
}

void DFSReverse(vector<vector<int>> &graph, stack<int> stack, int source) {
  for (int i = 0; i < (int)colors.size(); i++) {
    colors[i] = WHITE;
  }
  while (!stack_inversa.empty()) {
    int v = stack_inversa.top();
    if (colors[v] == WHITE) {
      DFSVisitReverse(rev_adj, stack, v);
    }
    stack_inversa.pop();
  }
}

int main() {
  buildGraph();
  DFS(adj, stack_DFS, first);
  last = stack_inversa.top();
  DFStime = 0;
  stack<int> stack2;
  DFSReverse(rev_adj, stack2, last);
  printf("%d\n", maximo);
  return 0;
}
