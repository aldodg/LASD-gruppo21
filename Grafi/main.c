#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Graph.h"


int main(int argc, const char * argv[])
{
    /*
    //srand((unsigned int)time(NULL));
    Graph L = initGraph(GRANDEZZA_GRAFO);
    addEdge(L, 1, 0, 20, 40);
    addEdge(L, 0, 1, 20, 40);
    printGraph(L);

    printf("\n\n");

    Nomi_Luoghi NM = NULL;
    NM = aggiungi_nome_citta(NM, 1, "Catania");
    NM = aggiungi_nome_citta(NM, 0, "Palermo");
    stampa_lista_nomi(NM);*/

    Graph L=NULL;
    Nomi_Luoghi NM = NULL;

    L=popola_grafo_file(L, &NM);
    printGraph(L);
    printf("\n\n");
    stampa_lista_nomi(NM);
    //aggiorna_grafo_file(L);
    printf("--------------------------------------------\n");
    removeEdge(L, 15, 14); //rimuovo la tratta da Catanzaro a reggio calabria
    printGraph(L);
    printf("--------------------------------------------\n");
    addEdge (L, 15, 14, 40, 25); //rimetto la tratta, impostando un costo di 40 euro e durata di 25 min
    printGraph(L);
    printf("----------------------------------------\n");
    removeNode (L, 15, &NM); //rimuovo catanzaro come aeroporto;
    printGraph(L);
    printf("\n\n");
    stampa_lista_nomi(NM);
    printf("-------------------------------------------\n");
    aggiungi_aeroporto(L, &NM);
    printGraph(L);
    printf("\n\n");
    stampa_lista_nomi(NM);

    freeGraph(L);
    cancellaListaNomi(NM);

    return 0;
}

