#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "matrice.h"
#define EDGE_SUCC_MAT 0.33

Graphmat randomGraphMat(int nodes){
  Graphmat G = initGraphMat(nodes);
  int i = 0;
  int j = 0;
  float p = 0;


  if(nodes>0){
    for(i=0;i<G->nodes_count;i++){
      for(j=0;j<G->nodes_count;j++){
        if(i!=j){ //per evitare di costruire cappi
          p=(float)((rand()%nodes)+1)/nodes;
          if(p<=EDGE_SUCC_MAT){
            addEdgeMat(G,i,j,(rand()%100)+1);
          }
        }
      }
    }
  }
  return G;
}


Graphmat initGraphMat(int nodes_count) {
    Graphmat G = (Graphmat)malloc(sizeof(struct graphmat));
    G->adj = (int*)malloc( (nodes_count * nodes_count) * sizeof(int));
    G->weights = (int*)calloc( (nodes_count * nodes_count), sizeof(int));
    G->nodes_count = nodes_count;
    return G;
}

void freeGraphMat(Graphmat G) {
    if (G != NULL) {
        if (G->nodes_count > 0) {
            free(G->adj);
            free(G->weights);
        }
        free(G);
    }
}

void printGraphAuxMat(Graphmat G) {
  int x = 0, i= 0;
	if (G != NULL) {
    for (x = 0; x < G->nodes_count; x++) {
      printf("%d -> ", x);
      for(i = 0; i < G->nodes_count; i++){
        if(G->adj[(x * G->nodes_count) + i] == 1){
          printf(" %d(%d) ", i, G->weights[(x * G->nodes_count) + i]);
        }
      }
      printf("\n");
    }
  }
}

void printGraphMat(Graphmat G) {
    printGraphAuxMat(G);
	  printf("\n\n");
}

void addEdgeMat(Graphmat G, int source, int target, int peso) {
    assert(G != NULL);
    assert(source < G->nodes_count);
    assert(target < G->nodes_count);
    if (source != target && G->adj[(G->nodes_count * source) + target] == 0){
        G->adj[(G->nodes_count * source) + target] = 1;
        G->weights[(G->nodes_count * source) + target] = peso;
    }
}

void removeEdgeMat(Graphmat G, int source, int target) {
    assert(G != NULL);
    assert(source < G->nodes_count);
    assert(target < G->nodes_count);
    if (source != target && G->adj[(G->nodes_count * source) + target] == 1){
      G->adj[(G->nodes_count * source) + target] = 0;
      G->weights[(G->nodes_count * source) + target] = 0;
    }
}

void addNodeMat(Graphmat G) {
    if (G != NULL) {
    	int *old=G->adj;
      int *pesi=G->weights;
    	int i=0, j=0;

        G->adj = (int *)calloc(((G->nodes_count+1) * (G->nodes_count+1)), sizeof(int));
        G->weights = (int *)calloc(((G->nodes_count+1) * (G->nodes_count+1)), sizeof(int));
        while(j < (G->nodes_count * G->nodes_count)){
          if(j != 0 && (j % G->nodes_count) == 0){
            i++;
          }
          G->adj[i] = old[j];
          G->weights[i] = pesi[j];
          j++;
          i++;
        }
        free(old);
        free(pesi);
        G->nodes_count += 1;
    }
}

int graphIndexMat(Graphmat G, int i, int j){//restituisce l'indice della locazione nella matrice di adiacenza con riga i e colonna j
  return (i * G->nodes_count) + j;
}

void removeNodeMat(Graphmat G, int node_to_remove) {
    if (G != NULL) {
        int i = 0;
        int j = 0;
        //int x = 0;
        int *old = G->adj;
        int *pesi = G->weights;
        G->adj = (int *)malloc((G->nodes_count-1) * (G->nodes_count-1) * sizeof(int));
        G->weights = (int *)malloc((G->nodes_count-1) * (G->nodes_count-1) * sizeof(int));
        while(j < (G->nodes_count-1) * (G->nodes_count-1)){
          if(i != 0 && i % G->nodes_count == node_to_remove){
            i++;
          }else if(i == (node_to_remove * G->nodes_count)){
            i = i + G->nodes_count;
          }else{
            G->adj[j] = old[i];
            G->weights[j] = pesi[i];
            j++;
            i++;
          }
        }
        free(old);
        free(pesi);
        G->nodes_count -= 1;
    }
}


int *calcolaGradoUscente(Graphmat G){
  int * gradiEntr = NULL;
  if(G){
    int i;
    gradiEntr = (int *)calloc(G->nodes_count,sizeof(int));
    int * currEdge = NULL;
    for(i=0 ; i < G->nodes_count ; i++ )
    for( currEdge = G->adj[i] ; currEdge ; currEdge = currEdge->weights)
         gradiEntr[i]++;
  }
  return gradiEntr;
}

int *calcolaGradoEntrante(Graphmat G){
  int * gradiEntr = NULL;
  if(G){
    int i;
    gradiEntr = (int *)calloc(G->nodes_count,sizeof(int));
    int * currEdge = NULL;
    for(i=0 ; i < G->nodes_count ; i++ )
    for( currEdge = G->adj[i] ; currEdge ; currEdge = currEdge->weights)
      gradiEntr[currEdge->target]++;
  }
  return gradiEntr;
}

void stampaGradi(Graphmat G, int * in, int * out){
  int i;
  if(G){
    for( i=0; i < G->nodes_count ; i++)
      printf("Nodo [%d] - Grado Entrante: %d - Grado uscente: %d\n",i,in[i],out[i]);
  }
}
