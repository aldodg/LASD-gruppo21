#include "gettonate.h"

Gettonate initList(char *partenza, char *destinazione, int cont){
    Gettonate G = (Gettonate)malloc(sizeof(struct MeteGettonate));
    G->partenza = partenza;
    G->destinazione = destinazione;
    G->cont=cont;
    G->next = NULL;
    return G;
}


Gettonate insertTailGettonate(Gettonate G, char *partenza , char *destinazione, int cont){
    if (G != NULL) {
        G->next = insertTailGettonate(G->next, partenza, destinazione, cont);
    }
    else{
        G = initList(partenza,destinazione, cont);
    }
    return G;
}


Gettonate insertHeadGettonate(Gettonate G, char *partenza ,char *destinazione, int cont){
    if (G != NULL) {
        Gettonate M = (Gettonate )malloc(sizeof(struct MeteGettonate));
        M->partenza = partenza;
        M->destinazione = destinazione;
        M->cont=cont;
        M->next = G;
        return M;
    }
    return initList(partenza,destinazione,cont);
}


void printMeteGettonate(Gettonate G){
    if (G != NULL) {
        printf("%s%s  ", G->partenza,G->destinazione);
        printf(" %d ", G->cont);
        printMeteGettonate(G->next);
    }
}


void freeListGettonate(Gettonate G){
    if (G != NULL) {
        freeListGettonate(G->next);
        free(G);
    }
}
