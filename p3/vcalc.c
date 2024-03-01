/**
* @file vcalc.c
* @author krvadla Kavya Vadla
* the top-level component, containing the main() function and supporting functions to parse statements, expressions and operands.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

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
    char ch = skipWhitespace(input); 
    if (islower(ch) != 0) {
        *vname = ch;
        *val = var[*vname - CONVERT_L];
        return true;
    } else if (ch == '-' ) {
        ungetc(ch, input);
        *vname = '\0';
        bool valid = parseNumber(val, input);
        return valid;
    } else if ('A' <= ch && ch <= 'T') {
        ungetc(ch, input);
        *vname = '\0';
        bool valid = parseNumber(val, input);
        return valid;
    }
   return false;
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
    char operator = '\0';
    char vname = '\0';
    long val = 0;
    
    while ((operator = skipWhitespace(input)) != ';' && operator != EOF){
        if (operator != '+' && operator != '-' && operator != '/' && operator != '*') {
            return false;
        }
        if (!parseOperand(&val, &vname, input)) {
            return false;
        }
        if (vname != '\0') {
            val = var[vname - CONVERT_L];
        }
        switch (operator) {
            case '-':
                if (!subtract(result, left, val)){
                    return false;
                }
                left = *result;
                break;
            case '+':
                if (!add(result, left, val)) {
                    return false;
                }
                left = *result;
                break;
            case '*':
                if (!multiply(result, left, val)) {
                    return false;
                }
                left = *result;
                break;
            case '/':
                if (!divide(result, left, val)) {
                    return false;
                }
                left = *result;
                break;
        }
    }
    if (operator == EOF) {
        ungetc(operator, input);
        return false;
    }
    return true;
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
    char vname = '\0';
    char ch = '\0';
    int varplace = 0;
    if (parseOperand(&value, &vname, input)) {
        if (vname != '\0') {
            varplace = vname - CONVERT_L;
            ch = skipWhitespace(input);
            if (ch == '=') {
                ch = skipWhitespace(input);
                ungetc(ch, input);
                if (parseOperand(&value, &vname, input)) {
                    ch = skipWhitespace(input);
                    if (ch == ';') {
                        var[varplace] = value;
                        return true;
                    } else {
                        ungetc(ch, input);
                        if (parseExpression(&result, value, input)) {
                            var[varplace] = result;
                            return true;
                        } else {
                            fprintf(output, "S%d: invalid\n", stmtNum);
                            while ((ch = skipWhitespace(input)) != ';' && ch != EOF) {
                                //parse through input
                            }
                            if (ch == EOF) {
                                ungetc(ch, input);
                            }
                            return false;
                        }
                    }
                } else {
                    fprintf(output, "S%d: invalid\n", stmtNum);
                    while ((ch = skipWhitespace(input)) != ';' && ch != EOF) {
                        //parse through input
                    }
                    if (ch == EOF) {
                        ungetc(ch, input);
                    }
                    return false;
                }
            } else {
                value = var[varplace];
                if (ch == ';') {
                    fprintf(output, "S%d: ", stmtNum);
                    printNumber(value, output);
                    fprintf(output, "\n"); 
                    return true;
                }
                ungetc(ch, input);
            }
        }
        ch = skipWhitespace(input);
        if (ch != '+' && ch != '-' && ch != '/' && ch != '*'  && ch != ';') {
            fprintf(output, "S%d: invalid\n", stmtNum);
            while ((ch = skipWhitespace(input)) != ';' && ch != EOF) {
                //parse through input
            }
            if (ch == EOF) {
                ungetc(ch, input);
            }
            return false;
        }
        ungetc(ch, input);
        if (parseExpression(&result, value, input)) {
            fprintf(output, "S%d: ", stmtNum);
            printNumber(result, output);
            fprintf(output, "\n");
            return true;
        } else {
            fprintf(output, "S%d: invalid\n", stmtNum);
            while ((ch = skipWhitespace(input)) != ';' && ch != EOF) {
                //parse through input
            }
            if (ch == EOF) {
                ungetc(ch, input);
            }
            return false;
        }

    } else {
        fprintf(output, "S%d: invalid\n", stmtNum);
        while ((ch = skipWhitespace(input)) != ';' && ch != EOF) {
            //parse through input
        }
        if (ch == EOF) {
            ungetc(ch, input);
        }
        return false;
    }
}

int main (int argc, char *argv[]) 
{
    if (argc > OUTPUT_ARG + 1) {
        usage();
    }
    FILE *fi;
    if ( ( fi = fopen( argv[INPUT_ARG], "r" ) ) == NULL ) {
        fprintf( stderr, "Can't open file: %s\n", argv[INPUT_ARG] );
        exit( EXIT_FAILURE );
    }

    FILE *fw;
    if (argc == OUTPUT_ARG + 1) {
        fw = fopen(argv[OUTPUT_ARG], "w");
    } else {
        fw = stdout;
    }
    
    int stmtNum = 1; 
    char ch;
    while ((ch = skipWhitespace(fi)) != EOF) {
        ungetc(ch, fi);
        parseStatement(stmtNum, fi, fw);
        stmtNum++;
    }

  fclose(fi);
  fclose(fw);
  return 0;
}