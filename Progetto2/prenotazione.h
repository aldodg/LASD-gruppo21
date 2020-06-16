#ifndef PRENOT
#define PRENOT

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Graph.h"
#include "Dijkstra.h"
#define MAXLEN_NOMI 50

struct voliPrenotati
{
    int partenza;
    int destinazione;
    int costo_complessivo;
    int durata_complessiva;
    struct voliPrenotati *next;
};
typedef struct voliPrenotati *Prenotati;

struct customer
{

    char  cognome[MAXLEN_NOMI];
    char  nome[MAXLEN_NOMI];
    char  user[MAXLEN_NOMI];
    char  password[MAXLEN_NOMI];
    Prenotati elenco_prenotazioni;
    int punti;
    struct customer *next;

};

typedef struct customer *Customers;

char *username;
char *nome;
char *cognome;
char *pass;
char *pass2;
char *adpass;


void registra(Customers *L, char *name, char * surname, char * username, char * password);//Funzione che riempie la lista delle registrazioni utente
int	UserGiaPresente(Customers L, char *username);//Funzione booleana che controlla se uno username è gia presente
int controllaCredenziali(Customers L,char * username, char * password);



/* INIZIALIZZA UN NUOVO NODO*/
Prenotati initNode(int, int, int);

/* FUNZIONE CHE AGGIUNGE UN NODO ALLA FINE DELLA LISTA*/
Prenotati insertTail(Prenotati P, int, int, int);

/* FUNZIONE CHE AGGIUNGE UN NODO IN TESTA ALLA LISTA*/
Prenotati insertHead(Prenotati P, int, int, int, int);

/* STAMPA LA LISTA DEI VOLI PRENOTATI*/
void printVoliPrenotati(Prenotati P, int);

/* DEALLOCA LA LISTA DEI VOLI PRENOTATI */
void freeVoliPrenotati(Prenotati P);

void freeCustomers (Customers C);

//int metaGettonata();

void prenotaVolo(Graph G, Customers Cliente, char * username, Nomi_Luoghi NM);

void visualizza_prenotazioni_effettuate(char *username, Customers Utente);

void AggiornaContatore(Nomi_Luoghi NM, int id);

#endif

