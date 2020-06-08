#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include "Graph.h"
#define GRANDEZZA_GRAFO 20
#define MAXLEN_LUOGO 30 //lunghezza massima del nome di un luogo nel quale si trova un aeroporto

int empty_graph(Graph G)
{
    return G==NULL;
}

int numeroVertici(Graph g)
{

    int ret;

    if(!empty_graph(g))
    {
        ret = g->nodes_count;
    }
    else
    {
        ret = 0;
    }

    return ret;
}



int numeroArchi(Graph g)
{

    int ret = 0;
    int i;
    List curr;

    if(!empty_graph(g))
    {
        for(i = 0; i < g->nodes_count; i++) //per tutte le liste di adiacenza del vettore
        {

            curr = g->adj[i];//partendo dall'inizio

            while(curr != NULL) //scorre la lista e conta gli elementi, potenzialmente 0
            {
                ret = ret + 1;
                curr = curr->next;
            }
        }
    }
    return ret;
}

int esisteArco(Graph g, int partenza, int arrivo)
{

    int ret = 0;
    List curr;

    if(!empty_graph(g))
    {
        if(partenza <= g->nodes_count && arrivo <= g->nodes_count)
        {

            curr = g->adj[partenza];
            while(curr != NULL && ret == 0)
            {

                if(curr->target == arrivo)
                {
                    ret = 1;
                }
                curr = curr->next;
            }
        }
        else
        {
            printf("ERRORE in esisteArco: vertice di partenza o arrivo fuori dal range\n");
        }
    }
    else
    {
        printf("ERRORE in esisteArco: grafo vuoto\n");
    }

    return ret;
}



int costoArco(Graph g, int partenza, int arrivo)
{

    List curr = NULL;
    int ret = 0;

    if(!empty_graph(g))
    {
        if(esisteArco(g, partenza, arrivo)) //forse esisteArco dovrebbe anche in qualche modo ritornare un puntatore all'arco se esiste?
        {

            curr = g->adj[partenza];
            while(curr->target != arrivo)
            {
                curr = curr->next;
            }
            ret = curr->costo_tratta;
        }
        else
        {
            printf("ERRORE in pesoArco: l'arco non esiste\n");
        }
    }
    else
    {
        printf("ERRORE in pesoArco: grafo vuoto\n");
    }

    return ret;
}

int esisteVertice(Graph g, int v)
{
    return v < g->nodes_count;
}



/////////////////////////////////////////////////////////////////////////////

//crea il Graph, della dimensione specificata, e inizializza i suoi nodi allocandone anche la memoria per ognuno
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


void removeEdge(Graph G, int source, int target) //rimuove un arco
{
    assert(G != NULL);
    assert(source < G->nodes_count);
    assert(target < G->nodes_count);
    if (source != target)
    {
        G->adj[source] = removeNodeList(G->adj[source], target);
    }
}


void addNode(Graph G) //QUESTA FUNZIONE ALLOCA SOLO MEMORIA PER IL NUOVO NODO
{
    if (G != NULL)
    {
        G->adj = realloc(G->adj, (G->nodes_count+1) * sizeof(List));
        G->nodes_count ++;
        G->adj[G->nodes_count] = NULL;
    }
}

void removeNode(Graph G, int node_to_remove, Nomi_Luoghi *NM) //rimuove un vertice o nodo, un nuovo luogo in pratica
{
    if (G != NULL)
    {
        int i = 0;
        int x = 0;
        List *tmp = G->adj;
        G->adj = calloc(G->nodes_count, sizeof(List));
        for (i = 0; i < G->nodes_count; i++) //i<=GNODES c'era prima boh controlla
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

        /*int target=G->adj[0]->target;
        int costo_tratta=G->adj[0]->costo_tratta;
        int durata_tratta=G->adj[0]->durata_tratta;

        free(*tmp);

        G->adj[0]->target=target;
        G->adj[0]->costo_tratta=costo_tratta;
        G->adj[0]->durata_tratta=durata_tratta;*/
        free(tmp);
        G->nodes_count -= 1;

        //il codice che segue serve ad aggiornare la lista delle corrispondenze id luoghi e nome del luogo
        // *NM=checkListRemoval_perNomiLuoghi(*NM, node_to_remove);
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

//////////////////////////////////////////////////////////////////////////////////////////

Nomi_Luoghi checkListRemoval_perNomiLuoghi(Nomi_Luoghi L, int node_to_remove)
{
    if (L != NULL)
    {
        L->next = checkListRemoval_perNomiLuoghi(L->next, node_to_remove);
        if (L->id == node_to_remove)
        {
            Nomi_Luoghi tmp = L->next;
            free(L);
            return tmp;
        }
        else if (L->id > node_to_remove)
        {
            L->id -= 1;
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
        printf("Nodo %d\t-> %-25s Persone che gia' ci sono andate -> %d\n", NM->id, NM->nome_luogo, NM->contatore_voli);
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
        nuovo->contatore_voli=0;
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

void cancellaListaNomi(Nomi_Luoghi L)
{
    if (L != NULL)
    {
        cancellaListaNomi(L->next);
        free(L);
    }
}

void scelta_visualizza_elenco (Nomi_Luoghi NM)
{

    char visualizza_elenco[2];

    printf("Vuoi visualizzare la lista degli aeroporti disponibili?\nPremi 1 e poi invio per visualizzare, altrimenti 0 e invio:\t");
    scanf("%2s", visualizza_elenco);
    //la funzione seguente impedisce all'utente di fare inserimenti non validi o addirittura dannosi per il programma
    //non ci sarebbero errori qualora scrivesse una stringa e neanche un intero valido ma seguito da uno spazio e poi altro
    while ((visualizza_elenco[0]!='1' && visualizza_elenco[0]!='0') || visualizza_elenco[1]!='\0')
    {
        while (getchar()!='\n');
        printf("\nMi dispiace, scelta non valida. Riprova.\t");
        scanf("%2s",visualizza_elenco );

    }
    while (getchar()!='\n'); //pulisco buffer in ingresso (stdin)
    if (atoi(visualizza_elenco)) stampa_lista_nomi(NM);
    printf("\n\n");
}

int calcola_id (Nomi_Luoghi NM)
{

    int count=0;

    while (NM!=NULL)
    {
        NM=NM->next;
        count++;
    }

    return count;
}

void aggiungi_aeroporto(Graph G, Nomi_Luoghi *NM)
{

    char nuovo_luogo[MAXLEN_LUOGO];

    printf("Inserisci il nome del nuovo luogo:\t");
    scanf("%29[^\n]", nuovo_luogo);
    //pulisco buffer in ingresso (stdin) per scongiurare comportamenti bizzarri del programma qualora l'utente inserisca input strani
    while (getchar()!='\n');
    //FACCIO LE TRE COSE DI SEGUITO SOLO SE LA STESSA CITTA NON SIA GIA PRESENTE, COMPLETARE
    addNode(G);
    aggiungi_nome_citta(*NM, calcola_id(*NM), nuovo_luogo);
    scelta_visualizza_elenco(*NM);
}

/*
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
*/


