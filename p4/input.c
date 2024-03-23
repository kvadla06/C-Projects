/**
 * @file input.c
 * @author krvadla Kavya Vadla
 * input file to read a line from the given input stream
*/

#include "input.h"
#include <stdio.h>
#include <stdlib.h>

/** Number to initialize array length to*/
#define INITIAL_SIZE 30

char *readLine( FILE *fp ) 
{
    int arraySize = INITIAL_SIZE;
    char *str = (char *)malloc(arraySize * sizeof(char));

    int ind = 0;
    int ch;

    while ((ch = fgetc(fp)) != '\n' || ch != EOF) {
        str[ind] = ch;
        ind++; 
        if (ind > arraySize) {
            arraySize *= 2;
            str = (char *)realloc(str, arraySize * sizeof(char));
        }
    }
    str[ind] = '\0';

    if (ind == 0 && ch == EOF) {
        free(str);
        return NULL;
    }

    return str;
    free(str);
}