// Simple test program for values containing an integer

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "value.h"

int main()
{
  // Try out the parse function for a few values.
  Value *v1 = parseInteger( "1" );
  assert( v1 != NULL );
  
  Value *v2 = parseInteger( "25" );
  assert( v2 != NULL );

  // Try out the toString() method
  char *s1 = v1->toString( v1 );
  assert( strcmp( s1, "1" ) == 0 );
  free( s1 );
    
  char *s2 = v2->toString( v2 );
  assert( strcmp( s2, "25" ) == 0 );
  free( s2 );
    
  // Try out the plus() method
  assert( v1->plus( v1, v2 ) );
  s1 = v1->toString( v1 );
  assert( strcmp( s1, "26" ) == 0 );
  free( s1 );
    
  // Free the integer objects.
  v1->destroy( v1 );
  v2->destroy( v2 );

  return EXIT_SUCCESS;
}
