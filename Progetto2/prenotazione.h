#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct voliPrenotati{
		    char *partenza;
		    char *arrivo;
		    int costo;
		    struct voliPrenotati *next;
		};
	typedef struct voliPrenotati *Prenotati;


/*INIZIALIZZA UN NUOVO NODO*/
Prenotati initNode(char *,char *, int);

/* FUNZIONE CHE AGGIUNGE UN NODO ALLA FINE DELLA LISTA*/
Prenotati insertTail(Prenotati P, char * , char *, int );

/* FUNZIONE CHE AGGIUNGE UN NODO IN TESTA ALLA LISTA*/
Prenotati insertHead(Prenotati P, char * ,char *, int );

/* STAMPA LA LISTA DEI VOLI PRENOTATI*/
void printVoliPrenotati(Prenotati P);

/* DEALLOCA LA LISTA DEI VOLI PRENOTATI */
void freeVoliPrenotati(Prenotati P);
