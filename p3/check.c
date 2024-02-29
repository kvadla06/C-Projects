/**
* @file check.c
* @author krvadla Kavya Vadla
* check.c provides functions for performing the four basic arithmetic operations on signed long values, automatically checking for overflow or divide-by zero
*/

#include "check.h"
#include <stdbool.h>
#include <limits.h>

bool add( long *result, long a, long b )
{
    if ((b > 0 && a > LONG_MAX - b) || (b < 0 && a < LONG_MIN - b)) {
        return false;
    }

    *result = a + b;
    return true; 
}

bool subtract(long *result, long a, long b) 
{
    if ((b < 0 && a > LONG_MAX + b) || (b > 0 && a < LONG_MIN + b)) {
        return false; 
    }

    *result = a - b;
    return true;
}

bool multiply(long *result, long a, long b) 
{
    if (a > 0) {
        if (b > LONG_MAX / a || b < LONG_MIN / a) {
            return false; 
        }
    } else if (a < -1) {
        if (b > 0 && a < LONG_MIN / b || b < 0 && a < LONG_MAX / b) {
            return false; 
        }
    } else if (a == -1 && b == LONG_MIN) {
        return false; 
    }

    *result = a * b;
    return true; 
}

bool divide( long *result, long a, long b )
{
    if (b == 0) {
        return false;
    }

    if (a == LONG_MIN && b == -1) {
        return false;
    }

    *result = a / b;
    return true;
}