#include "restituzione.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//questa funzione serve a determinare la riuscita della restituzione e infatti va a "dirigere" la struttura switch di restituisci_libro
int confronta_titoli_restituzione (char titolo_da_restituire[], Node *top, char matricola[])
{
    Node *tmp=top;
    int risultato_ricerca=0;

    if (tmp!=NULL)
    {

        //scorro la lista fino a finirla o fino a quando non sia stata trovata gia' la corrispondenza
        while (tmp!=NULL && risultato_ricerca<2)
        {
            if (!strcmp(titolo_da_restituire, tmp->nome_libro)) //cerco la riga col titolo giusto
            {
                if (!strcmp(tmp->matricola_studenteCheHaIlLibro, matricola)) //se anche la matricola corrisponde
                {
                    risultato_ricerca=2; //setto la flag in modo da fermare il ciclo
                    strcpy(tmp->matricola_studenteCheHaIlLibro, "xxxxxxxxx"); //e rimetto la matricola di default, indicante la disponibilita'
                }
                else risultato_ricerca=1; //scenario che simula un eventuale "disguido" esplicitato nella funzione successiva
            }
            tmp=tmp->next;
        }
    }

    return risultato_ricerca;
}

//questa funzione viene chiamata nel main e gestisce la restituzione di un libro
void restituisci_libro (Node *top, char matricola[])
{
    char titolo_da_restituire[DIM];
    char visualizza_elenco[2];

    printf("\nVuoi visualizzare una lista dei libri della Biblioteca?\nPremi 1 e poi invio per visualizzare, altrimenti 0 e invio:\t");
    scanf("%2s", visualizza_elenco);
    //la funzione seguente impedisce all'utente di fare inserimenti non validi o addirittura dannosi per il programma
    //non ci sarebbero errori qualora scrivesse una stringa e neanche un intero valido ma seguito da uno spazio e poi altro
    while ((visualizza_elenco[0]!='1' && visualizza_elenco[0]!='0') || visualizza_elenco[1]!='\0')
    {
        while (getchar()!='\n');
        printf("\nMi dispiace, scelta non valida. Riprova.\t");
        scanf("%2s",visualizza_elenco );

    }
    while (getchar()!='\n'); //pulisco buffer in ingresso (stdin)
    if (atoi(visualizza_elenco)) stampa_lista_privacy(top);

    printf("\nQuale libro vuoi restituire?\nSe ci hai ripensato, scrivi 0 e premi invio.\nRicorda di scrivere il titolo esatto!\t");
    //anche qui ho preferito usare scanf piuttosto che la piu' sicura fgets per ragioni di "pulizia": fgets memorizza il carattere \n e percio'
    //avrei dovuto aggiungere codice non bellissimo per rimuovere \n e sostituirlo con \0 affinche' i controlli successivi potessero funzionare.
    //La protezione, in ogni caso, e' ancora garantita dal while che pulisce il buffer in ingresso (stdin) per scongiurare comportamenti bizzarri
    //del programma qualora l'utente inserisca uno spazio e altri caratteri
    scanf("%100[^\n]", titolo_da_restituire);
    //pulisco buffer in ingresso (stdin) per scongiurare comportamenti bizzarri del programma qualora l'utente inserisca uno spazio e altri caratteri
    while (getchar()!='\n');

    if (titolo_da_restituire[0]!='0')
    {

        switch (confronta_titoli_restituzione(titolo_da_restituire, top, matricola))
        {
        case 1:
            printf("\n\nCi risulta che questo libro sia stato preso in prestito da un altro studente/studentessa oppure e' possibile"
                   " che tu abbia sbagliato a digitare la tua matricola.\nPurtroppo, nel primo caso, non possiamo autorizzarti a"
                   " restituire il libro per lui/lei, siamo spiacenti.\nSe invece sei davvero in possesso del libro, per favore contatta"
                   " direttamente il personale per risolvere, ci scusiamo per il disservizio. Grazie!\n\n");
            break;
        case 2:
            printf("\n\nPerfetto, il libro e' stato restituito. Torna a trovarci, grazie!\n\n");
            break;
        default:
            printf("\n\nPurtroppo non abbiamo trovato il libro nei nostri archivi. Forse hai commesso un errore di battitura, riprova.\n\n");
            break;
        }
    }
}


