#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "List.h"
#include "Graph.h"
#include<string.h>
int main()
{
    srand(time(NULL));

    Graph A;
    int* entrante;
    int* uscente;
    A=randomGraph(10,0,4);
    //printf("\nA= \n");
    printGraph(A);
    uscente=calcolaGradoUscente(A);
    entrante=calcolaGradoEntrante(A);


    printf("\nstampa il grado entrante ed uscente del grafo: \n");
    stampaGradi(A,entrante, uscente);


    return 0;
}
