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
    int contatore_voli;
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
void removeNode(Graph G, int node_to_remove, Nomi_Luoghi*);
List checkListRemoval(List L, int node_to_remove);

Nomi_Luoghi aggiungi_nome_citta(Nomi_Luoghi, int, char*);
void stampa_lista_nomi(Nomi_Luoghi NM);
Nomi_Luoghi checkListRemoval_perNomiLuoghi (Nomi_Luoghi L, int node_to_remove);
Graph popola_grafo_file (Graph, Nomi_Luoghi*);
void cancellaListaNomi(Nomi_Luoghi L);
void aggiungi_aeroporto(Graph, Nomi_Luoghi*);
void scelta_visualizza_elenco (Nomi_Luoghi NM);
//void aggiorna_grafo_file (Graph);

int empty_graph(Graph G);
int numeroVertici(Graph g);

int numeroArchi(Graph g);

int esisteArco(Graph g, int partenza, int arrivo);

int costoArco(Graph g, int partenza, int arrivo);

int esisteVertice(Graph g, int v);



#endif
