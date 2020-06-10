#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
#include "Graph.h"
#include "List.h"
/*Questa libreria contiene le funzioni principali da usare nello switch case del main*/

	void login();
	void menutratte(Graph G, Nomi_Luoghi NM);
    void rimuoviTratta(Graph G, Nomi_Luoghi NM);
    void aggiungiTratta(Graph G, Nomi_Luoghi NM);

#endif
