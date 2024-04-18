// Simple test program for values containing a double

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "value.h"

int main()
{
  // Try out the parse function for a few values.
  Value *v1 = parseDouble( "1.0" );
  assert( v1 != NULL );
  
  Value *v2 = parseDouble( "2.5" );
  assert( v2 != NULL );

  Value *v3 = parseDouble( "   1000.0001   " );
  assert( v3 != NULL );

  // This should fail.
  Value *v4 = parseDouble( "kdfsjfklsa" );
  assert( v4 == NULL );

  // This should also fail.
  v4 = parseDouble( "1.0 extra garbage" );
  assert( v4 == NULL );

  // Try out the toString() method
  char *s1 = v1->toString( v1 );
  assert( strcmp( s1, "1.000000" ) == 0 );
  free( s1 );
    
  char *s2 = v2->toString( v2 );
  assert( strcmp( s2, "2.500000" ) == 0 );
  free( s2 );
  
  char *s3 = v3->toString( v3 );
  assert( strcmp( s3, "1000.000100" ) == 0 );
  free( s3 );
    
  // Try out the plus() method
  assert( v2->plus( v2, v1 ) );
  s1 = v2->toString( v2 );
  assert( strcmp( s1, "3.500000" ) == 0 );
  free( s1 );
    
  assert( v3->plus( v3, v2 ) );
  s1 = v3->toString( v3 );
  assert( strcmp( s1, "1003.500100" ) == 0 );
  free( s1 );
    
  // This should fail, can't add a double and an integer.
  v4 = parseInteger( "5" );
  assert( v3->plus( v3, v4 ) == false );
  
  // Free the double objects.
  v1->destroy( v1 );
  v2->destroy( v2 );
  v3->destroy( v3 );
  v4->destroy( v4 );

  return EXIT_SUCCESS;
}
