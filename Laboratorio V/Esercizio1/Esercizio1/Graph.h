#ifndef Graph_Graph_h
#define Graph_Graph_h
#include "List.h"

struct TGraph {
    List *adj;
    int nodes_count;
};

typedef struct TGraph *Graph;

// Inizializza un nuovo grafo
// specifica in ingresso quanti nodi vuoi nel grafo
Graph initGraph(int nodes_count);

// Crea un grago in maniera randomica
Graph randomGraph(int nodes, int edges_min, int edges_max);

// Dealloca l'intero grafo
void freeGraph(Graph G);

// Stampa il grafo
void printGraph(Graph G);

// Aggiunge un arco, specificando sorgente,
// target e peso
void addEdge(Graph G, int source, int target, int peso);

// Rimuovi un arco specificando sorgente e target
void removeEdge(Graph G, int source, int target);

// Aggiungi un nodo
void addNode(Graph G);

// Rimuovi un nodo dal grafo, sistemando
// gli indici e riallocando la memoria
void removeNode(Graph G, int node_to_remove);

List checkListRemoval(List L, int );

int *calcolaGradoIn(Graph G);

int *calcolaGradoOut(Graph G);

void stampaGradi(Graph G , int *, int *);

#endif
