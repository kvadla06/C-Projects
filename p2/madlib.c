/**
 * @file madlib.c
 * @author krvadla Kavya Vadla
 * Main file that runs the madlib program
*/

#include "replace.h"
#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Main method that runs the madlib program
 * @return if the program was run successfully or not
*/
int main() {
    char noun1[FIELD_MAX + 1];
    char noun2[FIELD_MAX + 1];
    char verb[FIELD_MAX + 1];
    char adj[FIELD_MAX + 1];
    char adv[FIELD_MAX + 1];
    readWord(noun1);
    readWord(noun2);
    readWord(verb);
    readWord(adj);
    readWord(adv);
    
    char place1[] = "noun1";
    char place2[] = "noun2";
    char place3[] = "verb";
    char place4[] = "adj";
    char place5[] = "adv";
    char line [LINE_MAX + 1];
    while (readLine(line)) {
        replaceWord(line, noun1, place1);
        replaceWord(line, noun2, place2);
        replaceWord(line, noun2, place3);
        replaceWord(line, noun2, place4);
        replaceWord(line, noun2, place5);
        printf("%s\n", line);
    }
}