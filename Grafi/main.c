#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Graph.h"
#define GRANDEZZA_GRAFO 10


int main(int argc, const char * argv[])
{
    //srand((unsigned int)time(NULL));
    Graph L = initGraph(GRANDEZZA_GRAFO);
    addEdge(L, 1, 0, 20, 40);
    addEdge(L, 0, 1, 20, 40);
    printGraph(L);

    printf("\n\n");

    Nomi_Luoghi NM = NULL;
    NM = aggiungi_nome_citta(NM, 1, "Catania");
    NM = aggiungi_nome_citta(NM, 0, "Palermo");
    stampa_lista_nomi(NM);

    return 0;
}

