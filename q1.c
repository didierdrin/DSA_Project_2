#include <stdio.h>
#include <string.h>

#define MAX_SIZE 20

typedef struct {
    char id;
    int priority;
} Job;

Job heap[MAX_SIZE];
int heapSize = 0;

void swap(int i, int j) {
    Job temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}

void heapifyUp(int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (heap[parent].priority < heap[idx].priority) {
            swap(parent, idx);
            idx = parent;
        } else break;
    }
}

void heapifyDown(int idx) {
    while (1) {
        int left = 2*idx+1, right = 2*idx+2, largest = idx;
        if (left < heapSize && heap[left].priority > heap[largest].priority) largest = left;
        if (right < heapSize && heap[right].priority > heap[largest].priority) largest = right;
        if (largest != idx) { swap(idx, largest); idx = largest; }
        else break;
    }
}

void insert(char id, int priority) {
    heap[heapSize].id = id;
    heap[heapSize].priority = priority;
    heapSize++;
    heapifyUp(heapSize - 1);
}

void deleteRoot() {
    heap[0] = heap[heapSize - 1];
    heapSize--;
    heapifyDown(0);
}

void deleteByPriority(int priority) {
    int idx = -1;
    for (int i = 0; i < heapSize; i++) {
        if (heap[i].priority == priority) { idx = i; break; }
    }
    if (idx == -1) { printf("Job with priority %d not found.\n", priority); return; }
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
        printf("[%c:%d] ", heap[i].id, heap[i].priority);
    printf("\nTree structure (index-based):\n");
    int level = 0, count = 0, levelSize = 1;
    for (int i = 0; i < heapSize; i++) {
        if (count == 0) printf("Level %d: ", level);
        printf("[%c:%d] ", heap[i].id, heap[i].priority);
        count++;
        if (count == levelSize || i == heapSize - 1) {
            printf("\n");
            count = 0; level++; levelSize *= 2;
        }
    }
    printf("\n");
}

int main() {
    // Step 1: Build from array P = {42,17,93,28,65,81,54,60,99,73,88}
    int priorities[] = {42,17,93,28,65,81,54,60,99,73,88};
    int n = 11;
    char ids[] = "ABCDEFGHIJK";

    printf("=== QUESTION 1: Cloud Job Scheduler - Max-Heap ===\n\n");
    printf("Input array: P = {42, 17, 93, 28, 65, 81, 54, 60, 99, 73, 88}\n");
    printf("Job IDs assigned: A=42, B=17, C=93, D=28, E=65, F=81, G=54, H=60, I=99, J=73, K=88\n\n");

    // Build initial binary tree then heapify
    for (int i = 0; i < n; i++) {
        heap[i].id = ids[i];
        heap[i].priority = priorities[i];
    }
    heapSize = n;

    printf("--- Step 1: Initial Binary Tree (before heapify) ---\n");
    printHeap();

    // Build max-heap using bottom-up heapify
    for (int i = heapSize/2 - 1; i >= 0; i--)
        heapifyDown(i);

    printf("--- Step 2: After Building Max-Heap ---\n");
    printHeap();

    // Step 3: Insert priority 100
    printf("--- Step 3: Insert Urgent Job (Priority 100, ID='L') ---\n");
    insert('L', 100);
    printHeap();

    // Step 4: Remove priority 100
    printf("--- Step 4: Remove Job with Priority 100 (Aborted) ---\n");
    deleteByPriority(100);
    printHeap();

    return 0;
}
