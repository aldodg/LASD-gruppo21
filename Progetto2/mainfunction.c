#include "mainfunction.h"
#include "stdinutils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Funzione d'azione per l'utente, viene chiamata una volta che le operazioni di login hanno successo*/
void login(Graph G, Customers Utenti, char *Username, Nomi_Luoghi NM)
{
    int choice;

    do
    {


        printf("\n\n---Menu' Principale Aeroporto---\n\n");
        printf("1 - Prenota un volo\n");
        printf("2 - Visualizza prenotazioni effettuate\n");
        printf("3 - Esci\nScegli:\t");


        scanf("%d", &choice);

        switch (choice)
        {

        case 1:


            prenotaVolo(G, Utenti, Username, NM);
            break;


        case 2:
            visualizza_prenotazioni_effettuate(Username, Utenti);
            break;

        case 3:

            return;

        default:

            printf("\nScelta non corretta\nDigitare 1 per prenotare un volot\n2Per visualizzare le prenotazioni effettuate\n3Per uscire\nScegli:\t");

        }

    }
    while (choice !=1 || choice !=2  || choice !=3);

}


void aggiungiTratta(Graph G, Nomi_Luoghi NM)
{
    int choice, partenza, destinazione, costo, durata;

    do
    {

        printf("\n\n---Menu' gestione aggiungi viaggio---\n\n");
        printf("1 - Aggiungi nuova tratta tra due aeroporti esistenti\n");
        printf("2 - Aggiungi nuovo aeroporto\n");
        printf("3 - Esci\nScegli:\t");

        choice=readint();

        switch (choice)
        {

        case 1:
        {

            scelta_visualizza_elenco(NM);
            printf("Imposta la partenza: \n");
            partenza=readint();
            printf("\nImposta la destinazione: \n");
            destinazione=readint();
            printf("\nImposta il costo in euro \n");
            costo=readint();
            printf("\nImposta la durata in minuti: \n");
            durata=readint();
            addEdge(G, partenza, destinazione, costo, durata);
            printf("\n\nFatto!\n");
            printGraph(G);
            printf("\n\n");
            stampa_lista_nomi(NM);

            break;
        }
        case 2:
        {
            aggiungi_aeroporto(G, &NM);
            break;
        }
        case 3:
        {


            return;

        }
        default:
        {

            printf("\nScelta non corretta:\nDigitare 1 per aggiungere un viaggio\nDigitare 2 per aggiungere un luogo\nDigitare 3 per uscire\nScegli:\t");
        }
        }
        break;
    }
    while(choice !=1 || choice !=2 || choice !=3);

}

void rimuoviTratta(Graph G, Nomi_Luoghi NM)
{
    int choice, partenza, destinazione, nodo_da_rimuovere;

    do
    {

        printf("\n\n---Menu' gestione rimuovi viaggio---\n\n");
        printf("1 - Rimuovi tratta tra due aeroporti\n");
        printf("2 - Rimuovi aeroporto\n");
        printf("3 - Esci\nScegli:\t");
        fflush(stdin);
        choice=readint();

        switch (choice)
        {

        case 1:
        {

            printGraph(G);
            printf("\n\n");
            stampa_lista_nomi(NM);
            printf("Imposta la partenza.\t");
            scanf("%d",&partenza);

            printf("Imposta la destinazione.\t");
            scanf("%d",&destinazione);
            removeEdge(G, partenza, destinazione);
            printf("Fatto!\n");
            printGraph(G);
            printf("\n\n");

            break;
        }
        case 2:
        {
            scelta_visualizza_elenco(NM);
            printf("Scegli l'aeroporto da rimuovere.\t");
            fflush(stdin);
            scanf("%d",&nodo_da_rimuovere);

            removeNode(G, nodo_da_rimuovere, &NM);
            printf("Fatto!\n");
            stampa_lista_nomi(NM);

            break;
        }
        case 3:
        {


            return;

        }
        default:
        {

            printf("\nScelta non corretta:\nDigitare 1 per rimuovere un viaggio\nDigitare 2 per eliminare un luogo\nDigitare 3 per uscire\nScegli:\t");
        }
        }
        break;
    }
    while(choice !=1 || choice !=2 || choice !=3);

}

void menutratte(Graph G, Nomi_Luoghi NM)
{
    Nomi_Luoghi Luoghi = NM;

    int choice;

    do
    {

        printf("\n\n---Menu' gestione tratte---\n\n");
        printf("1 - Aggiungere viaggio\n");
        printf("2 - Rimuovi viaggio\n");
        printf("3 - Esci\nScegli:\t");
        fflush(stdin);
        choice=readint();

        switch (choice)
        {

        case 1:
        {

            aggiungiTratta(G, Luoghi);

            break;
        }
        case 2:
        {
            rimuoviTratta(G, Luoghi);

            break;
        }
        case 3:
        {

            return;

        }
        default:
        {
            printf("\nScelta non corretta:\nDigitare 1 per aggiungere una tratta\nDigitare 2 per eliminare una tratta\nDigitare 3 per uscire.\nScegli:\t");
        }
        }
        break;
    }
    while(choice !=1 || choice !=2 || choice !=3);

}

