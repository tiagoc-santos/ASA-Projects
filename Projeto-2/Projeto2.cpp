#include <cstdio>
#include <iostream>
#include <stack>
#include <vector>

#define WHITE 0
#define BLACK -1
#define GREY 1
using namespace std;

int I, R, first, last, DFStime, maximo = 0;
vector<vector<int>> adj;
vector<vector<int>> rev_adj;
vector<int> colors;
vector<int> times;
vector<int> reach;
vector<int> max_jump;
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
  max_jump = vector<int>(I + 1,  0);
  for (int i = 0; i < R; i++) {
    int u, v;
    int lol = scanf("%d %d", &u, &v);
    if (lol && !first) {
      first = u;
    }
    adj[u].push_back(v);
    rev_adj[v].push_back(u);
  }
}

void DFSVisit(vector<vector<int>> &graph, stack<int> &stack, int source) {
  stack.push(source);
  while (!stack.empty()) {
    int v = stack.top();
    DFStime++;
    if(colors[v] == WHITE){
      for (int i = 0; i < (int)graph[v].size(); i++) {
        stack.push(graph[v][i]);
      }
      colors[v] = GREY;
    }
    else if (colors[v] == GREY) {
      colors[v] = BLACK;
      stack.pop();
      times[v] = DFStime;
      stack_inversa.push(v);
    }
    else{
      stack.pop();
    }
  }
}

void DFSVisitReverse(vector<vector<int>> &graph,
                     int source) {
  stack<int> stack;
  stack.push(source);
  int max_jumps = 0;
  while (!stack.empty()) {
    int v = stack.top();
    if(colors[v] == WHITE){
      for (int i = 0; i < (int)rev_adj[v].size(); i++) {
        if (colors[rev_adj[v][i]] == WHITE) {
          stack.push(rev_adj[v][i]);
        }
        if(reach[rev_adj[v][i]] >= max_jumps){
          max_jumps = reach[rev_adj[v][i]] + 1;
        }
      }
      colors[v] = GREY;
    }
    else if (colors[v] == GREY) {
      colors[v] = BLACK;
      reach[v] = max_jumps;
      maximo = max(reach[v], maximo);
      stack.pop();
    }
    else{
      stack.pop();
    }
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
      DFSVisitReverse(rev_adj, v);
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