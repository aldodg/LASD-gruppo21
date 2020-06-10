#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct voliPrenotati
{
    int partenza;
    int destinazione;
    int costo_complessivo;
    int durata_complessiva;
    struct voliPrenotati *next;
};
typedef struct voliPrenotati *Prenotati;


/* INIZIALIZZA UN NUOVO NODO*/
Prenotati initNode(char *,char *, int, int);

/* FUNZIONE CHE AGGIUNGE UN NODO ALLA FINE DELLA LISTA*/
Prenotati insertTail(Prenotati P, char *, char *, int, int);

/* FUNZIONE CHE AGGIUNGE UN NODO IN TESTA ALLA LISTA*/
Prenotati insertHead(Prenotati P, int,int, int, int);

/* STAMPA LA LISTA DEI VOLI PRENOTATI*/
void printVoliPrenotati(Prenotati P);

/* DEALLOCA LA LISTA DEI VOLI PRENOTATI */
void freeVoliPrenotati(Prenotati P);

//prenotaVolo();

//void visualizza_prenotazioni_effettuate(char *username, Customers Utenti_registrati);

