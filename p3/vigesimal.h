/**
* @file vigesmal.h
* #author krvadla Kavya Vadla
* header file for vigesmal.c
*/

// The prototypes need the bool and FILE types.
#include <stdio.h>
#include <stdbool.h>

/**
* reads input from the file stream while skipping whitespace
* returns the first non whitespace character it finds
* @param input input filestream to read from
* @return the first non whitespace character 
*/
int skipWhitespace( FILE *input );

/**
* This function reads the next number from the given input stream in base 20. 
* If it detects errors in the input number, it returns false. If successful, 
* it returns true and stores the parsed value in the long variable pointed to by val
* @param val parsed value from input stream
* @param input file input stream to read from
* @return true if the input number is successfully read and false if it detects errors in the input number
*/
bool parseNumber( long *val, FILE *input );

/**
* This function prints the given val to the given stream in base 20
* @param val parsed value from input stream
* @param output file output stream to write to
*/
void printNumber( long val, FILE *output );