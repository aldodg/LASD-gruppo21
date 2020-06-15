#ifndef dijkstra_h
#define dijkstra_h

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include "Graph.h"

// Struttura che rappresenta il nodo minimo dello Heap
struct MinHeapNode
{
    int v;
    int dist;
    int precedente; //mi conservo il precedente per salvarmi il percorso esatto
};

// Struttura che rappresenta lo Heap minimo
struct MinHeap
{
    int size;    // Numero di nodi heap attualmente presenti
    int capacity; // capienza del min heap
    int *pos;    // serve per decrementare la chiave
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
void decreaseKey(struct MinHeap* minHeap, int, int v, int dist);
int isInMinHeap(struct MinHeap *minHeap, int v);
void printArr(int dist[], int n);
int dijkstra_durata(Graph G, int src, int, int);
int dijkstra_costo(Graph G, int src, int, int, int);

#endif
