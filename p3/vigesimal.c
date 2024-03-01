/**
* @file vigesimal.c
* @author krvadla Kavya Vadla
* This component reads numeric values from input and writes results to output in base 20
*/

#include "vigesimal.h"
#include "check.h"
#include <ctype.h>
#include <limits.h>

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
  
  if (ch == '-') {
    ch = fgetc(input);
    if ('A' <= ch && ch <= 'T') {
        while ( 'A' <= ch && ch <= 'T' ) {
            int d = (ch - CONVERT);
            if (!multiply(val, *val, BASE)) {
                return false;
            }
            if (!subtract(val, *val, d)) {
                return false;
            }
            ch = fgetc(input);
        }
    }  else {
        return false;
    }
    ungetc(ch, input);
    return true;
  }
  if ('A' <= ch && ch <= 'T') {
    while ( 'A' <= ch && ch <= 'T' ) {
        int d = ch - CONVERT;
        if (!multiply(val, *val, BASE)) {
            return false;
            }
        if (!add(val, *val, d)) {
            return false;
        }
        ch = fgetc(input);
    }
  } else {
    return false;
  }
  
  ungetc(ch, input);
  return true;
}

void printNumber( long val, FILE *output )
{
  int idx = 0;
  char str[MAX_NUMBER_LEN];
  bool longmin = false;

  if (val < 0) {
    fputc('-', output);
    if (val == LONG_MIN) {
        val += 1;
        longmin = true;
    }
    val = val * -1;
  }
  
  if (val == 0) {
    str[idx] = 'A';
    idx++;
  }
  
  int addone = 0;
  while ( val != 0 ) {
    int d = val % BASE;
    char ch = d + CONVERT;
    if (longmin) {
        if (addone == 0) {
            str[ idx ] = ch + 1;
            addone = 1;
        } else {
            str[ idx ] = ch;
        }
    } else {
        str[ idx ] = ch;
    }
    idx++;
    val = val / BASE;
  }

  str[ idx ] = '\0';

  for (int i = idx - 1; i >= 0 ; i--) {
    fputc(str[i], output);
  }
}