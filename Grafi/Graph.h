#ifndef Graph_Graph_h
#define Graph_Graph_h
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
    struct nomi *next;
};

typedef struct nomi* Nomi_Luoghi;

// Inizializza un nuovo grafo
// specifica in ingresso quanti nodi vuoi nel grafo
Graph initGraph(int nodes_count);

// Dealloca l'intero grafo
void freeGraph(Graph G);

// Stampa il grafo
void printGraph(Graph G);

// Aggiunge un arco, specificando sorgente,
// target e peso (costo_tratta)
void addEdge(Graph G, int source, int target, int costo_tratta, int durata_tratta);

// Rimuovi un arco specificando sorgente e target
void removeEdge(Graph G, int source, int target);

// Aggiungi un nodo
void addNode(Graph G);

// Rimuovi un nodo dal grafo, sistemando
// gli indici e riallocando la memoria
void removeNode(Graph G, int node_to_remove);
List checkListRemoval(List L, int node_to_remove);

Nomi_Luoghi aggiungi_nome_citta(Nomi_Luoghi, int, char*);
void stampa_lista_nomi(Nomi_Luoghi NM);

#endif
