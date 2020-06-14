#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "List.h"
#include "Graph.h"
#include "stdinutils.h"

int main()
{
    int choice;



    srand(time(NULL));

    Graph A;
    Graph B;

    int* entrante;
    int* uscente;


    do{
        printf("\n\n*-*-*-*-*-*-*-*-*-*-*-*-*-*Menu' Grafo*-*-*-*-*-*-*-*-*-*-*-*-*\n");
        printf("\n1 - Genera grafo casuale e calcola grado entrante e grado uscente\n");
        printf("2 - Generarare un grafo con nodo pozzo\n");
        printf("3 - Verifica esistenza sottografi con pesi multipli\n");
        printf("4 - Verifica esistenza di cicli in un grafo\n");
        printf("5 - Esci");
        printf("\n\n--------------------Digitare la scelta:-------------------------\n");
        choice=readint();

        switch(choice){

        case 1: {
        int num_Vertici;
        int min_archi;
        int max_archi;

        printf("\nInserire il numero dei vertici del grafo:\n");
        fflush(stdin);
        num_Vertici=readint();
        printf("\nInserire il numero minimo degli archi:\n");
        min_archi=readint();
        printf("\nInserire il  numero massimo degli archi:\n");
        max_archi=readint();
        if (min_archi > max_archi){
            printf("\nAttenzione! Il numero minimo di archi non puo' essere maggiore del numero massimo!\nReinserire i valori corretti.\n");
            fflush(stdin);
            printf("\nInserire il numero minimo degli archi:\n");
            min_archi=readint();
            printf("\nInserire il  numero massimo degli archi:\n");
            max_archi=readint();
        }
        printf("\nGenerazione automatica del grafo:\n");

        A=randomGraph(num_Vertici,min_archi,max_archi);

        printGraph(A);
        uscente=calcolaGradoUscente(A);
        entrante=calcolaGradoEntrante(A);


        printf("\nstampa il grado entrante ed uscente del grafo: \n");
        stampaGradi(A,entrante, uscente);
        freeGraph(A);


        break;
        }

        case 2:{
        int vertici;
        int nodo;
        printf("\nInserire il numero di vertici del grafo:\n");

        vertici=readint();
        printf("\nInserire il nodo scelto come pozzo\n");
        nodo=readint();

        if (vertici -1 < nodo){

            printf("\nErrore! Il nodo scelto non puo' essere presente nel grafo\n Inserire il valore corretto:\n");
             printf("\nInserire il nodo scelto come pozzo\n");
            nodo=readint();
        }

            printf("\nEsempio di grafo con nodo pozzo:\n");
            A= pozzo(vertici,nodo);
            printGraph(A);

            printf("\nRisoluzione del pozzo per il nodo %d: \n",nodo);

            addEdge(A,nodo,rand() % vertici,rand() % 50);
            printf("\n");
            printGraph(A);
            freeGraph(A);
            printf("\nPozzo risolto con successo!\n");


            break;
        }

        case 3: {

        printf("\nGenerazione di un grafo casuale e ricerca di un suo sottografo\n");
        int num_Vertici;
        int min_archi;
        int max_archi;

        printf("\nInserire il numero dei vertici del grafo:\n");
        fflush(stdin);
        num_Vertici=readint();
        printf("\nInserire il numero minimo degli archi:\n");
        min_archi=readint();
        printf("\nInserire il  numero massimo degli archi:\n");
        max_archi=readint();

        if (min_archi > max_archi){
            printf("\nAttenzione! Il numero minimo di archi non puo' essere maggiore del numero massimo!\nReinserire i valori corretti.\n");
            fflush(stdin);
            printf("\nInserire il numero minimo degli archi:\n");
            min_archi=readint();
            printf("\nInserire il  numero massimo degli archi:\n");
            max_archi=readint();
        }
        printf("\nGenerazione automatica del grafo G:\n");

        A=randomGraph(num_Vertici,min_archi,max_archi);

        printGraph(A);
        printf("\n\nRicerca di sottografi .........\n\n");

        creaSottografo(A);



//printGraph(B);
        break;
        }

        case 4: {
        int num_Vertici;
        int min_archi;
        int max_archi;

        printf("\nInserire il numero dei vertici del grafo:\n");
        fflush(stdin);
        num_Vertici=readint();
        printf("\nInserire il numero minimo degli archi:\n");
        min_archi=readint();
        printf("\nInserire il  numero massimo degli archi:\n");
        max_archi=readint();
        if (min_archi > max_archi){
            printf("\nAttenzione! Il numero minimo di archi non puo' essere maggiore del numero massimo!\nReinserire i valori corretti.\n");
            fflush(stdin);
            printf("\nInserire il numero minimo degli archi:\n");
            min_archi=readint();
            printf("\nInserire il  numero massimo degli archi:\n");
            max_archi=readint();
        }
        printf("\nGenerazione automatica del grafo:\n");

        A=randomGraph(num_Vertici,min_archi,max_archi);

        printGraph(A);

        printf("\nVerifica di cicli nel grafo...\n");

        if(!TrovaCicli(A)){

            printf("\nIl grafo e' aciclico\n");
        }else{
        printf("\nIl grafo possiede almeno un ciclo\n");}


        break;
        }
        case 5: {
            printf("\nUscita dal programma......");
            exit(0);

        }
        default:{

         printf("\nAttenzione!, Scelta non corretta, si prega di riprovare!\n\n");
         break;

        }

        }





    }while ( choice !=1  || choice !=2 || choice !=3 || choice !=4 || choice !=5);



    return 0;
}
