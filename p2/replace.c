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
    int lineCount;
    int wordCount;
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
        int placeLength;
        for(int i = 0; placeholder[i]; i++) {
            placeLength++;
        }
        char temp[LINE_MAX + 1];
        int linePlace;
        for (int i = 0; line[i]; i++) {
            if (line[i] == '<' ) {
                char placetemp[placeLength + 1];
                for (int j = i; line[j] == '>'; j++) {
                    int k = 0;
                    placetemp[k] = line[j];
                    k++;
                }
                if (strcmp(placeholder, placetemp) == 0) {
                    strcat(temp, word);
                    for (int k = i; line[k] == '>'; k++) {
                        linePlace = k + 1;
                    }
                    break;
                }
            } else {
                temp[i] = line[i];
            }
        }
        for (int i = linePlace + 1; line[i]; i++) {
            temp[i] = line[i];
        }
        line = temp;
    }
    
}

