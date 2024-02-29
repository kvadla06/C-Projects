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

/** number to convert between lowercase letters to array values that they're stored in*/
#define CONVERT_L 97

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
        *val = 0;
    } else if (ch == '-' || 'A' <= ch <= 'T') {
        ungetc(input);
        *vname = '\0';
        bool valid = parseNumber(val, input);
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
    char operator = skipWhitespace(input);
    char vname;
    long val = 0;
    if (operator != '+' && operator != '-' && operator != '/' && operator != '*') {
        return false;
    }
    if (!parseOperand(&val, &vname, input)) {
        return false;
    }
    if (vname != '\0') {
        value = var[vname - CONVERT_L];
    }
    switch (operator) {
        case '-':
            if (!subtract(result, left, val)){
                return false;
            }
            break;
        case '+':
            if (!add(result, left, val)){
                return false;
            }
            break;
        case '*':
            if (!multiply(result, left, val)){
                return false;
            }
            break;
        case '/':
            if (!divide(result, left, val)){
                return false;
            }
            break;
    }
}

/**
* This function reads the next statement from the input stream. If it’s an expression, 
* it reports its value to the given output stream using the given stmt number as the statement number.
* @param stmtNum number of statement to print
* @param input file input stream to read from
* @param output file output stream to write to 
* @return returns false if expression is invalid or true if its valid
*/
bool parseStatement( int stmtNum, FILE *input, FILE *output )
{
    long value = 0; 
    long result = 0;
    char vname;
    char ch;
    if (parseOperand(&value, &vname, input)) {
        if (vname != '\0') {
            ch = skipWhitespace(input);
            if (ch == '=') {
                ch = skipWhitespace(input);
                ungetc(input);
                if (parseOperand(&value, &value, input)) {
                    ch = skipWhitespace(input);
                    if (ch == ';') {
                        var[vname - CONVERT_L] = value;
                    } else {
                        ungetc(input);
                        if (parseExpression(&result, &value, input)){
                            var[vname - CONVERT_L] = result;
                            return true;
                        } else {
                            fprintf(output, "S%d: invalid\n", stmtNum);
                            return false;
                        }
                    }
                } else {
                    fprintf(output, "S%d: invalid\n", stmtNum);
                    return false;
                }
            } else {
                value = var[vname - CONVERT_L];
            }
        }
        ch = skipWhitespace(input);
        if (ch != '+' && ch != '-' && ch != '/' && ch != '*') {
            fprintf(output, "S%d: invalid\n", stmtNum);
            return false;
        }
        ungetc(input);
        if (parseExpression(&result, &value, input)) {
            fprintf(output, "S%d: %ld\n", stmtNum, result);
            return true;
        } else {
            fprintf(output, "S%d: invalid\n", stmtNum);
            return false;
        }

    } else {
        fprintf(output, "S%d: invalid\n", stmtNum);
        return false;
    }
}