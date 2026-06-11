#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 10
#define MAX_EDGES 50

typedef struct {
    int u, v, weight;
} Edge;

int parent[MAX_NODES], rank_[MAX_NODES];
int nodeCount;
char nodeNames[MAX_NODES];

int find(int x) {
    if (parent[x] != x) parent[x] = find(parent[x]);
    return parent[x];
}

void unite(int x, int y) {
    int px = find(x), py = find(y);
    if (rank_[px] < rank_[py]) { int t = px; px = py; py = t; }
    parent[py] = px;
    if (rank_[px] == rank_[py]) rank_[px]++;
}

int compareEdges(const void* a, const void* b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

int main() {
    printf("=== QUESTION 3: Fiber-Optic Network - Kruskal's MST ===\n\n");

    // Network graph (7 hubs: A=0, B=1, C=2, D=3, E=4, F=5, G=6)
    // Based on typical fiber network assignment topology
    char names[] = {'A','B','C','D','E','F','G'};
    nodeCount = 7;
    for (int i = 0; i < nodeCount; i++) nodeNames[i] = names[i];

    Edge edges[] = {
        {0,1,4}, {0,2,8},
        {1,2,11},{1,3,8},
        {2,4,7}, {2,5,1},
        {3,4,2}, {3,6,9},
        {4,5,6}, {4,6,10},
        {5,6,2}
    };
    int edgeCount = 11;

    // Print adjacency matrix
    int adj[7][7] = {0};
    for (int i = 0; i < edgeCount; i++) {
        adj[edges[i].u][edges[i].v] = edges[i].weight;
        adj[edges[i].v][edges[i].u] = edges[i].weight;
    }

    printf("--- Adjacency Matrix (cost in millions $) ---\n");
    printf("   ");
    for (int i = 0; i < nodeCount; i++) printf("  %c", names[i]);
    printf("\n");
    for (int i = 0; i < nodeCount; i++) {
        printf(" %c ", names[i]);
        for (int j = 0; j < nodeCount; j++)
            printf(" %2d", adj[i][j]);
        printf("\n");
    }
    printf("\n");

    // All edges listed
    printf("--- All Edges (sorted by cost) ---\n");
    qsort(edges, edgeCount, sizeof(Edge), compareEdges);
    for (int i = 0; i < edgeCount; i++)
        printf("  %c-%c : %d million\n", names[edges[i].u], names[edges[i].v], edges[i].weight);
    printf("\n");

    // Kruskal's algorithm
    for (int i = 0; i < nodeCount; i++) { parent[i] = i; rank_[i] = 0; }

    printf("--- Applying Kruskal's Algorithm ---\n");
    printf("%-15s %-10s %-10s\n", "Edge", "Cost($M)", "Action");
    printf("%-15s %-10s %-10s\n", "----", "--------", "------");

    Edge mst[MAX_NODES];
    int mstSize = 0, totalCost = 0;

    for (int i = 0; i < edgeCount && mstSize < nodeCount - 1; i++) {
        int u = edges[i].u, v = edges[i].v, w = edges[i].weight;
        if (find(u) != find(v)) {
            unite(u, v);
            mst[mstSize++] = edges[i];
            totalCost += w;
            printf("%c-%c            %-10d ADDED to MST\n", names[u], names[v], w);
        } else {
            printf("%c-%c            %-10d SKIPPED (creates cycle)\n", names[u], names[v], w);
        }
    }

    printf("\n--- MST Result: Selected Fiber-Optic Links ---\n");
    for (int i = 0; i < mstSize; i++)
        printf("  Hub %c <---> Hub %c : %d million dollars\n",
               names[mst[i].u], names[mst[i].v], mst[i].weight);
    printf("\nTotal Minimum Installation Cost: $%d million\n", totalCost);

    return 0;
}
