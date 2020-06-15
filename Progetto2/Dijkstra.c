#include "Dijkstra.h"


struct MinHeapNode* newMinHeapNode(int v, int dist)
{
    struct MinHeapNode* minHeapNode =
        (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}

struct MinHeap* createMinHeap(int capacity)
{
    struct MinHeap* minHeap =
        (struct MinHeap*) malloc(sizeof(struct MinHeap));
    minHeap->pos = (int *)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array =
        (struct MinHeapNode**) malloc(capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}


// Una funzione per scambiare due nodi dell'heap minimo. Necessario per min heapify
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// Una funzione standard per heapify in un determinato idx
// Questa funzione aggiorna anche la posizione dei nodi quando vengono scambiati.
// La posizione è necessaria per la decreasKey ()
void minHeapify(struct MinHeap* minHeap, int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < minHeap->size &&
            minHeap->array[left]->dist < minHeap->array[smallest]->dist )
        smallest = left;

    if (right < minHeap->size &&
            minHeap->array[right]->dist < minHeap->array[smallest]->dist )
        smallest = right;

    if (smallest != idx)
    {

        // I nodi da scambiare in heap min
        struct MinHeapNode *smallestNode = minHeap->array[smallest];
        struct MinHeapNode *idxNode = minHeap->array[idx];

        // Scambia posizioni
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;

        // Scambia nodi
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}


// funzione per verificare se il dato minHeap è ampty o meno
int isEmpty(struct MinHeap* minHeap)
{
    return minHeap->size == 0;
}


// Funzione standard per estrarre il nodo minimo dall'heap
struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
    if (isEmpty(minHeap))
        return NULL;


// Archivia il nodo principale
    struct MinHeapNode* root = minHeap->array[0];

    // Sostituisce il nodo principale con l'ultimo nodo
    struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

    // Aggiorna la posizione dell'ultimo nodo
    minHeap->pos[root->v] = minHeap->size-1;
    minHeap->pos[lastNode->v] = 0;

// Riduce le dimensioni dell'heap e radice heapify
    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}

// Funzione per diminuire il valore dist di un dato vertice v.
// Questa funzione usa pos [] dell'heap min per ottenere l'indice corrente del nodo nell'heap minimo
void decreaseKey(struct MinHeap* minHeap, int u, int v, int dist)
{
// Ottieni l'indice di v nell'array heap
    int i = minHeap->pos[v];

    // Ottieni il nodo e aggiorna il suo valore dist
    minHeap->array[i]->dist = dist;

    minHeap->array[i]->precedente=u;

    // Viaggia verso l'alto mentre l'albero completo non è epificato.
    // Questo è un loop O (Logn)
    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist)
    {
        // Scambia questo nodo con il suo genitore
        minHeap->pos[minHeap->array[i]->v] = (i-1)/2;
        minHeap->pos[minHeap->array[(i-1)/2]->v] = i;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);

        // passa all'indice principale
        i = (i - 1) / 2;
    }
}

// verificare se un dato vertice
// 'v' è in heap min oppure no
int isInMinHeap(struct MinHeap *minHeap, int v)
{
    if (minHeap->pos[v] < minHeap->size)
        return 1;
    return 0;
}

// stampa la soluzione
void printArr(int dist[], int n)
{
    printf("Distanza vertice dalla partenza\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}

//estrae la posizione del nodo (e quindi l' id del relativo luogo) a minor distanza da quello di partenza
int estrai_destinazione_con_distanza_minore (int dist[], int nodes_count)
{

    int posizione_distanza_minore=0, i;
    int min;

    if (dist[0]!=0) min=dist[0];
    else min=dist[1];

    for (i=0; i<nodes_count; i++)
    {

        if (dist[i]<min && dist[i]!=0)
        {
            min=dist[i];
            posizione_distanza_minore=i;
        }
    }



    return posizione_distanza_minore;

}

//questa funzione va a prendere la distanza (sia essa calcolata sulla durata o sul costo del volo, il peso scelto insomma)
//dal nodo di partenza src della funzione dijkstra al nodo destinazione desiderato
int estrai_distanza_minore_per_destinazione (int dist[], int destinazione, int nodes_count)
{

    int i=0;

    while (i<nodes_count && destinazione!=i)
    {
        i++;
    }

    return dist[i];

}

// La funzione principale che calcola le distanze dei percorsi più brevi da src a tutti i vertici
int dijkstra_costo(Graph G, int src, int destinazione, int scelta_output, int stampa_percorso)
{

    int nodes_count = G->nodes_count;// Ottieni il numero di vertici nel grafico
    int dist[nodes_count];     // valori dist usati per selezionare il bordo di peso minimo
    struct MinHeapNode salva_percorso[nodes_count];
    int a=0;

    struct MinHeap* minHeap = createMinHeap(nodes_count);

    // Inizializza heap minimo con tutti i vertici. valore dist di tutti i vertici
    for (int v = 0; v < nodes_count; ++v)
    {
        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }

    // Rende il valore dist del vertice src come 0 in modo che venga estratto per primo
    minHeap->array[src] = newMinHeapNode(src, dist[src]);
    minHeap->pos[src] = src;
    dist[src] = 0;
    decreaseKey(minHeap, -1, src, dist[src]);

    // Inizialmente la dimensione dell'heap minimo è uguale a V
    minHeap->size = nodes_count;

// Nel ciclo successivo, heap min contiene tutti i nodi la cui distanza più breve non è ancora stata finalizzata.
    while (!isEmpty(minHeap))
    {
        // Estrai il vertice con il valore della distanza minima
        struct MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v; // Memorizza il numero di vertice estratti
        salva_percorso[a].v=u;

        // Attraversa tutti i vertici adiacenti di u (l'estratto vertice) e aggiorna i loro valori di distanza
        struct TList  *pCrawl = G->adj[u];
        while (pCrawl != NULL)
        {
            int v = pCrawl->target;

            // Se la distanza più breve da v non è ancora stata finalizzata e la distanza da v attraverso u è inferiore alla sua distanza calcolata in precedenza
            if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX &&
                    pCrawl->costo_tratta + dist[u] < dist[v])
            {
                dist[v] = dist[u] + pCrawl->costo_tratta;

                // aggiorna anche il valore della distanza nell'heap minimo
                decreaseKey(minHeap, u, v, dist[v]);
            }
            pCrawl = pCrawl->next;
            salva_percorso[a].precedente=minHeapNode->precedente;
        }
        a++;
    }

    if (stampa_percorso)
    {
        int Percorso[nodes_count];
        int q=destinazione; // inserisci nodo di arrivo
        int arrivo=0;
        int i;
        Percorso[arrivo]=destinazione; // inserisci nodo di arrivo
        arrivo++;

        for(i=a; i>0 && q!=-1 && q!=src ; i--)
        {

            if(q == salva_percorso[i].v)
            {
                q=salva_percorso[i].precedente;

                Percorso[arrivo]=q;
                arrivo++;
                i=a;
            }
        }
        printf("\n\nQuesti sono i tuoi scali:\n\n");
        for(i=arrivo-1; i>0; i--)
        {
            printf(" |%d|-->",Percorso[i]);
        }
        printf(" |%d| ", Percorso[0]);
        printf("\n-----------\n");
    }

    if (scelta_output) return estrai_distanza_minore_per_destinazione (dist, destinazione, nodes_count); //restituisce il costo per quella dest
    else return estrai_destinazione_con_distanza_minore (dist, nodes_count);
}

int dijkstra_durata(Graph G, int src, int destinazione, int stampa_percorso)
{
    int nodes_count = G->nodes_count;// Ottieni il numero di vertici nel grafico
    int dist[nodes_count];     // valori dist usati per selezionare il bordo di peso minimo
    struct MinHeapNode salva_percorso[nodes_count];
    int a=0;

    struct MinHeap* minHeap = NULL;
    minHeap=createMinHeap(nodes_count);

    // Inizializza heap minimo con tutti i vertici. valore dist di tutti i vertici
    for (int v = 0; v < nodes_count; ++v)
    {
        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }

    // Rende il valore dist del vertice src come 0 in modo che venga estratto per primo
    minHeap->array[src] = newMinHeapNode(src, dist[src]);
    minHeap->pos[src] = src;
    dist[src] = 0;
    decreaseKey(minHeap, -1, src, dist[src]);

    // Inizialmente la dimensione dell'heap minimo è uguale a V
    minHeap->size = nodes_count;

    // Nel ciclo successivo, heap min contiene tutti i nodi la cui distanza più breve non è ancora stata finalizzata.
    while (!isEmpty(minHeap))
    {
        // Estrai il vertice con il valore della distanza minima
        struct MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v; // Store the extracted vertex number
        salva_percorso[a].v=u;

        // Attraversa tutti i vertici adiacenti di u (l'estratto vertice) e aggiorna i loro valori di distanza
        struct TList  *pCrawl = G->adj[u];
        while (pCrawl != NULL)
        {
            int v = pCrawl->target;

            // Se la distanza più breve da v non è ancora stata finalizzata e la distanza da v attraverso u è inferiore alla sua distanza calcolata in precedenza
            if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX &&
                    pCrawl->durata_tratta + dist[u] < dist[v])
            {
                dist[v] = dist[u] + pCrawl->durata_tratta;
                // aggiorna anche il valore della distanza nell'heap minimo
                decreaseKey(minHeap, u, v, dist[v]);
            }
            pCrawl = pCrawl->next;
            salva_percorso[a].precedente=minHeapNode->precedente;
        }
        a++;
    }

    if (stampa_percorso)
    {
        int Percorso[nodes_count];
        int q=destinazione; // inserisci nodo di arrivo
        int arrivo=0;
        int i;
        Percorso[arrivo]=destinazione; // inserisci nodo di arrivo
        arrivo++;

        for(i=a; i>0 && q!=-1 && q!=src ; i--)
        {

            if(q == salva_percorso[i].v)
            {
                q=salva_percorso[i].precedente;

                Percorso[arrivo]=q;
                arrivo++;
                i=a;
            }
        }
        printf("\n\nQuesti sono i tuoi scali:\n\n");
        for(i=arrivo-1; i>0; i--)
        {
            printf(" |%d|-->",Percorso[i]);
        }
        printf(" |%d| ", Percorso[0]);
        printf("\n-----------\n");
    }

    return estrai_distanza_minore_per_destinazione (dist, destinazione, nodes_count);
}

