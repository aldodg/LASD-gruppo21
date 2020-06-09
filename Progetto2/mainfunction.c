#include "mainfunction.h"
#include "stdinutils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//gli deve arrivare username dell'utente loggato!! ci sta un modo per controllare che l'username sia univoco?
//deve arrivare anche la lista di tutti gli utenti registrati e non so che altro

void login()
{
    int choice;

    do
    {


        printf("\n\n---Menu' Principale Aeroporto---\n\n");
        printf("1 - Prenota un volo\n");
        printf("2 - Visualizza prenotazioni effettuate\n");
        printf("3 - Esci\n");

        choice=readint();

        switch (choice)
        {

        case 1:

            //prenotaVolo(Lista_prenotazioni);
            break;


        case 2:
            //visualizza_prenotazioni_effettuate(username, Utenti_registrati);
            break;

        case 3:

            return;

        default:

            printf("\nScelta non corretta\nDigitare 1 per prenotare un volot\n2Per visualizzare le prenotazioni effettuate\n3Per uscire");

        }

    }
    while (choice !=1 || choice !=2  || choice !=3);

}


void aggiungiTratta()  //SONO BUONE NON CANCELLARE
{
    /*int choice, partenza, destinazione, costo, durata;

    do
    {

        printf("\n\n---Menu' gestione aggiungi tratta---\n\n");
        printf("1 - Aggiungi viaggio\n");
        printf("2 - Aggiungi luogo\n");
        printf("3 - Esci\n");

        choice=readint();

        switch (choice)
        {

        case 1:
        {

            scelta_visualizza_elenco();
            printf("Imposta la partenza.\t");
            partenza=readint();
            printf("Imposta la destinazione.\t");
            partenza=readint();
            printf("Imposta il costo.\t");
            costo=readint();
            printf("Imposta la durata.\t");
            durata=readint();
            addEdge(G, partenza, destinazione, costo, durata);
            printf("Fatto!");

            break;
        }
        case 2:
        {
            aggiungi_aeroporto(G, *NM);
            break;
        }
        case 3:
        {


            return;

        }
        default:
        {

            //printf("\nScelta non corretta:\nDigitare 1 per aggiungere una tratta\nDigitare 2 per eliminare una tratta\nDigitare 3 per uscire");
        }
        }
        break;
    }
    while(choice !=1 || choice !=2 || choice !=3);
*/
}

void rimuoviTratta()    //SONO BUONE NON CANCELLARE
{
    /*int choice, partenza, destinazione, nodo_da_rimuovere;

    do
    {

        printf("\n\n---Menu' gestione rimuovi tratta---\n\n");
        printf("1 - Rimuovi viaggio\n");
        printf("2 - Rimuovi luogo\n");
        printf("3 - Esci\n");

        choice=readint();

        switch (choice)
        {

        case 1:
        {

            scelta_visualizza_elenco();
            printf("Imposta la partenza.\t");
            partenza=readint();
            printf("Imposta la destinazione.\t");
            partenza=readint();
            removeEdge(G, partenza, destinazione);
            printf("Fatto!\n");

            break;
        }
        case 2:
        {
            scelta_visualizza_elenco();
            printf("Scegli il luogo da rimuovere.\t");
            nodo_da_rimuovere=readint();
            removeNode(G, nodo_da_rimuovere, NM);
            printf("Fatto!\n");

            break;
        }
        case 3:
        {


            return;

        }
        default:
        {

            //printf("\nScelta non corretta:\nDigitare 1 per aggiungere una tratta\nDigitare 2 per eliminare una tratta\nDigitare 3 per uscire");
        }
        }
        break;
    }
    while(choice !=1 || choice !=2 || choice !=3);
*/
}

void menutratte()
{

    int choice;

    do
    {

        printf("\n\n---Menu' gestione tratte---\n\n");
        printf("1 - Aggiungere tratta\n");
        printf("2 - Rimuovi tratta\n");
        printf("3 - Esci\n");

        choice=readint();

        switch (choice)
        {

        case 1:
        {

            aggiungiTratta();

            break;
        }
        case 2:
        {
            rimuoviTratta();

            break;
        }
        case 3:
        {

            return;

        }
        default:
        {
            //printf("\nScelta non corretta:\nDigitare 1 per aggiungere una tratta\nDigitare 2 per eliminare una tratta\nDigitare 3 per uscire");
        }
        }
        break;
    }
    while(choice !=1 || choice !=2 || choice !=3);

}


