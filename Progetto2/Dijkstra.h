#ifndef dijkstra_h
#define dijkstra_h

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include "Graph.h"

//typedef struct nomi* Nomi_Luoghi;

// Structure to represent a min heap node
struct MinHeapNode
{
    int v;
    int dist;
};

// Structure to represent a min heap
struct MinHeap
{
    int size;    // Number of heap nodes present currently
    int capacity; // Capacity of min heap
    int *pos;    // This is needed for decreaseKey()
    struct MinHeapNode **array;
};


// Inizializza un nuovo grafo
// specifica in ingresso quanti nodi vuoi nel grafo
int empty_graph(Graph G);
Graph initGraph(int nodes_count);
void addEdge(Graph G, int source, int target, int costo_tratta, int durata_tratta);
struct MinHeapNode* newMinHeapNode(int v, int dist);
struct MinHeap* createMinHeap(int capacity);
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b);
void minHeapify(struct MinHeap* minHeap, int idx);
int isEmpty(struct MinHeap* minHeap);
struct MinHeapNode* extractMin(struct MinHeap* minHeap);
void decreaseKey(struct MinHeap* minHeap, int v, int dist);
int isInMinHeap(struct MinHeap *minHeap, int v);
void printArr(int dist[], int n);
int dijkstra_durata(Graph G, int src, int);
int dijkstra_costo(Graph G, int src, int);

#endif
