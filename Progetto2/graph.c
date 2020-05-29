#include"graph.h"

int empty_graph(struct grafo* G){
	return G==NULL;
}


int creaGrafo(int vertici, grafo **g, int pesato){

  grafo *nuovo;
  int ret = 0;//inizializzata a 0 per gestire implicitamente i casi in cui non fosse possibile allocare memoria
  int i;

  if(vertici > 0){//alloca memoria solo se vertici e' maggiore di 0
    nuovo = (grafo*)malloc(sizeof(grafo));//alloca memoria per un nuovo grafo

    if(nuovo != NULL){//se ha allocato memoria per il grafo
      nuovo->n_vertici = vertici;
      nuovo->adiacenti = (arco**)malloc(sizeof(arco*) * vertici);//alloca memoria per il vettore di liste

      if(nuovo->adiacenti != NULL){//se ha allocato il vettore di liste
        for(i = 0; i < vertici; i++){//pone tutte le liste a NULL
          nuovo->adiacenti[i] = NULL;
        }

        *g = nuovo;//pone il valore del puntatore parametro alla posizione del grafo allocato
        ret = 1;

      }else{//se la malloc del vettore e' fallita
        printf("ERRORE in nuovoGrafo: impossibile allocare memoria per vettore di liste di adiacenza\n");
        free(nuovo);//dealloca la memoria del grafo
      }
    }else{//caso memoria per grafo non allocata gestito implicitamente
      printf("ERRORE in nuovoGrafo: impossibile allocare memoria per grafo\n");
    }
  }else{//caso vertici <= 0 gestito implicitamente
    printf("ERRORE in nuovoGrafo: impossibile creare grafo di 0 vertici\n");
  }
  return ret;//ritorna 1 o 0 a seconda che la creazione sia andata a buon fine o meno
}


void stampaGrafo(struct grafo* G){
	int ca=0, i; arco* app;
	if(!empty_graph(G)){
		printf("IL GRAFO HA VERTICI %d", G->n_vertici);
		printf("\n");
		for(i=0;i<G->n_vertici;i++){
			printf("NODI ADIACENTI AL VERTICE %d", i);
			printf("\n");
			app=G->adiacenti[i];
			while(app!=NULL){
				printf("%s",app->localita);
				printf("\n");
				ca++;
				app=app->next;
			}
		}
	}
	printf("IL GRAFO HA ARCHI %d", ca/2);
	printf("\n");
}

arco *nuovoArco(int destinazione, int costo){

  arco *nuovo = NULL;

  nuovo = (arco*)malloc(sizeof(arco));
  if(nuovo != NULL){
    nuovo->localita = destinazione;
    nuovo->next = NULL;
    nuovo->costo = costo;
  }else{
    printf("ERRORE: memoria insufficiente\n");
  }

  return nuovo;
}

