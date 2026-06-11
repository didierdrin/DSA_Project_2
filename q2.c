#include <stdio.h>
#include <string.h>

#define MAX_SIZE 20

typedef struct {
    char name[20];
    int riskScore;
} Passenger;

Passenger heap[MAX_SIZE];
int heapSize = 0;

void swap(int i, int j) {
    Passenger temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}

void heapifyUp(int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (heap[parent].riskScore < heap[idx].riskScore) {
            swap(parent, idx);
            idx = parent;
        } else break;
    }
}

void heapifyDown(int idx) {
    while (1) {
        int left = 2*idx+1, right = 2*idx+2, largest = idx;
        if (left < heapSize && heap[left].riskScore > heap[largest].riskScore) largest = left;
        if (right < heapSize && heap[right].riskScore > heap[largest].riskScore) largest = right;
        if (largest != idx) { swap(idx, largest); idx = largest; }
        else break;
    }
}

void insert(const char* name, int score) {
    strcpy(heap[heapSize].name, name);
    heap[heapSize].riskScore = score;
    heapSize++;
    heapifyUp(heapSize - 1);
}

void deleteByScore(int score) {
    int idx = -1;
    for (int i = 0; i < heapSize; i++) {
        if (heap[i].riskScore == score) { idx = i; break; }
    }
    if (idx == -1) { printf("Passenger with score %d not found.\n", score); return; }
    heap[idx] = heap[heapSize - 1];
    heapSize--;
    if (idx < heapSize) {
        heapifyUp(idx);
        heapifyDown(idx);
    }
}

void printHeap() {
    printf("Heap Array: ");
    for (int i = 0; i < heapSize; i++)
        printf("[%s:%d] ", heap[i].name, heap[i].riskScore);
    printf("\nTree structure:\n");
    int level = 0, count = 0, levelSize = 1;
    for (int i = 0; i < heapSize; i++) {
        if (count == 0) printf("Level %d: ", level);
        printf("[%s:%d] ", heap[i].name, heap[i].riskScore);
        count++;
        if (count == levelSize || i == heapSize - 1) {
            printf("\n");
            count = 0; level++; levelSize *= 2;
        }
    }
    printf("\n");
}

void extractPriorityQueue() {
    Passenger tempHeap[MAX_SIZE];
    int tempSize = heapSize;
    for (int i = 0; i < heapSize; i++) tempHeap[i] = heap[i];

    printf("Priority Queue - Screening Order (Highest Risk First):\n");
    int order = 1;
    while (heapSize > 0) {
        printf("  %d. %s (Risk Score: %d)\n", order++, heap[0].name, heap[0].riskScore);
        heap[0] = heap[heapSize - 1];
        heapSize--;
        heapifyDown(0);
    }
    // Restore heap
    heapSize = tempSize;
    for (int i = 0; i < heapSize; i++) heap[i] = tempHeap[i];
    printf("\n");
}

int main() {
    printf("=== QUESTION 2: Smart Airport Security - Max-Heap Priority Queue ===\n\n");

    // Passengers with assigned risk scores
    const char* names[] = {"Alice", "Brian", "Chen", "Fatima", "Noah", "Sofia"};
    int scores[] = {72, 55, 88, 63, 41, 79};
    int n = 6;

    printf("Passengers and Risk Scores:\n");
    for (int i = 0; i < n; i++)
        printf("  %s: %d\n", names[i], scores[i]);
    printf("\n");

    // Insert into array first for build-heap
    for (int i = 0; i < n; i++) {
        strcpy(heap[i].name, names[i]);
        heap[i].riskScore = scores[i];
    }
    heapSize = n;

    printf("--- Step 1: Initial Binary Tree (before heapify) ---\n");
    printHeap();

    // Build max-heap bottom-up
    for (int i = heapSize/2 - 1; i >= 0; i--)
        heapifyDown(i);

    printf("--- Step 2: After Building Max-Heap ---\n");
    printHeap();

    printf("--- Step 3: Priority Queue Extraction (Screening Order) ---\n");
    extractPriorityQueue();

    printf("--- Step 4: Insert New Passenger 'Zara' with Risk Score 98 ---\n");
    insert("Zara", 98);
    printHeap();

    printf("--- Step 5: Remove Passenger with Risk Score 98 (Cleared) ---\n");
    deleteByScore(98);
    printHeap();

    return 0;
}