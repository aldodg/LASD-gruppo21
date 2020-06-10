#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "List.h"
#include "Graph.h"

List initNodeList(int info, int peso) {
    List L = malloc(sizeof(struct TList));
    L->target = info;
    L->peso = peso;
    L->next = NULL;
    return L;
}


List randomList(int index, int mod) {
    List L = NULL;
    int i = 0;
    for (i = 0; i < index; i++) {
        L = appendNodeList(L, rand() % mod, rand() % 50);
    }
    return L;
}


List appendNodeList(List L, int target, int peso) {
    if (L != NULL) {
        if (L->target != target) {
            L->next = appendNodeList(L->next, target, peso);
        }
    } else {
        L = initNodeList(target, peso);
    }
    return L;
}

List addNodeHead(List L, int target, int peso) {
    if (L != NULL) {
        List G = malloc(sizeof(struct TList));
        G->target = target;
        G->next = L;
        return G;
    }
    return initNodeList(target, peso);
}




List removeNodeList(List L, int target) {
if (L != NULL) {
        if (L->target == target) {
            List tmp = L->next;
            free(L);
            return tmp;
            L=removeNodeList(L->next,target);
        }
        L->next = removeNodeList(L->next, target);
    }
    return L;
}


void freeList(List L) {
    if (L != NULL) {
        freeList(L->next);
        free(L);
    }
}


void printList(List L) {
    if (L != NULL) {
        printf(" %d(%d) ", L->target, L->peso);
        printList(L->next);
    }
}

