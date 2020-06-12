#ifndef PRENOT
#define PRENOT

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include "customers.h"
//#include "Graph.h"
#include "Dijkstra.h"

struct voliPrenotati
{
    int partenza;
    int destinazione;
    int peso;
    struct voliPrenotati *next;
};
typedef struct voliPrenotati *Prenotati;


/* INIZIALIZZA UN NUOVO NODO*/
Prenotati initNode(int, int, int);

/* FUNZIONE CHE AGGIUNGE UN NODO ALLA FINE DELLA LISTA*/
Prenotati insertTail(Prenotati P, int, int, int);

/* FUNZIONE CHE AGGIUNGE UN NODO IN TESTA ALLA LISTA*/
Prenotati insertHead(Prenotati P, int,int,  int);

/* STAMPA LA LISTA DEI VOLI PRENOTATI*/
void printVoliPrenotati(Prenotati P, int);

/* DEALLOCA LA LISTA DEI VOLI PRENOTATI */
void freeVoliPrenotati(Prenotati P);

void prenotaVolo(Graph G, Customers *Utenti, char *,Nomi_Luoghi NM);

void visualizza_prenotazioni_effettuate(char *username, Customers *Utente);

#endif

