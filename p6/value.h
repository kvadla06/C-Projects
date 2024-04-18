/**
* @file value.h
* @author krvadla Kavya Vadla
* header file for value.c
*/

#ifndef VALUE_H
#define VALUE_H

#include <stdbool.h>

/** Give a short name to the Value struct defined below. */
typedef struct ValueStruct Value;

/** Abstract type used to represent an arbitrary value. All Values
    support four basic operations. */
struct ValueStruct {
  /** Convert the given value to a dynamically allocated string.
      @param v Pointer to the value object to string-ify.
      @return dynamically allocated strign representation for v. */
  char *(*toString)( Value const *v );
  
  /** Subclass-specific behavior performing a += operation, adding
      two different values of the same type.
      @param v Pointer to the value we're modifying (adding to).
      @param x Pointer to the value we're adding to v.
      @return true if the types of v and x permit addition. */
  bool (*plus)( Value *v, Value const *x );
  
  /** Free any memory used to store this value.
      @param v Pointer to the value object to free. */
  void (*destroy)( Value *v );
};

/** Parse the given strign as an integer and create a dynamically allocated
    instance of Value for it.
    @param str string to parse as an integer.
    @return new value or NULL if str can't be parsed as an integer. */
Value *parseInteger( char const *str );

/** Parse the given string as a double and create a dynamically allocated
    instance of Value for it.
    @param str string to parse as an integer.
    @return new value or NULL if str can't be parsed as an double. */
Value *parseDouble( char const *str );

/** Returns the given double as dynamically allocated string
    @param v value to turn to string
    @return string with double */
char *doubleToString( Value const *v );

/** Adds the user inputted double value to the original double value
    @param v value to add to
    @param x value to add
    @return true if values were successfully added, false if not */
bool doublePlus( Value *v, Value const *x );

/** Frees the double value when done
    @param v value to destroy */
void doubleDestroy( Value *v );

/** Parse the given string as a string without quotes and create a dynamically allocated
    instance of Value for it.
    @param str string to parse as an string.
    @return new value or NULL if str can't be parsed as a string. */
Value *parseString( char const *str );

/** Returns the given string as dynamically allocated string with quotes
    @param v value to turn to string
    @return string */
char *stringToString( Value const *v );

/** Adds the user inputted string value to the original string value
    @param v value to add to
    @param x value to add
    @return true if values were successfully added, false if not */
bool stringPlus( Value *v, Value const *x );

/** Frees the string value when done
    @param v value to destroy */
void stringDestroy( Value *v );
#endif
