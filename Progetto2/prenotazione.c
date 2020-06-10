#include "prenotazione.h"
//#include "customers.h"

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


Prenotati insertHead(Prenotati P, int partenza,int destinazione, int costo, int durata)
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
        printf("\n");
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




//void prenotaVolo () {}




/* la commento perche' non riesce a vedere customers come tipo. tuttavia se aggiungo l'include in alto commentato da' tutto un casino

void visualizza_prenotazioni_effettuate(char *username, Customers Utenti_registrati)
{

    //ho il dubbio che possa andare in seg scritta cosi' in un caso particolare ma in effetti non credo
    //se dovesse dare problemi basta mettere la strcmp in un if dentro il ciclo e aggiornare una flag quando entra nell'if per uscire dal ciclo
    while (Utenti_registrati!=NULL && !strcmp(Utenti_registrati->user, username))
    {
        Utenti_registrati=Utenti_registrati->next;
    }
    printVoliPrenotati(Utenti_registrati->elenco_prenotazioni);

}
*/
