#include "mainfunction.h"
#include "stdinutils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "prenotazione.h"



//gli deve arrivare username dell'utente loggato!! ci sta un modo per controllare che l'username sia univoco?
//deve arrivare anche la lista di tutti gli utenti registrati e non so che altro

void login(Graph G, Customers *Utenti, char *Username, Nomi_Luoghi NM)
{
    int choice;

    do
    {


        printf("\n\n---Menu' Principale Aeroporto---\n\n");
        printf("1 - Prenota un volo\n");
        printf("2 - Visualizza prenotazioni effettuate\n");
        printf("3 - Esci\nScegli:\t");

        //choice=readint();
        scanf("%d", &choice);

        switch (choice)
        {

        case 1:

            (*Utenti)->punti=4;
            prenotaVolo(G, Utenti, Username, NM);

            //printf("%d ggg", (*Utenti)->punti);
            break;


        case 2:
            visualizza_prenotazioni_effettuate(username, Utenti);
            break;

        case 3:

            return;

        default:

            printf("\nScelta non corretta\nDigitare 1 per prenotare un volot\n2Per visualizzare le prenotazioni effettuate\n3Per uscire\nScegli:\t");

        }

    }
    while (choice !=1 || choice !=2  || choice !=3);

}


void aggiungiTratta(Graph G, Nomi_Luoghi NM)  //SONO BUONE NON CANCELLARE
{
    int choice, partenza, destinazione, costo, durata;

    do
    {

        printf("\n\n---Menu' gestione aggiungi tratta---\n\n");
        printf("1 - Aggiungi nuovo viaggio\n");
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
            printf("Fatto!");
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

void rimuoviTratta(Graph G, Nomi_Luoghi NM)    //SONO BUONE NON CANCELLARE
{
    int choice, partenza, destinazione, nodo_da_rimuovere;

    do
    {

        printf("\n\n---Menu' gestione rimuovi tratta---\n\n");
        printf("1 - Rimuovi viaggio\n");
        printf("2 - Rimuovi luogo\n");
        printf("3 - Esci\nScegli:\t");

        choice=readint();

        switch (choice)
        {

        case 1:
        {

            printGraph(G);
            printf("\n\n");
            stampa_lista_nomi(NM);
            printf("Imposta la partenza.\t");
            partenza=readint();
            printf("Imposta la destinazione.\t");
            destinazione=readint();
            removeEdge(G, partenza, destinazione);
            printf("Fatto!\n");
            printGraph(G);
            printf("\n\n");

            break;
        }
        case 2:
        {
            scelta_visualizza_elenco(NM);
            printf("Scegli il luogo da rimuovere.\t");
            nodo_da_rimuovere=readint();
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
        printf("1 - Aggiungere tratta\n");
        printf("2 - Rimuovi tratta\n");
        printf("3 - Esci\nScegli:\t");

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

