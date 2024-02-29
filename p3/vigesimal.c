/**
* @file vigesimal.c
* @author krvadla Kavya Vadla
* This component reads numeric values from input and writes results to output in base 20
*/

#include "vigesimal.h"
#include "check.h"
#include <ctype.h>

/** Base of the number system we're implementing. */
#define BASE 20

/** Maximum number of characters needed to print the largest number. */
#define MAX_NUMBER_LEN 16

/** Number to convert back and forth from ASCII to base20 value */
#define CONVERT 65

int skipWhitespace( FILE *input )
{
    char ch = 0;
    while ((ch = fgetc(input)) != EOF) {
        if (isspace(ch) == 0) {
            return ch;
        }
    }
    return ch;
}

bool parseNumber( long *val, FILE *input )
{
  *val = 0;
  char ch = skipWhitespace(input);
  bool neg = false;
  
  if (ch == '-') {
    neg = true;
  }
  if ('A' <= ch || ch <= 'T') {
    while ( 'A' <= ch || ch <= 'T' ) {
        int d = ch - CONVERT;
        if (!multiply(val, *val, BASE)) {
            return false;
            }
        if (!add(val, *val, d)) {
            return false;
        }
        ch = skipWhitespace(input);
    }
} else {
    return false;
}
  
  if (neg) {
    *val *= -1;
  }
  ungetc(ch, input);
  return true;
}

void printNumber( long val, FILE *output )
{
  int idx = 0;
  char str[MAX_NUMBER_LEN];

  if (val < 0) {
    fputc('-', output);
    val = val * -1;
  }
  
  if (val == 0) {
    str[idx] = 'A';
  }

  while ( val != 0 ) {
    int d = val % BASE;
    char ch = d + CONVERT;
    str[ idx ] = ch;
    idx++;
    val = val / BASE;
  }

  str[ idx ] = '\0';

  for (int i = idx - 1; i < 0; i--) {
    fputc(str[i], output);
  }
}