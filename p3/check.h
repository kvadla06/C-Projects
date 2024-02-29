/**
* @file check.h
* @author krvadla Kavya Vadla
* header file for check.c
*/

// The function prototypes need the bool type.
#include <stdbool.h>

/**
* checks to see if adding the long values a and b would overflow
* if overflow is detected, false is returned, otherwise the result is calculated
* and stored in the variable pointed to by the result pointer and true is returned
* @param result result of adding long a and long b
* @param a value 1 to add
* @param b value 2 to add
* @return returns true if values can be added, false if there is an overflow
*/
bool add( long *result, long a, long b );

/**
* checks to see if subtracting the long values a and b would overflow
* if overflow is detected, false is returned, otherwise the result is calculated
* and stored in the variable pointed to by the result pointer and true is returned
* @param result result of subtracting long a and long b
* @param a value 1 to subtract
* @param b value 2 to subtract
* @return returns true if values can be subtracted, false if there is an overflow
*/
bool subtract( long *result, long a, long b );

/**
* checks to see if multiplying the long values a and b would overflow
* if overflow is detected, false is returned, otherwise the result is calculated
* and stored in the variable pointed to by the result pointer and true is returned
* @param result result of multiplying long a and long b
* @param a value 1 to multiply
* @param b value 2 to multiply
* @return returns true if values can be multiplied, false if there is an overflow
*/
bool multiply( long *result, long a, long b );

/**
* checks to see if dividing the long values a and b would overflow or would cause a divide by zero
* if overflow is detected, false is returned, otherwise the result is calculated
* and stored in the variable pointed to by the result pointer and true is returned
* @param result result of dividing long a and long b
* @param a value 1 to divide
* @param b value 2 to divide
* @return returns true if values can be divided, false if there is an overflow or a divide by zero
*/
bool divide( long *result, long a, long b );