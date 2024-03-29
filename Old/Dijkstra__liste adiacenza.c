/*
**  dijkstra.c
**
**  Dato un grafo orientato, rappresentato con una
**  lista di adiacenza, e tale che ad ogni arco (u,v)
**  sia associato un peso non negativo w(u,v), per ogni
**  vertice v calcola il minimo cammino per raggiungere v
**  partendo dalla sorgente s. 
**  Il programma usa una coda di priorita' Q e un albero di cammini minimi
**
**  Pseudo-codifica dell'algoritmo:
**
**  Dijkstra(G, W, s)
**    per ogni v in V(G) ripeti:
**      d(v) = infinito
**      padre(v) = nil
**    end
**    d(s) = 0
**    Inserisci s in Q
**    fintanto che Q non e` vuoto ripeti:
**      sia u il l'elemento di Q con d(u) minima
**      estrai u da Q
**      per ogni vertice v adiacente a u ripeti:
**        se (d(v) == infinito) allora
**          d(v) = d(u) + w(u,v)
**          inserisci v in Q 
**          padre(v) = u
**        se (d(v) > d(u) + w(u,v)) allora
**          d(v) = d(u) + w(u,v)
**          decrementa la priorita' di v in Q 
**          padre(v) = u
**        end
**      end
**    end
**  END
**
*/


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INFINITO UINT_MAX
#define FLUSH while (getchar()!='\n')

typedef short boolean;

/*Implementazione Grafo con Liste di Adiacenza */
/*Nell'implementazione vengono considerati anche i pesi non negativi degli archi*/
/*Vengono riportate solo le funzioni per inserire vertici e archi */

#define EMPTYGRAPH NULL

typedef unsigned int vertex;
typedef unsigned int weight;

typedef struct node_edge{
  vertex v;
  weight w; /*e' il peso dell'arco che entra in v */
  struct node_edge *next; 
} node_edge;

typedef struct node_vertex{
  vertex v;
  boolean present; 
  node_edge *adj; /* lista di adiacenze del vertex v*/ 
} node_vertex;

typedef struct node_graph {
   unsigned int nv;   /* numero massimo di vertici del grafo */
   node_vertex *vect; /* vettore con le liste delle adiacenze */ 
} * graph ;

graph MakeNULLGraph(unsigned int dim) {
   graph G; 
   unsigned int i;

   if (dim>0) {
       G = (graph)malloc(sizeof(struct node_graph));
       if (!G) printf("\nERRORE: impossibile allocare memoria per il grafo\n");
       else {
         G->vect=(node_vertex *)malloc(dim*sizeof(node_vertex));
         if (!G->vect) {
                  printf("ERRORE: impossibile allocare memoria ");
                  printf("per il vettore di liste\n");
                  free(G);
                  G=NULL;
         } else {
           G->nv = dim;
           for (i=0; i<dim; i++){
                   G->vect[i].v=i;
                   G->vect[i].present=0;
                   G->vect[i].adj=EMPTYGRAPH;
           }
        }
      }
   } else G=NULL;
   return(G);
}

/*funzione che inserisce l�arco (u,v) in un grafo G, inserendo anche il peso
w(u,v). L'arco (v,u) NON viene inserito. Se esiste deve essere fatto 
con una chiamata esplicita invertendo i vertici.
Precondizioni: G diverso da NULL; u e v vertici del grafo esistenti  
(compresi tra 0 e G->nv-1); l'arco (u,v) non � gi� presente nel grafo
Complessita' O(1)
*/

void AddEdgeGraph(graph G, vertex u, vertex v, weight w) {
    node_edge *new;

    if (G && u<G->nv && v<G->nv ) {
        if (G->vect[u].present && G->vect[v].present) {
            new = (node_edge*)malloc(sizeof(node_edge));
            if (new==NULL) printf("\nERRORE: impossibile allocare memoria \n");
            else {
                new->v=v; 
                new->w=w;
                new->next=G->vect[u].adj;
                G->vect[u].adj = new;
            }
        }
    }      
}

/*funzione che inserisce un nuovo vertice v in un grafo G.
Precondizione: G diverso da NULL. 
Complessita' O(1)
*/

void AddVertexGraph(graph G, vertex v) {
   node_vertex *p;
   unsigned int dim;
   
   if (G!=NULL && !G->vect[v].present)
     if(v<G->nv) 
           G->vect[v].present=1;
     else 
       if (v==G->nv) {
         dim=G->nv+1;       
         p=(node_vertex *)realloc(G->vect,dim*sizeof(node_vertex));
         if (!p) printf("ERRORE: impossibile reallocare memoria \n");
         else {
           G->vect=p;
           G->nv=dim;
           G->vect[v].v=v;
           G->vect[v].present=1;
           G->vect[v].adj=EMPTYGRAPH;
         }
      }  
}


/*Coda Con Priorita' Min */
/*nella coda ogni elemento ha come valore il vertex v */
/*e come priorita' il peso dell'arco w(s,v), ossia la distanza dalla sorgente */
 
#define CPVUOTA 0

typedef vertex tipobaseValCP;
typedef weight tipobasePrCP;

typedef struct {
		tipobaseValCP valore;
		tipobasePrCP priorita;
		unsigned long posizione;
} nodoCP;

typedef struct {
		unsigned long capacita, dim;
    nodoCP * H;
}CP;

void MakeCP(CP * p, unsigned long n){
    p->capacita=n;
    p->dim=CPVUOTA;
    p->H=(nodoCP *)malloc(n*sizeof(nodoCP));
}

void ReleaseCP(CP cp){
    free (cp.H);
}

boolean EmptyCP(CP cp){
 return(cp.dim==CPVUOTA);
}

boolean FullCP(CP cp){
 return(cp.dim==cp.capacita);
}

tipobaseValCP MinCP(CP cp){
  if (!EmptyCP(cp)) 
       return(cp.H[0].valore);
}

void scambio(nodoCP v[], unsigned long i, unsigned long j){
   nodoCP tmp=v[i];
   v[i]=v[j];
   v[j]=tmp;
   v[i].posizione=i;
   v[j].posizione=j;
}

void InsertMinCP(CP * p, tipobaseValCP x, tipobasePrCP pr){
   nodoCP tmp;
   unsigned long i;
   
   if (!FullCP(*p)) {
       i=p->dim;
       p->dim=p->dim+1;

       tmp.valore=x;
       tmp.priorita=pr;
       tmp.posizione=i;

       p->H[i]=tmp;
       
       while (i>0 && p->H[i].priorita < p->H[(i-1)/2].priorita) {
              scambio(p->H,i,(i-1)/2);
              i=(i-1)/2;
       }
   }    
}


void minHeapRestore(nodoCP v[], unsigned long i, unsigned long n){
   unsigned long min=i;
   
   if (2*i+1<n && v[2*i+1].priorita<v[min].priorita ) min=2*i+1;
   if (2*i+2<n && v[2*i+2].priorita<v[min].priorita) min=2*i+2;
   if (i!=min) {
       scambio(v,i,min);
       minHeapRestore(v,min,n);   
   }
}


tipobaseValCP DeleteMinCP(CP * p) {
   
   if (!EmptyCP(*p)){
       p->dim=p->dim-1;
       scambio(p->H,0,p->dim);
       minHeapRestore(p->H,0,p->dim);
       return p->H[p->dim].valore;  
   }       
}

void DecreaseKeyMinCP(CP * p, tipobaseValCP x, tipobasePrCP pr ) {

   unsigned int i;
      
   if (!EmptyCP(*p))
       for (i=0; i<p->dim; i++) 
           if (p->H[i].valore==x) {
             if (p->H[i].priorita>pr) {
                p->H[i].priorita=pr;
                while (i>0 && p->H[i].priorita < p->H[(i-1)/2].priorita) {
                         scambio(p->H,i,(i-1)/2);
                         i=(i-1)/2;
                }
             }
             break;
           }  
}


/*Strutture Dati Necessarie all'Algoritmo di Dijkstra*/
/*Vengono usati due vettori di dimensione n, ossia numero di vertici*/
/*Ogni vettore ha come indice, l'indice del vertice */
/*Vettore d[n]: contiene per ogni vertice la distanza minima dalla sorgente s*/
/*Vettore padre[n]: e' l'albero dei cammini mimini a partire da s*/
/*Alla fine dell'algoritmo di Dijkstra, il vettore d fornisce per ogni vertice, 
il valore della distanza minima dal vertice sorgente s */
/*Il vettore padre, deve essere letto a ritroso a partire da un vertice destinazione*/
/*Ad esempio supponiamo che ci siano 6 vertici nel grafo e si supponga che 
il nodo sorgente s sia il vertice 0. Si supponga poi che il vettore padre sia,
alla fine dell'algoritmo di Dijkstra:
     
    ?,0,0,1,3,4 

il punto ? e' stato messo perche' il vertice 0 e' la sorgente.
Il vettore padre deve essere letto come segue. Si supponga si voglia sapere il 
cammino minimo dal vertice 0 al vertice 5. Dall'elemento di indice 5 si 
viene a sapere che il padre di 5 e' il 4. Dall'elemento 4, si viene a 
sapere che il padre di 4 e' il 3. Dall'elemento di indice 3 si viene a sapere
che il padre di 3 e' 1, e infine dall'elemento di indice 1 si viene a sapere
che il padre e' il vertice sorgente 0. Dunque il cammino minimo e':
    0, 1, 3, 4, 5
*/

/*i vettori padre e d vengono allocati all'esatta dimensione di n, ossia del
numero di vertici nel grafo*/

vertex *padre;
weight *d;

/*L'algoritmo riceve in ingresso un grafo G, un vertice sorgente s, 
e fornisce i vettori delle distanze e dell'albero dei cammini minimi a partire
dalla sorgente s */

void Dijkstra(graph G, vertex s, vertex padre[], weight d[]){

   vertex u,v;
   CP coda;
   node_edge *p; 
   
   if (G && s<G->nv && G->vect[s].present) {
      for (u=0; u<G->nv; u++) d[u]=INFINITO;
      d[s]=0;
      MakeCP(&coda, G->nv);
      InsertMinCP(&coda, s, d[s]);
      while (!EmptyCP(coda)){
        u=DeleteMinCP(&coda);
        p=G->vect[u].adj;
        if (p) {
           if (d[p->v]==INFINITO) {
              InsertMinCP(&coda,p->v,d[u]+p->w);
              d[p->v]=d[u]+p->w;
              padre[p->v]=u;
           } else if (d[u]+p->w<d[p->v]) {
              DecreaseKeyMinCP(&coda,p->v,d[u]+p->w);
              d[p->v]=d[u]+p->w;
              padre[p->v]=u;
           }  
           while (p->next->next!=EMPTYGRAPH){
              if (d[p->next->v]==INFINITO) {
                 InsertMinCP(&coda,p->next->v,d[u]+p->next->w);
                 d[p->next->v]=d[u]+p->next->w;
                 padre[p->next->v]=u;
              } else if (d[u]+p->next->w < d[p->next->v]) {
                 DecreaseKeyMinCP(&coda,p->next->v,d[u]+p->next->w);
                 d[p->next->v]=d[u]+p->next->w;
                 padre[p->next->v]=u;
              }     
              p=p->next;
           }
        }
      }
      ReleaseCP(coda);
   }
} 


main(){

}
