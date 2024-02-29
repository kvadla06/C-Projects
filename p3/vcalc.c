/**
* @file vcalc.c
* @author krvadla Kavya Vadla
* the top-level component, containing the main() function and supporting functions to parse statements, expressions and operands.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "vigesimal.h"
#include "check.h"

/** Requried input-file argument. */
#define INPUT_ARG 1

/** Optional, output-file argument. */
#define OUTPUT_ARG 2

/** number of letters in alphabet */
#define ALPHA 26

/** array to hold values of variables */
long var[ALPHA];

static void usage()
{
  fprintf( stderr, "usage: vcalc INPUT-FILE [OUTPUT-FILE]\n");
  exit( EXIT_FAILURE );
}

int main (int argc, char *argv[]) 
{
    if (argc != OUTPUT_ARG || argc != OUTPUT_ARG + 1) {
        usage();
    }
    FILE *fi;
    if ( ( fi = fopen( argv[INPUT_ARG], "r" ) ) == NULL ) {
        fprintf( stderr, "Can't open file: %s\n", argv[INPUT_ARG] );
        exit( EXIT_FAILURE );
    }

    FILE *fw;
    if (argv[OUTPUT_ARG] != '\0') {
        *fw = fopen(argv[OUTPUT_ARG], "w");
    } else {
        *fw = fopen("output.txt", "w");
    }
    
    int stmtNum = 0; 
    while (!feof(fi)) {
        parseStatement(stmtNum, *fi, *fw);
        stmtNum++;
    }

  fclose(fi);
  fclose(fw);
}

/**
* This function attempts to read the next operand from the given input stream. 
* It stores the value of the operand in the long variable pointed to by val. If the operand is a variable, 
* it also stores the name of the variable in the char pointed to by vname. 
* If it’s not a variable, it sets the char to '\0'.
* @param val value of operand
* @param vname name of variable 
* @param input file input stream to read from
* @return returns false if input does not have a valid operand and true if it does
*/
bool parseOperand( long *val, char *vname, FILE *input )
{
    char ch = fgetc(input); 
    if (islower(ch) != 0) {
        *vname = ch;
    } else if (ch == '-' || 'A' <= ch <= 'T') {
        ungetc(input);
        *vname = '\0';
        bool valid = parseNumber(*val, *input);
        return valid;
    } else{
        return false;
    }
   
}

/**
* This function reads an expression as a sequence of operands separated by the ‘+’, ‘-’, ’*’ and ‘/’ operators.
* It computes the result of the whole expression and stores it in the long variable pointed to by result.
* @param result result of the calculated expression 
* @param left parsed value of the first operand 
* @param input file input stream to read from
* @return returns false if expression is invalid or true if its valid
*/
bool parseExpression( long *result, long left, FILE *input )
{
    
}

/**
* This function reads an expression as a sequence of operands separated by the ‘+’, ‘-’, ’*’ and ‘/’ operators.
* It computes the result of the whole expression and stores it in the long variable pointed to by result.
* @param stmtNum number of statement to print
* @param input file input stream to read from
* @param output file output stream to write to 
* @return returns false if expression is invalid or true if its valid
*/
bool parseStatement( int stmtNum, FILE *input, FILE *output )
{
    
}