#include <stdio.h>
#include <stdlib.h>

int main()
{

    srand(time(NULL));
    printf("\nA= \n");
    printGraph(A);

    Graphmat A;
    A=randomGraphMat(20,2,4);
    return 0;
}
