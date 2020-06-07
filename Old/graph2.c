#include"graph.h"

int empty_graph(grafo* G)
{
    return G==NULL;
}



int creaGrafo(int vertici, grafo **g)
{

    grafo *nuovo;
    int ret = 0;//inizializzata a 0 per gestire implicitamente i casi in cui non fosse possibile allocare memoria
    int i;

    if(vertici > 0) //alloca memoria solo se vertici e' maggiore di 0
    {
        nuovo = (grafo*)malloc(sizeof(grafo));//alloca memoria per un nuovo grafo

        if(nuovo != NULL) //se ha allocato memoria per il grafo
        {
            nuovo->n_vertici = vertici;
            nuovo->adiacenti = (arco**)malloc(sizeof(arco*) * vertici);//alloca memoria per il vettore di liste

            if(nuovo->adiacenti != NULL) //se ha allocato il vettore di liste
            {
                for(i = 0; i < vertici; i++) //pone tutte le liste a NULL
                {
                    nuovo->adiacenti[i] = NULL;
                }

                *g = nuovo;//pone il valore del puntatore parametro alla posizione del grafo allocato
                ret = 1;

            }
            else  //se la malloc del vettore e' fallita
            {
                printf("ERRORE in nuovoGrafo: impossibile allocare memoria per vettore di liste di adiacenza\n");
                free(nuovo);//dealloca la memoria del grafo
            }
        }
        else  //caso memoria per grafo non allocata gestito implicitamente
        {
            printf("ERRORE in nuovoGrafo: impossibile allocare memoria per grafo\n");
        }
    }
    else  //caso vertici <= 0 gestito implicitamente
    {
        printf("ERRORE in nuovoGrafo: impossibile creare grafo di 0 vertici\n");
    }
    return ret;//ritorna 1 o 0 a seconda che la creazione sia andata a buon fine o meno
}



void stampaGrafo(grafo* G)
{
    int ca=0, i;
    arco* app;
    if(!empty_graph(G))
    {
        printf("IL GRAFO HA VERTICI %d", G->n_vertici);
        printf("\n");
        for(i=0; i<G->n_vertici; i++)
        {
            printf("NODI ADIACENTI AL VERTICE %d", i);
            printf("\n");
            app=G->adiacenti[i];
            while(app!=NULL)
            {
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



arco *nuovoArco(int destinazione, int costo)
{

    arco *nuovo = NULL;

    nuovo = (arco*)malloc(sizeof(arco));
    if(nuovo != NULL)
    {
        *nuovo->localita = destinazione;
        nuovo->next = NULL;
        nuovo->costo = costo;
    }
    else
    {
        printf("ERRORE: memoria insufficiente\n");
    }

    return nuovo;
}



int numeroVertici(grafo *g)
{

    int ret;

    if(!empty_graph(g))
    {
        ret = g->n_vertici;
    }
    else
    {
        ret = 0;
    }

    return ret;
}



int numeroArchi(grafo *g)
{

    int ret = 0;
    int i;
    arco *curr;

    if(!empty_graph(g))
    {
        for(i = 0; i < g->n_vertici; i++) //per tutte le liste di adiacenza del vettore
        {

            curr = g->adiacenti[i];//partendo dall'inizio

            while(curr != NULL) //scorre la lista e conta gli elementi, potenzialmente 0
            {
                ret = ret + 1;
                curr = curr->next;
            }
        }
    }
    return ret;
}



int aggiungiArcoPesato(grafo *g, int partenza, int arrivo, int costo)
{

    arco *curr;
    int ret = 0;

    if(!empty_graph(g))
    {

        if(costo == 0)
        {

            if(partenza < g->n_vertici && arrivo < g->n_vertici)
            {

                curr = g->adiacenti[partenza];//imposta curr al primo arco uscente da partenza
                while(curr != NULL && curr->next != NULL && *curr->localita != arrivo)
                {
                    /*arriva alla fine della lista di adiacenza di partenza
                    o si ferma prima se l'arco con arrivo uguale e' gia' presente*/
                    curr = curr->next;
                }

                if(curr == NULL) //se la lista di adiacenza era vuota
                {
                    g->adiacenti[partenza] = nuovoArco(arrivo, costo);//crea un arco e modifica il puntatore nell'array perche' punti a questo
                    ret = 1;
                }
                else if(curr->next == NULL)  //se e' arrivato alla fine della lista
                {
                    curr->next = nuovoArco(arrivo, costo);//crea un arco e lo imposta come successivo dell'ultimo
                    ret = 1;
                }
                else  //l'arco era gia' presente
                {
                    printf("L'arco %d -> %d e' gia' presente nel grafo\n", partenza, arrivo);
                    ret = 1;
                }
            }
            else
            {
                printf("Non esiste il vertice di partenza o di arrivo\n");
            }
        }
        else
        {
            printf("Impossibile inserire arco pesato in grafo non pesato\n");
        }
    }
    else
    {
        printf("Il grafo e' vuoto\n");
    }
    return ret;
}



int aggiungiArco(grafo *g, int partenza, int arrivo)
{

    return aggiungiArcoPesato(g,partenza,arrivo,0);
}



int rimuoviArco(grafo *g, int partenza, int arrivo)
{


    arco *curr, *prev;
    int ret = 0;

    if(!empty_graph(g))
    {

        if(partenza < g->n_vertici && arrivo < g->n_vertici)
        {

            ret = 1;
            curr = g->adiacenti[partenza];

            while(curr != NULL && *curr->localita != arrivo)
            {
                prev = curr;
                curr = curr->next;
            }

            if(curr != NULL) //controlla sia il caso in cui la lista fosse vuota, sia il caso in cui sia stata esplorata tutta senza trovare l'elemento
            {

                if(curr == (g)->adiacenti[partenza]) //se il nodo da eliminare e' il primo bisogna modificare il puntatore nel vettore delle liste
                {
                    g->adiacenti[partenza] = g->adiacenti[partenza]->next;
                    free(curr);
                }
                else  //altrimenti l'eliminazione e' uguale sia se l'elemento e' centrale sia se e' l'ultimo della lista
                {
                    prev->next = curr->next;
                    free(curr);
                }

            }
            else
            {
                printf("L'arco non e' presente nel grafo\n");
                ret = 1;
            }
        }
        else
        {
            printf("Non esiste il vertice di partenza o di arrivo\n");
        }
    }
    else
    {
        printf("Il grafo e' vuoto\n");
    }
    return ret;
}



int esisteArco(grafo *g, int partenza, int arrivo)
{

    int ret = 0;
    arco *curr;

    if(!empty_graph(g))
    {
        if(partenza <= g->n_vertici && arrivo <= g->n_vertici)
        {

            curr = g->adiacenti[partenza];
            while(curr != NULL && ret == 0)
            {

                if(*curr->localita == arrivo)
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



int costoArco(grafo *g, int partenza, int arrivo)
{

    arco *curr = NULL;
    int ret = 0;

    if(!empty_graph(g))
    {
        if(esisteArco(g, partenza, arrivo)) //forse esisteArco dovrebbe anche in qualche modo ritornare un puntatore all'arco se esiste?
        {

            curr = g->adiacenti[partenza];
            while(*curr->localita != arrivo)
            {
                curr = curr->next;
            }
            ret = curr->costo;
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



int aggiungiVertice(grafo *g)
{

    arco **nuovo = NULL;
    int ret = 0;

    if(!empty_graph(g))
    {

        nuovo = (arco**)realloc(g->adiacenti, g->n_vertici + 1);

        if(nuovo != NULL)
        {
            g->adiacenti = nuovo;
            g->n_vertici = g->n_vertici + 1;
            ret = 1;
        }
        else
        {
            printf("Impossibile allocare memoria per nuovo vertice\n");
        }
    }
    else
    {
        printf("Grafo vuoto\n");
    }

    return ret;
}



int esisteVertice(grafo *g, int v)
{
    return v < g->n_vertici;
}



int rimuoviVertice(grafo *g, int vertice)
{

    int ret = 0;
    int i;
    arco **nuovo = NULL;
    arco *prev = NULL, *curr = NULL;

    if(!empty_graph(g))
    {

        if(vertice < g->n_vertici) //se il vertice da eliminare è presente
        {

            nuovo = (arco**)malloc(sizeof(arco*) * (g->n_vertici - 1));//alloca memoria per un vettore degli adiacenti temporaneo di un elemento in meno rispetto all'attuale
            if(nuovo != NULL) //se l'allocazione è andata a buon fine
            {

                ret = 1;

                for(i = 0; i < g->n_vertici; i++) //scorre tutte le vecchie liste d'adiacenza
                {

                    if(i < vertice || i > vertice) //per tutte le liste tranne quella del vertice da eliminare
                    {
                        curr = g->adiacenti[i];//parte dall'inizio
                        prev = curr;//tiene traccia del precedente dell'elemento considerato

                        while(curr != NULL) //scorre tutta una lista
                        {

                            if(*curr->localita == vertice) //se analizza un arco che andava nel vertice da eliminare
                            {

                                if(curr == g->adiacenti[i]) //se l'arco da eliminare è il primo
                                {
                                    g->adiacenti[i] = g->adiacenti[i]->next;//imposta il nuovo primo nel vettore delle liste
                                    free(curr);
                                    curr = g->adiacenti[i];//setta il prossimo elemento della lista da analizzare

                                }
                                else  //se l'arco da eliminare e' in una posizione qualunque tranne la prima
                                {
                                    prev->next = curr->next;//bypassa l'elemento da eliminare
                                    free(curr);
                                    curr = prev->next;//setta il prossimo da analizzare
                                }

                            }
                            else  //se l'arco non andava nel vertice da eliminare
                            {

                                if(*curr->localita > vertice) //se andava in un vertice maggiore di quello da eliminare
                                {
                                    curr->localita = curr->localita - 1;//diminuisce il valore di questo perché dopo aver eliminato vertice tutti i maggiori avranno il loro numero ridotto

                                }
                                prev = curr;//manda avanti la ricerca sia se l'arco era maggiore, sia se non lo era
                                curr = curr->next;
                            }
                        }//fine del while

                        //ogni elemento del nuovo vettore delle liste viene fatto puntare alla lista corretta
                        if(i < vertice)
                        {
                            nuovo[i] = g->adiacenti[i];
                        }
                        else
                        {
                            nuovo[i-1] = g->adiacenti[i];
                        }

                    }
                    else if(i == vertice)  //per la lista del vertice da eliminare
                    {

                        prev = g->adiacenti[i];

                        while(prev != NULL) //elimina tutti i nodi
                        {
                            curr = prev->next;
                            free(prev);
                            prev = curr;
                        }
                    }
                }

                free(g->adiacenti);//elimina il vecchio vettore dei puntatori alle liste
                g->adiacenti = nuovo;//modifica il puntatore verso il vettore delle liste
                g->n_vertici = g->n_vertici - 1;//riduce il numero di vertici nella struttura grafo

            }
            else
            {
                printf("ERRORE in rimuoviVertice: Impossibile allocare memoria per nuovo vettore delle adiacenze\n");
            }
        }
        else
        {
            printf("ERRORE in rimuoviVertice: Vertice da rimuovere fuori dal range del grafo\n");
        }
    }
    else
    {
        printf("ERRORE in rimuoviVertice: Il grafo e' vuoto\n");
    }
    return ret;
}
