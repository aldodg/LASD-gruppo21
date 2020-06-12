#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "matrice.h"
int main()
{

    srand(time(NULL));

    Graphmat A;
    int* entrante;
    int* uscente;
    A=randomGraphMat(10);
    //printf("\nA= \n");
    printGraphMat(A);
    uscente=calcolaGradoUscente(A);
    entrante=calcolaGradoEntrante(A);


    printf("\nstampa il grado entrante ed uscente del grafo: \n");
    stampaGradi(A,entrante, uscente);


    return 0;
}
