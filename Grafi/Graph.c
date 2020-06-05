#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include "Graph.h"
#define GRANDEZZA_GRAFO 20
#define MAXLEN_LUOGO 30

//crea il grafo, della dimensione specificata, e inizializza i suoi nodi allocandone anche la memoria per ognuno
Graph initGraph(int nodes_count)
{
    Graph G = malloc(sizeof(struct TGraph));
    G->adj = calloc(nodes_count, sizeof(List));
    G->nodes_count = nodes_count;

    return G;
}

void freeGraph(Graph G)
{
    if (G != NULL)
    {
        if (G->nodes_count > 0)
        {
            int i = 0;
            for (i = 0; i < G->nodes_count; i++)
            {
                freeList(G->adj[i]);
            }
        }
        free(G);
    }
}

//funzione di test che stampa il grafo nel seguente formato: nodo in considerazione -> tutti i nodi ad esso collegati
void printGraph(Graph G)
{
    if (G != NULL)
    {
        int x = 0;
        for (x = 0; x < G->nodes_count; x++)
        {
            printf("Nodo %d\t-> ", x);
            printList(G->adj[x]);
            printf("\n");
        }
    }
}

//questa funzione va a creare un arco fra due nodi del grafo creati in precedenza con initGraph dopo aver stabilito quali siano
//i due nodi in questione, il peso(costo_tratta) dell'arco e la durata della tratta
void addEdge(Graph G, int source, int target, int costo_tratta, int durata_tratta)
{
    assert(G != NULL);
    assert(source < G->nodes_count);
    assert(target < G->nodes_count);
    if (source != target)
    {
        G->adj[source] = appendNodeList(G->adj[source], target, costo_tratta, durata_tratta);
    }
}


void removeEdge(Graph G, int source, int target)
{
    assert(G != NULL);
    assert(source < G->nodes_count);
    assert(target < G->nodes_count);
    if (source != target)
    {
        G->adj[source] = removeNodeList(G->adj[source], target);
    }
}


void addNode(Graph G)
{
    if (G != NULL)
    {
        G->adj = realloc(G->adj, (G->nodes_count+1) * sizeof(List));
        G->nodes_count += 1;
        G->adj[G->nodes_count] = NULL;
    }
}


void removeNode(Graph G, int node_to_remove)
{
    if (G != NULL)
    {
        int i = 0;
        int x = 0;
        List *tmp = G->adj;
        G->adj = calloc(G->nodes_count, sizeof(List));
        for (i = 0; i <= G->nodes_count; i++)
        {
            if (i != node_to_remove)
            {
                G->adj[x] = checkListRemoval(tmp[i], node_to_remove);
                x++;
            }
            else
            {
                freeList(G->adj[x]);
            }
        }
        free(*tmp);
        G->nodes_count -= 1;
    }
}


List checkListRemoval(List L, int node_to_remove)
{
    if (L != NULL)
    {
        L->next = checkListRemoval(L->next, node_to_remove);
        if (L->target == node_to_remove)
        {
            List tmp = L->next;
            free(L);
            return tmp;
        }
        else if (L->target > node_to_remove)
        {
            L->target -= 1;
        }
    }
    return L;
}

//questa funzione controlla che la riga acquisita dall' fgets sia valida, ovvero che contenga i tre campi che la funzione chiamante si aspetta;
//evita inoltre che il programma vada in crash nel caso di file con dati corrotti o comunque sporchi
int riga_valida (char riga[])
{

    int valida=0, contatore_occorrenze=0, contatore_stesso_carattere=0, len_sottostringa=0, len_stringa=0, i=0, j;
    char stringa_da_cercare[]="|"; //in questo caso e' solo un carattere

    if (riga[0]!='\n' && riga[0]!='\0' && riga[0]!='\r')
    {
        len_stringa=strlen(riga);
        len_sottostringa=strlen(stringa_da_cercare);
        while (i<len_stringa)
        {
            j=0;
            contatore_stesso_carattere=0;
            while (riga[i]==stringa_da_cercare[j])
            {
                contatore_stesso_carattere++;
                i++;
                j++;
            }
            if (contatore_stesso_carattere==len_sottostringa)
            {
                contatore_occorrenze++;
                contatore_stesso_carattere=0;
            }
            else i++;
        }
        if (contatore_occorrenze==5)
        {
            //perche', per costruzione, ogni riga del file di db deve avere 6 campi, quindi occorrono 5 separatori
            valida=1;
        }
    }

    return valida;

}

void stampa_lista_nomi(Nomi_Luoghi NM)
{
    if (NM != NULL)
    {
        printf("Nodo %d\t-> %s\n", NM->id, NM->nome_luogo);
        stampa_lista_nomi(NM->next);
    }
}

Nomi_Luoghi aggiungi_nome_citta (Nomi_Luoghi L, int id, char *luogo)
{
    Nomi_Luoghi nuovo=malloc(sizeof(struct nomi));
    //se il luogo che sto inserendo e' gia' presente nella lista non devo fare modifiche alla lista (per evitare ripetizioni)

    if (L != NULL)
    {
        if (strcmp(L->nome_luogo, luogo))
        {
            L->next = aggiungi_nome_citta(L->next, id, luogo);
        }
    }
    else
    {
        nuovo->id=id;
        nuovo->nome_luogo=(char*)malloc((strlen(luogo)+1)*sizeof(char));
        strcpy(nuovo->nome_luogo, luogo);
        nuovo->next=NULL;
        L = nuovo;
    }

    return L;
}

Graph leggi_file (Graph L, FILE *ptr, Nomi_Luoghi *NM)
{

    char *luogo_tmp;
    int id_luogo_tmp, id_partenza_tmp, id_destinazione_tmp, durata_tratta_tmp, costo_tratta_tmp;
    char riga[MAXLEN_LUOGO*2];
    L = initGraph(GRANDEZZA_GRAFO);

    while (fgets(riga, MAXLEN_LUOGO*2, ptr))
    {
        if (riga_valida(riga))
        {
            luogo_tmp=strtok(riga, "|");
            id_luogo_tmp=atoi(strtok(NULL, "|"));
            id_partenza_tmp=atoi(strtok(NULL, "|"));
            id_destinazione_tmp=atoi(strtok(NULL, "|"));
            durata_tratta_tmp=atoi(strtok(NULL, "|"));
            costo_tratta_tmp=atoi(strtok(NULL, "\n"));

            *NM = aggiungi_nome_citta(*NM, id_luogo_tmp, luogo_tmp);
            addEdge(L, id_partenza_tmp, id_destinazione_tmp, costo_tratta_tmp, durata_tratta_tmp);
        }
    }

    return L;
}

//questa funzione viene chiamata all'inizio per caricare in memoria il database del grafo per consentire maggior velocita'
//nel caso di un ipotetico scenario reale con un database molto ampio
Graph popola_grafo_file (Graph L, Nomi_Luoghi *NM)
{
    FILE *ptr=fopen("db_grafo.txt","r");

    if (ptr==NULL)
    {
        perror("");
        printf("Mi dispiace, impossibile accedere all'archivio in questo momento. Contattaci per favore.\n");
        //chiudi_finestra();
        exit (-1);
    }
    else
    {
        L=leggi_file(L, ptr, NM);
    }
    fclose(ptr);

    return L;

}

//la funzione aggiorna il database locale del grafo all'uscita del programma
void aggiorna_grafo (Graph L)
{

    Node *tmp=top;
    FILE *ptr;


    if ((ptr=fopen("db_grafo.txt", "w"))==NULL)
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
            fprintf(ptr, "%s|%d|%d|%d|%d|%d\n", tmp->nome_libro, tmp->numero_copia, tmp->matricola_studenteCheHaIlLibro);
            tmp=tmp->next;
        }
    }
    fclose(ptr);
}



