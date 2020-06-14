#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "Graph.h"


Graph initGraph(int nodes_count) {
    Graph G = malloc(sizeof(struct TGraph));
    G->adj = calloc(nodes_count, sizeof(List));
    G->nodes_count = nodes_count;
    return G;
}


/*Funzione di generazione del nodo pozzo*/
Graph pozzo(int nodes, int target){
     Graph G=initGraph(nodes);

int i=0;
    for(i=0; i<nodes; i++){

        addEdge(G,i,target,rand() % 50);/*In questo for faccio coinvergere tutti i nodi al nodo pozzo*/

    }

for(i=0; i<nodes; i++){

        if (i==target)/*In questo ciclo for, aggiungo archi ad altri nodi casuali, tranne il target, che non avrà vertici uscenti*/
        continue;
        addEdge(G,i,rand() % nodes,rand() % 50);
    }

    return G;
}





Graph randomGraph(int nodes, int edges_min, int edges_max) {
    Graph G = initGraph(nodes);
    if (edges_max > nodes) {
        edges_max = nodes - 1;
    }
    int i = 0;
    int x = 0;
    int y = 0;
    for (i = 0; i < nodes; i++) {
        for (x = 0; x < edges_min; x ++) {
            addEdge(G, i, rand() % nodes, rand() % 50);
        }
        for (y = 0; y < rand() % (edges_max - edges_min); y++) {
            addEdge(G, i, rand() % nodes, rand() % 50);
        }
    }
    return G;
}


void freeGraph(Graph G) {
    if (G != NULL) {
        if (G->nodes_count > 0) {
            int i = 0;
            for (i = 0; i < G->nodes_count; i++) {
                freeList(G->adj[i]);
            }
        }
        free(G);
    }
}


void printGraph(Graph G) {
    if (G != NULL) {
        int x = 0;
        for (x = 0; x < G->nodes_count; x++) {
            printf("%d -> ", x);
            printList(G->adj[x]);//printa il suo adiacente
            printf("\n");
        }
    }
}

    void creaSottografo(Graph G ){

    int mezzi=(G->nodes_count/2)-2;//Il sottografo dovrà avere misure ridotte rispetto al grafo originale

    Graph B=initGraph(mezzi);
    int i;
    List  currEdge = NULL;

    for (i=mezzi/3; i<mezzi; i++){
        for( currEdge = G->adj[i] ; currEdge ; currEdge = currEdge->next)

        //Scorro il primo grafo ed aggiungo solo i vertici e archi che mi interessano
        // Non partendo dall'inizio.
        //Il peso è un multiplo dei pesi del primo grafo
        addEdge(B,i,currEdge->target, rand()%10 *currEdge->peso);


    }
    printf("\nTrovato il seguente sottografo H con pesi multipli di G\n");
    for (i=mezzi/3; i<mezzi; i++)

    {
        printf("%d ->", i);
        printList(B->adj[i]);
        printf("\n");
    }
    freeGraph(B);
    }

void addEdge(Graph G, int source, int target, int peso) {
    assert(G != NULL);
   // assert(source < G->nodes_count);
  //  assert(target < G->nodes_count);
    if (source != target) {
        G->adj[source] = appendNodeList(G->adj[source], target, peso);
    }
}


void removeEdge(Graph G, int source, int target) {
    assert(G != NULL);
    assert(source < G->nodes_count);
    assert(target < G->nodes_count);
    if (source != target) {
        G->adj[source] = removeNodeList(G->adj[source], target);
    }
}


void addNode(Graph G) {
    if (G != NULL) {
        G->adj = realloc(G->adj, (G->nodes_count+1) * sizeof(List));
        G->nodes_count += 1;
        G->adj[G->nodes_count] = NULL;
    }
}

void removeNode(Graph G, int node_to_remove) {
        if (G != NULL) {
        int i = 0;
        int x = 0;
        List *tmp = G->adj;
        G->adj = (List *)calloc(G->nodes_count-1, sizeof(List));
        for (i = 0; i < G->nodes_count; i++) {
            if (i != node_to_remove) {
                G->adj[x] = checkListRemoval(tmp[i], node_to_remove);
                x++;
            } else {
				//freeList(G->adj[x]);
                freeList(tmp[i]);
            }
        }
        free(tmp);
        G->nodes_count -= 1;
    }
}

List checkListRemoval(List L, int node_to_remove) {
    if (L != NULL) {
        L->next = checkListRemoval(L->next, node_to_remove);
        if (L->target == node_to_remove) {
            List tmp = L->next;
            free(L);
            return tmp;
        } else if (L->target > node_to_remove) {
            L->target -= 1;
        }
    }
    return L;
}

int *calcolaGradoUscente(Graph  G){
  int * gradiEntr = NULL;
  if(G){
    int i;
    gradiEntr = (int *)calloc(G->nodes_count,sizeof(int));
    List  currEdge = NULL;
    for(i=0 ; i < G->nodes_count ; i++ )
    for( currEdge = G->adj[i] ; currEdge ; currEdge = currEdge->next)
         gradiEntr[i]++;
  }
  return gradiEntr;
}

int *calcolaGradoEntrante(Graph G){
  int * gradiEntr = NULL;
  if(G){
    int i;
    gradiEntr = (int *)calloc(G->nodes_count,sizeof(int));
    List  currEdge = NULL;
    for(i=0 ; i < G->nodes_count ; i++ )
    for( currEdge = G->adj[i] ; currEdge ; currEdge = currEdge->next)
      gradiEntr[currEdge->target]++;
  }
  return gradiEntr;
}

void stampaGradi(Graph G, int * in, int * out){
  int i;
  if(G){
    for( i=0; i < G->nodes_count ; i++)
      printf("Nodo [%d] - Grado Entrante: %d - Grado uscente: %d\n",i,in[i],out[i]);
  }
}

// Funzione cerca nel grafo i vertici gia visitati
    int CheckGrafo(Graph G, int V, int visited[], int Stack[]){

        List head=NULL;

        if(visited[V]==0){

            visited[V]=1;
            Stack[V]=1;

            for(head=G->adj[V];head!=NULL; head=head->next){

                if(!visited[head->target] && CheckGrafo(G,head->target,visited,Stack))
                    return 1;
                else if (Stack[head->target])
                    return 1;


            }



        }

    return Stack[V]=0;
    return 0;


    }




// Itera nel grafo alla ricerca di nodi gia visitati, se torniamo su un nodo gia visitato indica un ciclo

    int TrovaCicli(Graph G) {

    int j;
    int visitato[MAX];
    int Stack[MAX];

    for (j=0;j<G->nodes_count;j++){

       visitato[j]=0;
       Stack[j]=0;
    }

    for (j=0; j<G->nodes_count;j++){
        if(CheckGrafo(G,j,visitato,Stack)){
            removeEdge(G,j,G->adj[j]->target);
            return 1;
        }
    }


    return 0;


    }

/*
void calcolaGradi(Graph G, int * inDeg, int * outDeg){
	int i = 0;
	List edge = NULL;
	for( ; i<G->nodes_count ; i++){
		for(edge = G->adj[i]; edge ; edge = edge->next){
			inDeg[edge->target]++;
			outDeg++;
		}
	}
}

*/


/*


void gestioneSottografo(Graph A, Graph B, int vertici , int edge_min, int edge_max){

    B=initGraph();





}
*/
