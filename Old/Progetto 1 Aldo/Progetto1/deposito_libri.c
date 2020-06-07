#include "deposito_libri.h"
#include "prestito.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//la funzione che segue serve semplicemente a non far chiudere bruscamente la finestra
//ho deciso di implementarla per non usare system("pause") essendo una chiamata al sistema operativo non necessaria e tra l'altro usabile solo su Windows
void chiudi_finestra ()
{
    //while(getchar()!='\n') {} //per pulire un eventualmente non vuoto buffer stdin
    printf("Premi invio per chiudere la finestra. Grazie!\t");
    getchar();

}

//questa funzione e' di test, in quella corretta non si possono vedere le matricole per privacy
void stampa_lista(Node *top)
{

    Node *tmp=top;

    printf("\n\nAutore/i - Titolo \t\t\t\tMatricola dello studente che ha il libro \tNumero_copia \n\n");
    while (tmp!=NULL)
    {
        printf("%-78s \t%-10s \t%10d\n", tmp->nome_libro, tmp->matricola_studenteCheHaIlLibro, tmp->numero_copia);
        tmp=tmp->next;
    }
    printf("\n\n" );

}

//questa funzione e' quella che andra' a sfruttare l'utente per la visualizzazione, non si possono vedere le matricole per privacy
void stampa_lista_privacy(Node *top)
{

    Node *tmp=top;

    printf("\n\nDisponibile?\t Numero copia del libro\t\tAutore1_AutoreN-Titolo\n\n");
    while (tmp!=NULL)
    {
        printf("%7s\t\t~\t %d\t~\t~\t%s\n", (strcmp(tmp->matricola_studenteCheHaIlLibro, "xxxxxxxxx") ? "no" : "si"), tmp->numero_copia, tmp->nome_libro);
        tmp=tmp->next;
    }
    printf("\n\n" );

}


void dealloca (Node *top)
{

    if (top!=NULL)
    {
        dealloca (top->next);
        free(top);
        top=NULL;
    }
}

void dealloca_richieste (Node_Sospese *top)
{

    if (top!=NULL)
    {
        dealloca_richieste (top->next);
        free(top);
        top=NULL;
    }
}

Node *nuovo_nodo(char nome_libro_tmp[], int numero_copia_tmp, char matricola_studenteCheHaIlLibro_tmp[])
{

    Node *tmp=(Node*)malloc(sizeof(Node));

    strcpy(tmp->nome_libro, nome_libro_tmp);
    strcpy(tmp->matricola_studenteCheHaIlLibro, matricola_studenteCheHaIlLibro_tmp);
    tmp->numero_copia=numero_copia_tmp;
    tmp->next=NULL;

    return tmp;
}

Node *ins_coda (Node *top, char nome_libro_tmp[], int numero_copia_tmp, char matricola_studenteCheHaIlLibro_tmp[])
{

    Node *tmp=top, *new=nuovo_nodo(nome_libro_tmp, numero_copia_tmp, matricola_studenteCheHaIlLibro_tmp);

    if (top==NULL)
    {
        top=new;
        new->next=NULL;
    }
    else
    {
        while (tmp->next!=NULL)
        {
            tmp=tmp->next;
        }
        tmp->next=new;
        new->next=NULL;
    }

    return top;
}

//questa funzione controlla che la riga acquisita dall' fgets sia valida, ovvero che contenga i tre campi che la funzione chiamante si aspetta;
//evita inoltre che il programma vada in crash nel caso di file con dati corrotti o comunque sporchi
int riga_valida (char riga[])
{

    int valida=0;
    char *prima_occorrenza;

    if (riga[0]!='\n' && riga[0]!='\0' && riga[0]!='\r' && (prima_occorrenza=strstr(riga, "|"))!=NULL)
    {
        if (strstr(prima_occorrenza, "|")) valida=1;
    }

    return valida;

}

Node *crea_lista (Node*top, FILE *ptr)
{

    char *nome_libro_tmp, *matricola_studenteCheHaIlLibro_tmp;
    int numero_copia_tmp;
    char riga[MATR+DIM+3];

    while (fgets(riga, MATR+DIM+3, ptr))
    {
        if (riga_valida(riga))
        {
            nome_libro_tmp=strtok(riga, "|");
            numero_copia_tmp=atoi(strtok(NULL, "|"));
            matricola_studenteCheHaIlLibro_tmp=strtok(NULL, "\n");
            top=ins_coda(top, nome_libro_tmp, numero_copia_tmp, matricola_studenteCheHaIlLibro_tmp);
        }
    }

    return top;
}

//questa funzione viene chiamata all'inizio per caricare in memoria il database dei libri per consentire maggior velocita'
//nel caso di un ipotetico scenario reale con un database molto ampio
Node *popola_con_libri_default (Node *top)
{
    FILE *ptr=fopen("deposito_iniziale.txt","r");

    if (ptr==NULL)
    {
        perror("");
        printf("Mi dispiace, impossibile accedere all'archivio in questo momento. Contattaci per favore.\n");
        chiudi_finestra();
        exit (-1);
    }
    else
    {
        //creo lista linkata semplice inserendo in coda, popolandola in seguito a lettura dei dati da file
        top=crea_lista(top, ptr);
    }
    fclose(ptr);

    return top;

}

//la funzione aggiorna il database locale dei libri all'uscita del programma
void aggiorna_deposito (Node *top)
{

    Node *tmp=top;
    FILE *ptr;


    if ((ptr=fopen("deposito_iniziale.txt", "w"))==NULL)
    {
        perror("");
        printf("Ci dispiace ma purtroppo si e' verificato un errore con il salvataggio, contattaci per favore.\n");
        chiudi_finestra();
        exit(-1);
    }
    else
    {
        while (tmp!=NULL)
        {
            fprintf(ptr, "%s|%d|%s\n", tmp->nome_libro, tmp->numero_copia, tmp->matricola_studenteCheHaIlLibro);
            tmp=tmp->next;
        }
    }
    fclose(ptr);
}

//la funzione aggiorna il database locale delle richieste sospese all'uscita del programma
void salva_richieste_su_file (Node_Sospese *top)
{

    Node_Sospese *tmp=top;
    FILE *ptr;

    if ((ptr=fopen("storico_richieste.txt", "w"))==NULL)
    {
        perror("");
        printf("Ci dispiace ma purtroppo si e' verificato un errore con il salvataggio delle richieste, contattaci per favore.\n");
        chiudi_finestra();
        exit(-1);
    }
    else
    {
        while (tmp!=NULL)
        {
            fprintf(ptr, "%s|%s\n", tmp->libro, tmp->matricola_richiedente);
            tmp=tmp->next;
        }
    }
    fclose(ptr);
}

//questa funzione viene chiamata all'inizio per caricare in memoria il database delle richieste sospese per consentire maggior velocita'
//nel caso di un ipotetico scenario reale con un database molto ampio
Node_Sospese *carica_richieste_pregresse(Node_Sospese *top_richieste)
{

    FILE *ptr;
    //char titolo_tmp[DIM], matricola_richiedente_tmp[MATR];
    char *titolo_tmp, *matricola_richiedente_tmp,riga[MATR+DIM+4];


    if ((ptr=fopen("storico_richieste.txt", "r"))==NULL)
    {
        perror("");
        printf("Mi dispiace, impossibile accedere allo storico richieste in questo momento. Contattaci per favore.\n");
        chiudi_finestra();
        exit(-1);
    }
    else
    {
        //creo lista linkata semplice inserendo in coda, popolandola in seguito a lettura dei dati da file
        while (fgets(riga, MATR+DIM+1, ptr))
        {
            if (riga[0]!='\n' && riga[0]!='\0' && riga[0]!='\r' && strstr(riga, "|")!=NULL)
            {
                titolo_tmp=strtok(riga, "|");
                matricola_richiedente_tmp=strtok(NULL, "\n");
                //la funzione ins_code_richiesta e' definita nel file prestito.c
                top_richieste=ins_coda_richiesta(top_richieste, titolo_tmp, matricola_richiedente_tmp);
            }
        }

    }
    fclose(ptr);

    return top_richieste;
}


