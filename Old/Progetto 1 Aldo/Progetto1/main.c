#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deposito_libri.h"
#include "restituzione.h"
#include "prestito.h"


int main()
{
    char matricola[MATR];
    char scelta_menu[2];
    Node *top=NULL; //lista che conserva tutti i libri della biblioteca, una sorta di registro
    Node_Sospese *top_richieste=NULL; //lista che conserva tutte le richieste pendenti

    matricola[0]='1';
    top=popola_con_libri_default(top);
    top_richieste=carica_richieste_pregresse(top_richieste);

    //questo e' il menu principale; il while esterno termina quando si vuole chiudere il programma
    while (matricola[0]!='0')
    {

        printf("Ciao! Benvenuto nella nostra biblioteca!\nPuoi scrivermi la tua matricola, per favore?\nRicorda che dovra' essere "
               "lunga al massimo 9 caratteri, con primo carattere diverso da 0 e diversa da xxxxxxxxx.\nPer uscire dal"
               " programma scrivi 0 e premi invio.\nGrazie!\t");
        scanf("%9[^\n]", matricola);
        while ((matricola[0]=='0' && matricola[1]!='\0')|| !strcmp(matricola, "xxxxxxxxx"))
        {
            while (getchar()!='\n');
            printf("\nMi dispiace, scelta non valida. Riprova.\t");
            scanf("%9[^\n]", matricola);

        }
        while (getchar()!='\n'); //pulisco buffer

        if (matricola[0]!='0')
        {
            printf("\nPerfetto, la tua matricola e' %s\n", matricola);
            scelta_menu[0]='1';
            //questo while interno invece termina quando l'utente vuole uscire e permette di fargli fare piu' operazioni
            while (scelta_menu[0]!='0')
            {
                printf("\nCosa vuoi fare?\nScrivi 1 e  premi invio per prendere in prestito un libro\nScrivi 2 e  premi invio per"
                       " restituire un libro (preso in prestito precedentemente)\nScrivi 0 e premi invio per cedere la postazione ad"
                       " un altro studente o per uscire dal programma\n\t(tornerai nel menu iniziale, dal quale potrai uscire subito). Scelta:\t");
                scanf("%2s", scelta_menu);
                //la funzione seguente impedisce all'utente di fare inserimenti non validi o addirittura dannosi per il programma
                //non ci sarebbero errori qualora scrivesse una stringa e neanche un intero valido ma seguito da uno spazio e poi altro
                while ((scelta_menu[0]!='1' && scelta_menu[0]!='2' && scelta_menu[0]!='0') || scelta_menu[1]!='\0')
                {
                    while (getchar()!='\n');
                    printf("\nMi dispiace, scelta non valida. Riprova.\t");
                    scanf("%2s",scelta_menu );

                }
                while (getchar()!='\n'); //pulisco buffer in ingresso (stdin)

                switch (atoi(scelta_menu)) //uso la funzione atoi per convertire la stringa in intero, per poter essere usata nello switch
                {
                case 1:
                    top_richieste=chiedi_prestito(top, matricola, top_richieste);
                    break;
                case 2:
                    restituisci_libro(top, matricola);
                    break;
                case 0:
                    printf("\nArrivederci Studente %s!\n\n-------------------------------------------------------------\n\n", matricola);
                    break;
                }
            }
        }
        //il controllo per l'eventuale risoluzione di richieste pendenti deve essere fatto a ogni cambio di utente in modo da garantire
        //l'esaudimento di una richiesta a un eventuale studente in attesa prima possibile; funzione in prestito.c
        top_richieste=controlla_richieste_sospese(top, top_richieste);
    }


    printf("\nArrivederci!\n\n");
    //update del file di deposito con la situazione all'uscita del programma
    aggiorna_deposito(top);
    //salvataggio delle richieste pendenti su un nuovo file, in modo da poterle riprendere quando il programma riparte
    salva_richieste_su_file(top_richieste);
    //dealloca lista deposito
    dealloca(top);
    //dealloca lista richieste
    dealloca_richieste(top_richieste);
    chiudi_finestra();

    return 0;
}
