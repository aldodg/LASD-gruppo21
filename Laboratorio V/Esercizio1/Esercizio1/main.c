#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "List.h"
#include "Graph.h"

int main()
{
    srand(time(NULL));

    Graph A;
    int entrante;
    int uscente;
    A=randomGraph(20,2,4);
    //printf("\nA= \n");
    //printGraph(A);

    printf("stampa il grado entrante ed uscente del grafo: \n");
    stampaGradi(A,&entrante,&uscente);


    return 0;
}
