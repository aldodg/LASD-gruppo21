#ifndef CUSTOMERS_H_INCLUDED
#define CUSTOMERS_H_INCLUDED

/*Questa libreria contiene i metodi e la lista degli utenti che usano la app*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "prenotazione.h"

struct customer
{

    char * cognome;
    char * nome;
    char * user;
    char * password;
    Prenotati *prenotato;
    int sconto;
    struct customer *next;

};

typedef struct customer Customers;

char *username;
char *nome;
char *cognome;
char *pass;
char *pass2;
char *adpass;


void registra(Customers ** L, char *name, char * surname, char * username, char * password);//Funzione che riempie la lista delle registrazioni utente
int	UserGiaPresente(Customers *L, char *username);//Funzione booleana che controlla se uno username è gia presente
int controllaCredenziali(Customers *L,char * username, char * password);







#endif
