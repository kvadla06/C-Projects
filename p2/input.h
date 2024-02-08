/**
* @file input.h
* @author krvadla Kavya Vadla
* header file for input file that will read in the replacement strings
*/

#include "replace.h"

/**
 * reads in a word or phrase on a line and checks to make sure it is not over 24 characters 
 * or that it doesnt contain invalid characters
 * @param word the replacement string
*/
void readWord( char word[ FIELD_MAX + 1 ]);

/**
 * reads in line of input, making sure that it is not more than 100 characters
 * @param line line of input to be read from input file
 * @return returns true if line was successfully read with correct input and false if otherwise
 * 
*/
bool readLine( char line[ LINE_MAX + 1 ]);
