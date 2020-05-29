#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct arco{
  char *localita;
  struct arco *next;
  int costo;
}arco;

typedef struct grafo{
  int n_vertici;
  arco **adiacenti;
}grafo;


int empty_graph(struct grafo*);

int creaGrafo(int, grafo **, int);

void stampaGrafo(grafo *);

arco *nuovoArco(int, int );


#endif // GRAPH_H_INCLUDED
