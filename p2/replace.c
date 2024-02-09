/**
 * @file replace.c
 * @author krvadla Kavya Vadla
 * replace file that will replace the replacement strings into the story
*/

#include "replace.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Computes the length of the line if the replacement string is added to the line
 * @param line line of story
 * @param word replacement string being inserted
 * @param placeholder placeholder that replacement string will replace
 * @return returns true if line will be less than 100 characters, false if it will be more than
 * 100 characters
*/
static bool computeLen( char line[ LINE_MAX + 1], char word[ FIELD_MAX + 1], char placeholder[])
{
    int lineCount = 0;
    int wordCount = 0;
    int placeCount = 2;
    for (int i = 0; line[i]; i++) {
        lineCount++;
    }
    for (int i = 0; word[i]; i++) {
        wordCount++;
    }
    for (int i = 0; placeholder[i]; i++) {
        placeCount++;
    }

    if ((lineCount - placeCount + wordCount) > LINE_MAX) {
        
        return false;
    }

    return true;

}

void replaceWord( char line[ LINE_MAX + 1], char word[ FIELD_MAX + 1], char placeholder[] )
{
    if (computeLen(line, word, placeholder)) {
        char temp[LINE_MAX + 1];
        int t = 0;
        for (int i = 0; line[i]; i++) {
            if (line[i] == '<' ) {
                char placetemp[FIELD_MAX];
                int k = 0;
                for (int j = i + 1; line[j] != '>'; j++) {
                    placetemp[k] = line[j];
                    placetemp[k + 1] = '\0';
                    k++;
                    i = j + 1;
                }
                int placeCount = 0;
                for (int j = 0; placetemp[j]; j++) {
                    placeCount++;
                }
                char place[placeCount];
                for (int j = 0; placetemp[j]; j++) {
                    place[j] = placetemp[j];
                    place[j + 1] = '\0';
                }
                if (strcmp(&place[0], "noun1") != 0 && strcmp(&place[0], "noun2") != 0 && strcmp(&place[0], "verb") != 0 && strcmp(&place[0], "adverb") != 0 && strcmp(&place[0], "adjective") != 0) {
                    exit(EXIT_4);
                }
                if (strcmp(&place[0], &placeholder[0]) == 0) {
                    for (int j = 0; word[j]; j++) {
                        temp[t] = word[j];
                        t++;
                    }
                } else {
                    temp[t] = '<';
                    t++;
                    for (int j = 0; place[j]; j++) {
                        temp[t] = place[j];
                        t++;
                    }
                    temp[t] = '>';
                    t++;
                }
            } else {
                temp[t] = line[i];
                t++;
            }
        }
        temp[t] = '\0';
        strcpy(line, temp);
    } else {
        exit(EXIT_3);
    }
    
}

