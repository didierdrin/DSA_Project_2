#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NODES 10
#define MAX_EDGES 50
#define INF 0

// Graph for enterprise workstation network
// Nodes: 0=WS1, 1=WS2, 2=WS3, 3=WS4, 4=WS5, 5=WS6, 6=WS7
// Edges with data transfer times (minutes)

int adjMatrix[MAX_NODES][MAX_NODES];
int nodeCount = 7;
char* wsNames[] = {"WS1","WS2","WS3","WS4","WS5","WS6","WS7"};

void addEdge(int u, int v, int weight) {
    adjMatrix[u][v] = weight;
    adjMatrix[v][u] = weight;
}

void bfs(int start) {
    int visited[MAX_NODES] = {0};
    int queue[MAX_NODES];
    int front = 0, rear = 0;

    visited[start] = 1;
    queue[rear++] = start;

    printf("BFS traversal from %s:\n", wsNames[start]);
    printf("  Visiting: %s (Source / Suspected Breach Point)\n", wsNames[start]);

    // One-hop neighbors with their transfer times
    printf("\nDirect Neighbors (One-Hop Contacts) of %s:\n", wsNames[start]);
    printf("  %-8s | Transfer Time (min)\n", "Node");
    printf("  ---------|--------------------\n");

    int maxTime = -1, maxNode = -1;

    while (front < rear) {
        int curr = queue[front++];
        for (int i = 0; i < nodeCount; i++) {
            if (adjMatrix[curr][i] > 0 && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
                if (curr == start) { // Only direct neighbors
                    printf("  %-8s | %d min\n", wsNames[i], adjMatrix[curr][i]);
                    if (adjMatrix[curr][i] > maxTime) {
                        maxTime = adjMatrix[curr][i];
                        maxNode = i;
                    }
                }
            }
        }
        if (curr != start) break; // Only go one hop deep for analysis
    }

    printf("\nHighest Risk Contact Analysis:\n");
    if (maxNode != -1)
        printf("  => %s has the highest data transfer time: %d minutes\n", wsNames[maxNode], maxTime);
    printf("  => This workstation is at HIGHEST RISK of exposure and data breach propagation.\n");
}

int main() {
    printf("=== QUESTION 4: Cyber Incident BFS Analysis ===\n\n");

    memset(adjMatrix, 0, sizeof(adjMatrix));

    // Enterprise communication graph
    // WS1=0, WS2=1, WS3=2, WS4=3, WS5=4, WS6=5, WS7=6
    addEdge(0, 1, 8);   // WS1-WS2: 8 min
    addEdge(0, 2, 15);  // WS1-WS3: 15 min
    addEdge(0, 3, 5);   // WS1-WS4: 5 min
    addEdge(1, 4, 12);  // WS2-WS5: 12 min
    addEdge(2, 4, 7);   // WS3-WS5: 7 min
    addEdge(2, 5, 9);   // WS3-WS6: 9 min
    addEdge(3, 5, 11);  // WS4-WS6: 11 min
    addEdge(4, 6, 6);   // WS5-WS7: 6 min
    addEdge(5, 6, 14);  // WS6-WS7: 14 min

    printf("Enterprise Communication Graph:\n");
    printf("  WS1 <-> WS2: 8 min\n");
    printf("  WS1 <-> WS3: 15 min\n");
    printf("  WS1 <-> WS4: 5 min\n");
    printf("  WS2 <-> WS5: 12 min\n");
    printf("  WS3 <-> WS5: 7 min\n");
    printf("  WS3 <-> WS6: 9 min\n");
    printf("  WS4 <-> WS6: 11 min\n");
    printf("  WS5 <-> WS7: 6 min\n");
    printf("  WS6 <-> WS7: 14 min\n\n");

    // User input
    char input[10];
    int suspect = -1;
    printf("Enter suspected compromised workstation (e.g., WS1, WS2, ...WS7): ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;

    for (int i = 0; i < nodeCount; i++) {
        if (strcmp(input, wsNames[i]) == 0) { suspect = i; break; }
    }

    if (suspect == -1) {
        printf("Workstation not found. Defaulting to WS1.\n");
        suspect = 0;
    }
    printf("\n");

    bfs(suspect);

    return 0;
}
