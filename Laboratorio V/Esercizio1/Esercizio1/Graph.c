#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "Graph.h"


Graph initGraph(int nodes_count) {
    Graph G = malloc(sizeof(struct TGraph));
    G->adj = calloc(nodes_count, sizeof(List));
    G->nodes_count = nodes_count;
    return G;
}


Graph randomGraph(int nodes, int edges_min, int edges_max) {
    Graph G = initGraph(nodes);
    if (edges_max > nodes) {
        edges_max = nodes - 1;
    }
    int i = 0;
    int x = 0;
    int y = 0;
    for (i = 0; i < nodes; i++) {
        for (x = 0; x < edges_min; x ++) {
            addEdge(G, i, rand() % nodes, rand() % 50);
        }
        for (y = 0; y < rand() % (edges_max - edges_min); y++) {
            addEdge(G, i, rand() % nodes, rand() % 50);
        }
    }
    return G;
}


void freeGraph(Graph G) {
    if (G != NULL) {
        if (G->nodes_count > 0) {
            int i = 0;
            for (i = 0; i < G->nodes_count; i++) {
                freeList(G->adj[i]);
            }
        }
        free(G);
    }
}


void printGraph(Graph G) {
    if (G != NULL) {
        int x = 0;
        for (x = 0; x < G->nodes_count; x++) {
            printf("%d -> ", x);
            printList(G->adj[x]);
            printf("\n");
        }
    }
}

void addEdge(Graph G, int source, int target, int peso) {
    assert(G != NULL);
    assert(source < G->nodes_count);
    assert(target < G->nodes_count);
    if (source != target) {
        G->adj[source] = appendNodeList(G->adj[source], target, peso);
    }
}


void removeEdge(Graph G, int source, int target) {
    assert(G != NULL);
    assert(source < G->nodes_count);
    assert(target < G->nodes_count);
    if (source != target) {
        G->adj[source] = removeNodeList(G->adj[source], target);
    }
}


void addNode(Graph G) {
    if (G != NULL) {
        G->adj = realloc(G->adj, (G->nodes_count+1) * sizeof(List));
        G->nodes_count += 1;
        G->adj[G->nodes_count] = NULL;
    }
}

void removeNode(Graph G, int node_to_remove) {
        if (G != NULL) {
        int i = 0;
        int x = 0;
        List *tmp = G->adj;
        G->adj = (List *)calloc(G->nodes_count-1, sizeof(List));
        for (i = 0; i < G->nodes_count; i++) {
            if (i != node_to_remove) {
                G->adj[x] = checkListRemoval(tmp[i], node_to_remove);
                x++;
            } else {
				//freeList(G->adj[x]);
                freeList(tmp[i]);
            }
        }
        free(tmp);
        G->nodes_count -= 1;
    }
}

List checkListRemoval(List L, int node_to_remove) {
    if (L != NULL) {
        L->next = checkListRemoval(L->next, node_to_remove);
        if (L->target == node_to_remove) {
            List tmp = L->next;
            free(L);
            return tmp;
        } else if (L->target > node_to_remove) {
            L->target -= 1;
        }
    }
    return L;
}

int *calcolaGradoIn(Graph  G){
  int *gradiIn = NULL;
  if(G){
    int i;
    gradiIn = (int *)calloc(G->nodes_count,sizeof(int));
    List currEdge = NULL;
    for(i=0 ; i < G->nodes_count ; i++ )
      for( currEdge = G->adj ; currEdge ; currEdge = currEdge->next)
        gradiIn[currEdge->target]++;
  }
  return gradiIn;
}

int *calcolaGradoOut(Graph G){
  int * gradiOut = NULL;
  if(G){
    int i;
    gradiOut = (int *)calloc(G->nodes_count,sizeof(int));
    List  currEdge = NULL;
    for(i=0 ; i < G->nodes_count ; i++ )
    for( currEdge = G->adj ; currEdge ; currEdge = currEdge->next)
      gradiOut[currEdge->target]++;
  }
  return gradiOut;
}

void stampaGradi(Graph G, int  in, int  out){
  int i;
  if(G){
    for( i=0; i < G->nodes_count ; i++)
      printf("Nodo [%03d] - IN: %d - OUT: %d\n",i,in,out);
  }
}

