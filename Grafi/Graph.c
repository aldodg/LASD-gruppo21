#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include "Graph.h"

//crea il grafo, della dimensione specificata, e inizializza i suoi nodi allocandone anche la memoria per ognuno
Graph initGraph(int nodes_count)
{
    Graph G = malloc(sizeof(struct TGraph));
    G->adj = calloc(nodes_count, sizeof(List));
    G->nodes_count = nodes_count;

    return G;
}

Nomi_Luoghi aggiungi_nome_citta (Nomi_Luoghi L, int id, char *luogo)
{
    Nomi_Luoghi nuovo=malloc(sizeof(struct nomi));

    if (L != NULL)
    {
        L->next = aggiungi_nome_citta(L->next, id, luogo);
    }
    else
    {
        nuovo->id=id;
        nuovo->nome_luogo=(char*)malloc((strlen(luogo)+1)*sizeof(char));
        strcpy(nuovo->nome_luogo, luogo);
        nuovo->next=NULL;
        L = nuovo;
    }

    return L;
}

void stampa_lista_nomi(Nomi_Luoghi NM)
{
    if (NM != NULL)
    {
        printf("Nodo %d -> %s\n", NM->id, NM->nome_luogo);
        stampa_lista_nomi(NM->next);
        printf("\n");

    }
}

void freeGraph(Graph G)
{
    if (G != NULL)
    {
        if (G->nodes_count > 0)
        {
            int i = 0;
            for (i = 0; i < G->nodes_count; i++)
            {
                freeList(G->adj[i]);
            }
        }
        free(G);
    }
}

//funzione di test che stampa il grafo nel seguente formato: nodo in considerazione -> tutti i nodi ad esso collegati
void printGraph(Graph G)
{
    if (G != NULL)
    {
        int x = 0;
        for (x = 0; x < G->nodes_count; x++)
        {
            printf("Nodo %d -> ", x);
            printList(G->adj[x]);
            printf("\n");
        }
    }
}

//questa funzione va a creare un arco fra due nodi del grafo creati in precedenza con initGraph dopo aver stabilito quali siano
//i due nodi in questione, il peso(costo_tratta) dell'arco e la durata della tratta
void addEdge(Graph G, int source, int target, int costo_tratta, int durata_tratta)
{
    assert(G != NULL);
    assert(source < G->nodes_count);
    assert(target < G->nodes_count);
    if (source != target)
    {
        G->adj[source] = appendNodeList(G->adj[source], target, costo_tratta, durata_tratta);
    }
}


void removeEdge(Graph G, int source, int target)
{
    assert(G != NULL);
    assert(source < G->nodes_count);
    assert(target < G->nodes_count);
    if (source != target)
    {
        G->adj[source] = removeNodeList(G->adj[source], target);
    }
}


void addNode(Graph G)
{
    if (G != NULL)
    {
        G->adj = realloc(G->adj, (G->nodes_count+1) * sizeof(List));
        G->nodes_count += 1;
        G->adj[G->nodes_count] = NULL;
    }
}


void removeNode(Graph G, int node_to_remove)
{
    if (G != NULL)
    {
        int i = 0;
        int x = 0;
        List *tmp = G->adj;
        G->adj = calloc(G->nodes_count, sizeof(List));
        for (i = 0; i <= G->nodes_count; i++)
        {
            if (i != node_to_remove)
            {
                G->adj[x] = checkListRemoval(tmp[i], node_to_remove);
                x++;
            }
            else
            {
                freeList(G->adj[x]);
            }
        }
        free(*tmp);
        G->nodes_count -= 1;
    }
}


List checkListRemoval(List L, int node_to_remove)
{
    if (L != NULL)
    {
        L->next = checkListRemoval(L->next, node_to_remove);
        if (L->target == node_to_remove)
        {
            List tmp = L->next;
            free(L);
            return tmp;
        }
        else if (L->target > node_to_remove)
        {
            L->target -= 1;
        }
    }
    return L;
}


