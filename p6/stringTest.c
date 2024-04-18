// Simple test program for values containing a string

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "value.h"

int main()
{
  // Try out the parse function for a few values.
  Value *v1 = parseString( "\"a\"" );
  assert( v1 != NULL );
  
  Value *v2 = parseString( "\"abcd\"" );
  assert( v2 != NULL );

  Value *v3 = parseString( "\"two words\"" );
  assert( v3 != NULL );

  Value *v4 = parseString( "  \"  extra spaces   \"   " );
  assert( v4 != NULL );

  Value *v5 = parseString( "\"\"" );
  assert( v5 != NULL );

  // This should fail.
  Value *v6 = parseString( "no-quotes" );
  assert( v6 == NULL );

  // This should also fail.
  v6 = parseString( "\"no-closing-quote" );
  assert( v6 == NULL );

  // Try out the toString() method
  char *s1 = v1->toString( v1 );
  assert( strcmp( s1, "\"a\"" ) == 0 );
  free( s1 );
    
  char *s2 = v2->toString( v2 );
  assert( strcmp( s2, "\"abcd\"" ) == 0 );
  free( s2 );
  
  char *s3 = v3->toString( v3 );
  assert( strcmp( s3, "\"two words\"" ) == 0 );
  free( s3 );
    
  char *s4 = v4->toString( v4 );
  assert( strcmp( s4, "\"  extra spaces   \"" ) == 0 );
  free( s4 );
    
  char *s5 = v5->toString( v5 );
  assert( strcmp( s5, "\"\"" ) == 0 );
  free( s5 );
    
  // Try out the plus() method
  assert( v1->plus( v1, v2 ) );
  s1 = v1->toString( v1 );
  assert( strcmp( s1, "\"aabcd\"" ) == 0 );
  free( s1 );
  
  assert( v1->plus( v1, v5 ) );
  s1 = v1->toString( v1 );
  assert( strcmp( s1, "\"aabcd\"" ) == 0 );
  free( s1 );
    
  assert( v3->plus( v3, v2 ) );
  s1 = v3->toString( v3 );
  assert( strcmp( s1, "\"two wordsabcd\"" ) == 0 );
  free( s1 );
    
  // Free the double objects.
  v1->destroy( v1 );
  v2->destroy( v2 );
  v3->destroy( v3 );
  v4->destroy( v4 );
  v5->destroy( v5 );

  return EXIT_SUCCESS;
}
