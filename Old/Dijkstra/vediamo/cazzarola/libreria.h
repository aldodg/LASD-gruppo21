#ifndef Graph_Graph_h
#define Graph_Graph_h

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include "List.h"

//struttura del grafo
struct TGraph {
    List *adj;
    int nodes_count;
};

typedef struct TGraph* Graph;

//struttura della lista che contiene le corrispondenze fra identificativi di nodi e nomi di luoghi in cui c'e' l'aeroporto a cui si
//riferisce l'identificativo univoco
struct nomi {
    char *nome_luogo;
    int id;
    int contatore_voli;
    struct nomi *next;
};

/*struct TList {
    int target; //nodo della destinazione a cui ci stiamo riferendo
    int costo_tratta; //considerato come peso dell'arco
    int durata_tratta; //durata prevista del volo in minuti
    struct TList* next;
};

typedef struct TList* List;
*/

typedef struct nomi* Nomi_Luoghi;

// Structure to represent a min heap node
struct MinHeapNode
{
    int v;
    int dist;
    struct MinHeapNode *parent; //Keep some extra information like a parent pointer which points to the previous node discovered.
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
void dijkstra( Graph G, int src);

#endif
