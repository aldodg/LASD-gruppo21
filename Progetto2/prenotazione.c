#include "prenotazione.h"

Prenotati initNode(char *partenza, char *destinazione, int costo, int durata)
{
    Prenotati P = (Prenotati)malloc(sizeof(struct voliPrenotati));
    P->partenza = partenza;
    P->destinazione = destinazione;
    P->costo = costo;
    P->durata = durata;
    P->next = NULL;
    return P;
}


Prenotati insertTail(Prenotati P, char *partenza, char *destinazione, int costo, int durata)
{
    if (P != NULL)
    {
        P->next = insertTail(P->next, partenza, destinazione, costo, durata);
    }
    else
    {
        P = initNode(partenza,destinazione,costo,durata);
    }
    return P;
}


Prenotati insertHead(Prenotati P, char *partenza,char *destinazione, int costo, int durata)
{
    if (P != NULL)
    {
        Prenotati X = (Prenotati )malloc(sizeof(struct voliPrenotati));
        X->partenza = partenza;
        X->destinazione = destinazione;
        X->costo = costo;
        X->durata=durata;
        X->next = P;
        return X;
    }
    return initNode(partenza, destinazione, costo, durata);
}


void printVoliPrenotati(Prenotati P)
{
    if (P != NULL)
    {
        printf(" %s %s ", P->partenza, P->destinazione);
        printf(" %d ", P->costo);
        printf(" %d ", P->durata);
        printVoliPrenotati(P->next);
    }
}


void freeVoliPrenotati(Prenotati P)
{
    if (P != NULL)
    {
        freeVoliPrenotati(P->next);
        free(P);
    }
}
