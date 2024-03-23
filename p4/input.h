/**
* @file input.h
* @author krvadla Kavya Vadla
* header file for input file that will read a line from the given input stream
*/

#include <stdio.h>

/**
* reads a single line of input from the given input stream (stdin or a file) and returns it as a string inside a block of dynamically allocated memory
* @param fp file to read from 
* @return the line of string from the input file
*/
char *readLine( FILE *fp );