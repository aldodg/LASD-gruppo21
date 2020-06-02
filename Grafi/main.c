#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Graph.c"

//ATTENZIONE, DOBBIAMO MODIFICARE QUESTE LIBRERIE IN MODO CHE GESTISCANO CORRETTAMENTE LE STRINGHE
//PER IL MOMENTO COMPILIAMO QUESTO FILE CON IL SUO MAIN
//QUANDO FUNZIONERA' TUTTO COPIAMO SOLO LE LIBRERIE CHE CI SERVONO


int main(int argc, const char * argv[]) {
    srand((unsigned int)time(NULL));
   Graph L= initGraph(10);
    addEdge(L,1,2,20,"Catania");
    printGraph(L);
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}

