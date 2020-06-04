#ifndef Graph_List_h
#define Graph_List_h

struct TList {
    int target; //identificativo univoco del nodo considerato
    int costo_tratta; //considerato come peso dell'arco
    int durata_tratta; //durata prevista del volo in minuti
    struct TList* next;
};

typedef struct TList* List;

// Inizializza un nuovo nodo
List initNodeList(int info, int costo_tratta, int durata_tratta);

/*
// Crea una lista random, per mod si
// puo' specificare il modulo utilizzato la funzione rand()
// La funzione ritorna sempre la testa della lista
List randomList(int index, int mod);
*/

// Aggiunge un nodo alla fine della lista
// controllandone l'esistenza
// La funzione ritorna sempre la testa della lista
List appendNodeList(List L, int target, int costo_tratta, int durata_tratta);

// Aggiunge un nodo in testa alla lista
// senza controllare l'esistenza
// La funzione ritorna sempre la testa della lista
List addNodeList(List L, int target, int costo_tratta, int durata_tratta);

// Rimuove solo un occorrenza di un nodo con il target specificato
// dalla lista
// La funzione ritorna sempre la testa della lista
List removeNodeList(List L, int target);

// Dealloca la lista interamente
void freeList(List L);

// Stampa la lista
void printList(List L);
#endif
