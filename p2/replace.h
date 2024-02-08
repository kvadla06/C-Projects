/**
* @file replace.h
* @author krvadla Kavya Vadla
* header file for replace file that will insert the replacement strings in the story
*/

#include <stdbool.h>

/** Maximum length for replacement string. */
#define FIELD_MAX 24

/** Maximum length for line of text. */
#define LINE_MAX 100

/** exit status 1*/
#define EXIT_1 101

/** exit status 2*/
#define EXIT_2 102

/** exit status 1*/
#define EXIT_3 103

/**
 * replaces placeholders with the given replacement strings
 * @param line line for the replacement strings to be inserted into
 * @param word replacment string to be put into the story
 * @param placeholder placeholder to be replaced
*/
void replaceWord( char line[ LINE_MAX + 1], char word[ FIELD_MAX + 1], char placeholder[] );