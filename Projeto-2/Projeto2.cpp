#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

typedef struct Vertice{
    string color = "white";
    Vertice* predecessor;
    int num = -1, discover = -1, final = -1;
} Vertice;


class Graph {
    public:
        vector<vector<int>>adjMatrix;
        vector<Vertice>vertices;
        int _numVertices;
        Graph(int numVertices){
            adjMatrix = vector<vector<int>>(numVertices + 1, vector<int>(numVertices + 1, 0));
            vertices = vector<Vertice>(numVertices + 1);
            _numVertices = numVertices;
        }
        void addEdge(int u, int v){
            adjMatrix[u][v] = 1;
            if(vertices[u].num == -1){
                vertices[u].num = u;
            }
            if(vertices[v].num == -1){
                vertices[v].num = v;
            }
        }      
};

int DFS_Visit(Graph &G, int u, int time) {
    G.vertices[u].color = "gray";
    G.vertices[u].discover = ++time;
    for (int v = 1; v <= G._numVertices; ++v) {
        if (G.adjMatrix[u][v] == 1 && G.vertices[v].color == "white") {
            G.vertices[v].predecessor = &G.vertices[u];
            time = DFS_Visit(G, v, time);
        }
    }
    G.vertices[u].color = "black";
    G.vertices[u].final = ++time;
    return time;
}

void DFS(Graph &G) {
    int time = 0;
    for (int u = 1; u <= G._numVertices; ++u) {
        if (G.vertices[u].color == "white" && G.vertices[u].num != -1) {
            time = DFS_Visit(G, u, time);
        }
    }
}

void invertGraph(Graph &g){
    for(int i = 1; i <= g._numVertices; i++){
        for(int j = 1; j <= g._numVertices; j++){
            
        }
    }
}

int main(){
    int numRelations = 0, numIndiv = 0, lol = 0, u = 0, v = 0;
    lol = scanf("%d %d", &numIndiv, &numRelations);
    if(!lol)
        return 0;
    
    Graph graph = Graph(numIndiv);
    
    for(int i = 0; i < numRelations; i++){
        lol = scanf("%d %d", &u, &v);
        graph.addEdge(u,v);
    }
    DFS(graph);
    invertGraph(graph);
    return 0;
}