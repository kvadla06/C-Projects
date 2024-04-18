/**
* @file value.c
* @author krvadla Kavya Vadla 
* Defines the struct called Value. It’s used to represent integer, floating-point and string values.
* This helps to parse user input and it’s part of the map representation.
*/

#include "value.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/** Type used to represent a subclass of Value that holds an integer. */
typedef struct {
  // Superclass fields.
  char *(*toString)( Value const *v );
  bool (*plus)( Value *v, Value const *x );
  void (*destroy)( Value *v );

  // Subclass fields.
  int val;
} IntegerValue;

/** Type used to represent a subclass of Value that holds an double. */
typedef struct {
  // Superclass fields.
  char *(*toString)( Value const *v );
  bool (*plus)( Value *v, Value const *x );
  void (*destroy)( Value *v );

  // Subclass fields.
  double val;
} DoubleValue;

/** Type used to represent a subclass of Value that holds an string. */
typedef struct {
  // Superclass fields.
  char *(*toString)( Value const *v );
  bool (*plus)( Value *v, Value const *x );
  void (*destroy)( Value *v );

  // Subclass fields.
  char *val;
} StringValue;

/** Maximum length of a 32-bit integer as a string. */
#define INTEGER_LENGTH 11

// toString method for integers
static char *integerToString( Value const *v )
{
  // Get v as a pointer to the subclass struct.
  IntegerValue *this = (IntegerValue *) v;

  // Convert to a dynamically allocated string.
  char *str = (char *) malloc( INTEGER_LENGTH + 1 );
  sprintf( str, "%d", this->val );
  return str;
}

// Plus method for integers.
static bool integerPlus( Value *v, Value const *x )
{
  // We can use a function pointer to make sure x is also an
  // integrer.
  if ( x->toString != integerToString )
    return false;
  
  // Get the parameters as IntegerValue poitners.
  IntegerValue *this = (IntegerValue *) v;
  IntegerValue *that = (IntegerValue *) x;

  // Add the value in x to v.
  this->val += that->val;
  return true;
}

// destroy method for integers
static void integerDestroy( Value *v )
{
  // All the memory for an integer is in one big block.
  free( v );
}

Value *parseInteger( char const *str )
{
  // Try to parse an integer from str.  The buffer is to make sure
  // there's no extra, non-space characters after the integer value.
  int ival;
  char buffer[ 2 ];

  if ( sscanf( str, "%d%1s", &ival, buffer ) != 1 )
    return NULL;

  // Make a new instance of an integer value.
  IntegerValue *v = (IntegerValue *) malloc( sizeof( IntegerValue ) );
  v->toString = integerToString;
  v->plus = integerPlus;
  v->destroy = integerDestroy;
  v->val = ival;

  // Return as a pointer to the superclass.
  return (Value *)v;
}

/** This is the maximum number of characters I could get from a double value,
    printed with %f. */
#define DOUBLE_LENGTH 317

// toString method for doubles
char *doubleToString( Value const *v )
{
  // Get v as a pointer to the subclass struct.
  DoubleValue *this = (DoubleValue *) v;

  // Convert to a dynamically allocated string.
  char *str = (char *) malloc( DOUBLE_LENGTH + 1 );
  sprintf( str, "%lf", this->val );
  return str;
}

// Plus method for doubles.
bool doublePlus( Value *v, Value const *x )
{
  if ( x->toString != doubleToString )
    return false;
  
  DoubleValue *this = (DoubleValue *) v;
  DoubleValue *that = (DoubleValue *) x;

  this->val += that->val;
  return true;
}

// destroy method for doubles
void doubleDestroy( Value *v )
{
  free( v );
}

Value *parseDouble( char const *str )
{
  double dval;
  char buffer[ 2 ];

  if ( sscanf( str, "%lf%1s", &dval, buffer ) != 1 ) {
    return NULL;
  }

  DoubleValue *v = (DoubleValue *) malloc( sizeof( DoubleValue ) );
  v->toString = doubleToString;
  v->plus = doublePlus;
  v->destroy = doubleDestroy;
  v->val = dval;

  return (Value *)v;
}

// toString method for string
char *stringToString( Value const *v )
{
  // Get v as a pointer to the subclass struct.
  StringValue *this = (StringValue *) v;

  char *str = (char *) malloc( (DOUBLE_LENGTH + 1) * sizeof(char));
  strcpy(str, "\"");
  strcat(str, this->val);
  strcat(str, "\"\0");
  return str;
}

// Plus method for string.
bool stringPlus( Value *v, Value const *x )
{
  
  
  StringValue *this = (StringValue *) v;
  if ( x->toString != stringToString ){
    char *str = x->toString(x);
    char str2[DOUBLE_LENGTH]; 
    strcpy(str2, this->val);
    strcat(str2, str);
    strcpy(this->val, str2);
    free(str);
  } else {
    StringValue *that = (StringValue *) x;
    char str[DOUBLE_LENGTH];
    strcpy(str, this->val);
    strcat(str, that->val);
    strcpy(this->val, str);
  }
  
  return true;
}

// destroy method for strings
void stringDestroy( Value *v )
{
    StringValue *this = (StringValue *) v;
    free(this->val);
    free( this );
}

Value *parseString(const char *str) {
    while (isspace(*str)) {
        str++;
    }

    if (*str != '\"') {
        return NULL;
    }
    str++;

    const char *end = strchr(str, '\"');
    if (end == NULL) {
        return NULL;
    }
    str--;
    size_t len = end - str;
    str++;
    char *value = (char *) malloc((len + 1) * sizeof(char));

    memcpy(value, str, len);
    value[len - 1] = '\0';

    StringValue *v = (StringValue *) malloc(sizeof(StringValue));
    v->toString = stringToString;
    v->plus = stringPlus;
    v->destroy = stringDestroy;
    v->val = (char *)malloc((DOUBLE_LENGTH + 1) * sizeof(char));
    strcpy(v->val, value);
    free(value);
    return (Value *)v;
}
