#include "prestito.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


void stampa_lista_richieste(Node_Sospese *top) //e' una funzione di test
{

    Node_Sospese *tmp=top;

    if (tmp!=NULL)
    {
        printf("\n\nMatricola dello studente che richiede il libro\t\t\t\tAutore/i - Titolo\n\n");
        while (tmp!=NULL)
        {
            printf("%10s \t%78s\n", tmp->matricola_richiedente, tmp->libro);
            tmp=tmp->next;
        }
        printf("\n\n" );
    }
    else printf("Non ci sono richieste sospese.\n\n");
}


Node_Sospese *nuovo_nodo_richiesta(char libro[], char matricola_richiedente[])
{

    Node_Sospese *tmp=(Node_Sospese*)malloc(sizeof(Node_Sospese));

    strcpy(tmp->libro, libro);
    strcpy(tmp->matricola_richiedente, matricola_richiedente);
    tmp->next=NULL;
    tmp->prev=NULL;

    return tmp;
}

Node_Sospese *ins_coda_richiesta (Node_Sospese *top, char libro[], char matricola_richiedente[])
{

    Node_Sospese *tmp=top, *new=nuovo_nodo_richiesta(libro, matricola_richiedente);

    if (top==NULL)
    {
        top=new;
        new->next=NULL;
        new->prev=NULL;
    }
    else
    {
        while (tmp->next!=NULL)
        {
            tmp=tmp->next;
        }
        tmp->next=new;
        new->next=NULL;
        new->prev=tmp;
    }

    return top;
}

//questa funzione si occupa di creare effettivamente la richiesta e inserirla nella lista delle richieste, in coda.
//e' chiamata in chiedi_prestito se un libro non e' disponibile
Node_Sospese *crea_richiesta(char titolo[], char matricola[], Node_Sospese *top_richieste)
{

    top_richieste=ins_coda_richiesta(top_richieste, titolo, matricola);

    return top_richieste;
}

//funzione che ritorna un valore positivo qualora sia disponibile un'altra copia del libro che si sta richiedendo
int disponibile_altra_copia (Node *top, char titolo[])
{
    Node *tmp=top;
    int corrispondenza=0;

    while (tmp!=NULL && !corrispondenza)
    {
        if (!strcmp(tmp->matricola_studenteCheHaIlLibro, "xxxxxxxxx") && !strcmp(tmp->nome_libro, titolo)) corrispondenza=1;
        tmp=tmp->next;
    }

    return corrispondenza;
}

//funzione che ritorna un valore positivo se un'altra copia del libro sia gia' in possesso della stessa persona con la matricola"
// che lo sta richiedendo
int prestata_altra_copia (Node *top, char matricola[], char titolo[])
{
    Node *tmp=top;
    int corrispondenza=0;

    while (tmp!=NULL && !corrispondenza)
    {
        if (!strcmp(tmp->matricola_studenteCheHaIlLibro, matricola) && !strcmp(tmp->nome_libro, titolo)) corrispondenza=1;
        tmp=tmp->next;
    }

    return corrispondenza;
}

//funzione che ritorna un valore positivo se una stessa persona abbia gia' precedentemente fatto richiesta per il libro che sta chiedendo
int controlla_richiesta_gia_creata (Node_Sospese *top, char matricola[], char titolo[])
{
    Node_Sospese *tmp=top;
    int corrispondenza=0;

    while (tmp!=NULL && !corrispondenza)
    {
        if (!strcmp(tmp->matricola_richiedente, matricola) && !strcmp(tmp->libro, titolo)) corrispondenza=1;
        tmp=tmp->next;
    }

    return corrispondenza;
}

//questa e' la vera funzione operativa chiamata da chiedi_prestito
int confronta_titoli_prestito (char titolo_da_cercare[], Node *top, char matricola[], Node_Sospese *top_richieste)
{
    Node *tmp=top;
    int risultato_ricerca=0; //contiene il valore di ritorno della funzione, utile per controlli e design pulito, evitando return nel mezzo


    while (tmp!=NULL && risultato_ricerca<=1)
    {

        if (!strcmp(titolo_da_cercare, tmp->nome_libro)) //inizio col confrontare i titoli
        {
            //se hanno stesso titolo vado a vedere se non sia gia' stato preso da qualcuno o dallo stesso studente; se si verifica
            //quanto prima, ho successo,altrimenti memorizzo la richiesta
            if (!strcmp(tmp->matricola_studenteCheHaIlLibro, matricola))
            {
                risultato_ricerca=2;
            }
            //questo che segue e' il caso di successo: la matricola registrata col libro e' quella di default, significa che il
            // libro sia disponibile
            else if(!strcmp(tmp->matricola_studenteCheHaIlLibro, "xxxxxxxxx") )
            {
                //controllo, prima della registrazione effettiva, che l'utente non disponga gia' del libro ma in una diversa copia della prima
                // il controllo avviene dal nodo ("oggetto" relazione libro-studente a cui e' prestato) successivo (tmp->next) a quello che
                // in modo da evitare di partire dall'inizio della lista ogni volta; questo e' possibile e legittimo grazie all'adeguata
                //struttura del database (qui un semplice file di testo)
                if (!prestata_altra_copia(tmp->next, matricola, titolo_da_cercare))
                {
                    strcpy(tmp->matricola_studenteCheHaIlLibro, matricola);
                    risultato_ricerca=3;
                }
                else risultato_ricerca=2;
            }
            else
            {
                //caso in cui nessuna copia del volume sia al momento disponibile. controllo prima che non sia effettivamente
                //disponibile nessun'altra copia
                //snippet scritto in questo modo solo per motivi di leggibilita' del codice
                if (!disponibile_altra_copia(tmp->next, titolo_da_cercare))
                {
                    //controllo atto a impedire all'utente di fare una nuova richiesta per un libro che ha gia' richiesto
                    if (controlla_richiesta_gia_creata(top_richieste,matricola, titolo_da_cercare))
                    {
                        risultato_ricerca=4;
                    }
                    if (risultato_ricerca!=4)risultato_ricerca=1;
                }
            }
        }
        tmp=tmp->next;
    }


    return risultato_ricerca;
}

//questa funzione e' chiamata nel main, va a costruire l'interfaccia in base al ritorno della vera funzione operativa
Node_Sospese* chiedi_prestito(Node *top, char matricola[], Node_Sospese *top_richieste)
{
    char titolo_da_cercare[DIM];
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

    printf("\nQuale libro vuoi chiedere in prestito?\nSe ci hai ripensato, scrivi 0 e premi invio.\nRicorda di scrivere il titolo esatto!\t");
    //anche qui ho preferito usare scanf piuttosto che la piu' sicura fgets per ragioni di "pulizia": fgets memorizza il carattere \n e percio'
    //avrei dovuto aggiungere codice non bellissimo per rimuovere \n e sostituirlo con \0 affinche' i controlli successivi potessero funzionare.
    //La protezione, in ogni caso, e' ancora garantita dal while che pulisce il buffer in ingresso (stdin) per scongiurare comportamenti bizzarri
    //del programma qualora l'utente inserisca uno spazio e altri caratteri
    scanf("%100[^\n]", titolo_da_cercare);
    //pulisco buffer in ingresso (stdin) per scongiurare comportamenti bizzarri del programma qualora l'utente inserisca uno spazio e altri caratteri
    while (getchar()!='\n');

    //il controllo e' reso possibile e legittimo dall'adeguata struttura del database (qui un semplice file di testo)
    if (titolo_da_cercare[0]!='0')
    {
        switch (confronta_titoli_prestito(titolo_da_cercare, top, matricola, top_richieste)) //ho un'indea per un workaround un po' sporco
        {
        case 1:
            top_richieste=crea_richiesta(titolo_da_cercare, matricola, top_richieste);
            printf("\n\nPurtroppo il libro che cerchi non e' disponibile al momento.\nAbbiamo preso in carico la tua richiesta e "
                   "provvederemo prima possibile.\n\n");
            break;
        case 2:
            printf("\n\nHai gia' lo stesso libro, non puoi prenderlo due volte!\n\n");
            break;
        case 3:
            printf("\n\nEcco il tuo libro! Rispetta la scadenza e il libro stesso, a presto!\n\n");
            break;
        case 4:
            printf("\n\nAbbiamo gia' preso in carico la tua richiesta.\nPer favore pazienta, ti contatteremo appena il libro sara' "
                   "disponibile. Grazie.\n\n");
            break;
        default:
            printf("\n\nPurtroppo non abbiamo trovato il libro. Forse hai commesso un errore di battitura, riprova.\n\n");
            break;
        }
    }
    return top_richieste;
}

//funzione che si occupa della cancellazione del nodo contenente una richiesta soddisfatta dalla lista delle richieste
//aggiorna inoltre la flag testa_spostata nel caso in cui a essere rimosso sia il primo nodo
void cancella_nodo(Node_Sospese** top_richieste, Node_Sospese* tmp_richieste, int *testa_spostata)
{

    if (*top_richieste != NULL && tmp_richieste != NULL)
    {
        //se il nodo da rimovere e' la testa
        if (*top_richieste == tmp_richieste)
        {
            *top_richieste = tmp_richieste->next;
            *testa_spostata=1;
        }
        //cambiare il campo next solo se il nodo da cancellare NON e' l'ultimo nodo
        if (tmp_richieste->next != NULL)
            tmp_richieste->next->prev = tmp_richieste->prev;

        //cambiare il campo prev solo se il nodo da cancellare NON e' il primo nodo
        if (tmp_richieste->prev != NULL)
            tmp_richieste->prev->next = tmp_richieste->next;

        //Deallocazione della memoria occupata dal nodo
        free(tmp_richieste);
    }

}

//la funzione che segue si occupa di controllare e, nel caso sia possibile, esaudire le richieste salvate nella lista top_richieste
Node_Sospese *controlla_richieste_sospese (Node *top, Node_Sospese *top_richieste)
{
    Node_Sospese *tmp_richieste=top_richieste;
    Node *tmp=top;
    int richiesta_accolta=0;//questa flag, se vera, indica che una richiesta sia stata accolta
    int testa_spostata=0; //questa flag, se vera, indica che la richiesta accolta fosse la prima della lista;
                        //si dovra' operare di conseguenza nell'algoritmo

    if (tmp!=NULL)
    {
        //questo ciclo esterno riguarda la lista delle richieste e parte sempre dalla testa, affinche' venga garantito, nel caso
        //in cui due utenti diversi facciano richiesta per lo stesso libro, che il libro sia ottenuto prima da chi l'abbia effettivamente
        //richiesto per primo
        while (tmp_richieste!=NULL)
        {
            //scorro tutta la lista top, che contiene tutti i libri della biblioteca (una sorta di registro), fino a quando finisca o
            //se ho gia' accolto la richiesta
            while (tmp!=NULL && !richiesta_accolta)
            {
                //controllo che ci sia corrispondenza del titolo nelle due righe delle due tabelle (immaginando una rappresentazione
                //tabellare dei dati delle liste per semplicita' e se il libro sia adesso disponibile (xxxxxxxxx e' la matricola di default)
                if(!strcmp(tmp->nome_libro, tmp_richieste->libro) && !strcmp(tmp->matricola_studenteCheHaIlLibro, "xxxxxxxxx"))
                {
                    //associo la matricola del richiedente a quel libro, ora disponibile
                    strcpy(tmp->matricola_studenteCheHaIlLibro, tmp_richieste->matricola_richiedente);
                    //vado quindi a rimuovere il nodo e aggiornando la flag per non "rompere" il ciclo,
                    //avendo cambiato la lista tmp_richieste
                    cancella_nodo(&top_richieste, tmp_richieste, &testa_spostata);
                    richiesta_accolta=1;
                }
                tmp=tmp->next;
            }
            //se una richiesta e' stata accolta, devo "riavvolgere" il puntatore temporaneo alla lista "totale" dei libri
            if (richiesta_accolta)
            {
                tmp=top;
                richiesta_accolta=0; //altrimenti non potrei andare a scorrere la lista totale una volta passato a una nuova richiesta
            }
            //se, inoltre, la richiesta accolta fosse la prima della lista, non devo incrementare il puntatore perche'
            //altrimenti non andrei a considerare la (nuovo) prima richiesta
            if(testa_spostata) testa_spostata=0; //devo comunque resettare la flag
            else tmp_richieste=tmp_richieste->next;
        }
    }


    return top_richieste;
}





