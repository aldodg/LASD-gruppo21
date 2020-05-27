#define DIM 100
#define MATR 10
#ifndef DEPOSITO H
#define DEPOSITO H


//semplice lista linkata
typedef struct libro{
    char nome_libro[DIM];
    int numero_copia;
    char matricola_studenteCheHaIlLibro[MATR];
    struct libro *next;
} Node;

//qui e' invece stata scelta una lista doppiamente linkata, per maggior velocita' di rimozione
typedef struct prestito {
    char libro[DIM];
    char matricola_richiedente[MATR];
    struct prestito *next;
    struct prestito *prev;
} Node_Sospese;


Node *popola_con_libri_default (Node*);
void stampa_lista(Node *);
void stampa_lista_privacy(Node *top);
void dealloca (Node *top);
void dealloca_richieste (Node_Sospese *top);
void aggiorna_deposito (Node *top);
void salva_richieste_su_file (Node_Sospese *top);
Node_Sospese *carica_richieste_pregresse(Node_Sospese *top_richieste);
void chiudi_finestra();



#endif

