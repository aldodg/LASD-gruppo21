#include "prenotazione.h"

Prenotati initNode(char *partenza, char *arrivo, int costo){
    Prenotati P = malloc(sizeof(struct voliPrenotati));
    P->partenza = partenza;
    P->arrivo = arrivo;
    P->costo = costo;
    P->next = NULL;
    return P;
}


Prenotati insertTail(Prenotati P, char *partenza , char *arrivo, int costo){
    if (P != NULL) {
        if (P->partenza != arrivo) {
            P->next = insertTail(P->next, partenza, arrivo, costo);
        }
    } else {
        P = initNode(partenza,arrivo,costo);
    }
    return P;
}


Prenotati insertHead(Prenotati P, char *partenza,char *arrivo, int costo) {
    if (P != NULL) {
        Prenotati X = malloc(sizeof(struct voliPrenotati));
        X->partenza = partenza;
        X->arrivo = arrivo;
        X->costo = costo;
        X->next = P;
        return X;
    }
    return initNode(partenza, arrivo, costo);
}


void printVoliPrenotati(Prenotati P){
    if (P != NULL) {
        printf(" %s %s ", P->partenza, P->arrivo);
        printf(" %d ", P->costo);
        printVoliPrenotati(P->next);
    }
}


void freeVoliPrenotati(Prenotati P){
    if (P != NULL) {
        freeVoliPrenotati(P->next);
        free(P);
    }
}
