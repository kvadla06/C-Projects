/**
 * @file input.c
 * @author krvadla Kavya Vadla
 * input file to read in the replacement strings
*/

#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



void readWord( char word[ FIELD_MAX + 1 ])
{
    if (scanf("%[^\n]%*c", word) == EOF) {
        exit(EXIT_1);
    }
    
    int count = 0;

    for(int i = 0; word[i]; i++) {
        if (isalnum(word[i]) == 0) {
            if (ispunct(word[i]) == 0) {
                if (isspace(word[i]) == 0) {
                    exit(EXIT_2);
                }
            } else {
                if (word[i] != '\'' && word[i] != '-') {
                    exit(EXIT_2);
                }
            }
        }
        count++;
    }

    if (count > FIELD_MAX) {
        exit(EXIT_2);
    }
}

bool readLine( char line[ LINE_MAX + 1 ])
{
    if (scanf("%[^\n]%*c", line) == EOF) {
        return false;
    }

    int count = 0;
    for (int i = 0; line[i]; i++) {
        count++;
    }
    
    if (count > LINE_MAX) {
        exit(EXIT_3);
    }

    return true;
}