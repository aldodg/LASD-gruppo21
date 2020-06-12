#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct MeteGettonate{
        char *partenza;
        char *destinazione;
        int cont;
        struct MeteGettonate *next;
		};
	typedef struct MeteGettonate *Gettonate;

/*INIZIALIZZA UN NUOVO NODO*/
Gettonate initList(char *,char *, int);

/* FUNZIONE CHE AGGIUNGE UN NODO ALLA FINE DELLA LISTA*/
Gettonate insertTailGettonate(Gettonate G, char * , char *, int);

/* FUNZIONE CHE AGGIUNGE UN NODO IN TESTA ALLA LISTA*/
Gettonate insertHeadGettonate(Gettonate G, char * ,char *, int);

/* STAMPA LA LISTA DELLE METE GETTONATE*/
void printMeteGettonate(Gettonate G);

/* DEALLOCA LA LISTA DELLE METE GETTONATE */
void freeListGettonate(Gettonate G);

