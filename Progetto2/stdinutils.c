
#include <stdio.h>
#include <stdlib.h>
#include "stdinutils.h"
//Funzioni di input

char* read()
{
    unsigned size = BUFSIZE;
    char *buf = NULL;
    int c, i;

    size = i = 0;
    do
    {
        size += BUFSIZE;
        buf = realloc(buf, size);
        while (i < size && (c = getchar()) != '\n')
            buf[i++] = c;
    }
    while (c != '\n');
    if (!i)
    {
        free(buf);
        return NULL;
    }
    buf[i] = '\0';
    return buf;
}

int readint()
{
    char *char_input = read();
    int input = atoi(char_input);
    free(char_input);
    return input;
}
