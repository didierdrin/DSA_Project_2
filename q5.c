#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_NODES 10
#define MAX_EDGES 50
#define INF INT_MAX

typedef struct {
    int u, v, weight;
} Edge;

int nodeCount = 8;
char* branchNames[] = {"A","B","C","D","E","F","G","H"};
Edge edges[MAX_EDGES];
int edgeCount = 0;

void addEdge(int u, int v, int w) {
    edges[edgeCount].u = u;
    edges[edgeCount].v = v;
    edges[edgeCount].weight = w;
    edgeCount++;
}

void bellmanFord(int src) {
    int dist[MAX_NODES], prev[MAX_NODES];
    for (int i = 0; i < nodeCount; i++) { dist[i] = INF; prev[i] = -1; }
    dist[src] = 0;

    // Relax edges (nodeCount - 1) times
    for (int iter = 0; iter < nodeCount - 1; iter++) {
        int updated = 0;
        for (int i = 0; i < edgeCount; i++) {
            int u = edges[i].u, v = edges[i].v, w = edges[i].weight;
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                prev[v] = u;
                updated = 1;
            }
        }
        if (!updated) break;
    }

    // Detect negative-weight cycles
    int hasNegCycle = 0;
    for (int i = 0; i < edgeCount; i++) {
        int u = edges[i].u, v = edges[i].v, w = edges[i].weight;
        if (dist[u] != INF && dist[u] + w < dist[v]) {
            hasNegCycle = 1;
            printf("WARNING: Negative-weight cycle detected involving edge %s->%s!\n",
                   branchNames[u], branchNames[v]);
        }
    }
    if (!hasNegCycle) printf("No negative-weight cycles detected. Network is stable.\n");

    printf("\n--- Shortest Paths from Branch %s ---\n", branchNames[src]);
    printf("%-10s %-12s %-20s\n", "Branch", "Min Cost", "Path");
    printf("%-10s %-12s %-20s\n", "------", "--------", "----");

    for (int i = 0; i < nodeCount; i++) {
        if (i == src) continue;
        printf("%-10s ", branchNames[i]);
        if (dist[i] == INF) {
            printf("%-12s UNREACHABLE\n", "INF");
            continue;
        }
        printf("%-12d ", dist[i]);

        // Reconstruct path
        int path[MAX_NODES], pathLen = 0, curr = i;
        while (curr != -1) { path[pathLen++] = curr; curr = prev[curr]; }
        for (int j = pathLen - 1; j >= 0; j--) {
            printf("%s", branchNames[path[j]]);
            if (j > 0) printf(" -> ");
        }
        printf("\n");
    }
}

int main() {
    printf("=== QUESTION 5: Banking Risk Propagation - Bellman-Ford ===\n\n");

    // Bank branch transaction network
    // Nodes: A=0, B=1, C=2, D=3, E=4, F=5, G=6, H=7
    // Directed weighted edges (transaction cost/risk)
    addEdge(0, 1, 4);   // A -> B: 4
    addEdge(0, 3, 16);  // A -> D: 16
    addEdge(1, 2, 6);   // B -> C: 6
    addEdge(1, 4, 7);   // B -> E: 7
    addEdge(2, 6, 9);   // C -> G: 9
    addEdge(3, 4, 3);   // D -> E: 3  (note: could be negative for suspicious route)
    addEdge(4, 5, 2);   // E -> F: 2
    addEdge(5, 2, -3);  // F -> C: -3 (suspicious/exploitable route - negative weight)
    addEdge(5, 6, 10);  // F -> G: 10
    addEdge(6, 7, 13);  // G -> H: 13
    addEdge(3, 7, 20);  // D -> H: 20

    printf("Transaction Network Edges:\n");
    for (int i = 0; i < edgeCount; i++)
        printf("  Branch %s -> Branch %s : cost/risk = %d\n",
               branchNames[edges[i].u], branchNames[edges[i].v], edges[i].weight);
    printf("\nNote: Negative edge weights indicate exploitable or suspicious routes.\n\n");

    bellmanFord(0); // Start from Branch A

    return 0;
}

