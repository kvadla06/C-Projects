// Simple test program the map component.

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "value.h"
#include "map.h"

int main()
{
  // make an empty map.
  Map *m = makeMap();
  assert( mapSize( m ) == 0 );

  // Try putting a key with an integer value in the map.
  mapSet( m, "x", parseInteger( "25" ) );
  Value *v = mapGet( m, "x" );
  assert( v != NULL );
  
  char *s = v->toString( v );
  assert( strcmp( s, "25" ) == 0 );
  free( s );
  assert( mapSize( m ) == 1 );

  // Put in a value with a different key.
  mapSet( m, "A", parseInteger( "75" ) );
  v = mapGet( m, "A" );
  assert( v != NULL );
  
  s = v->toString( v );
  assert( strcmp( s, "75" ) == 0 );
  free( s );
  
  // Put in a value with a two-character key
  mapSet( m, "ab", parseInteger( "999" ) );
  v = mapGet( m, "ab" );
  assert( v != NULL );
  
  s = v->toString( v );
  assert( strcmp( s, "999" ) == 0 );
  free( s );
  
  // Put in a value with a ten-character key
  mapSet( m, "challenges", parseInteger( "-1" ) );
  assert( mapSize( m ) == 4 );
  v = mapGet( m, "challenges" );
  assert( v != NULL );
  
  s = v->toString( v );
  assert( strcmp( s, "-1" ) == 0 );
  free( s );
  
  // Replace the value at a key
  mapSet( m, "A", parseInteger( "76" ) );
  v = mapGet( m, "A" );
  assert( v != NULL );
  assert( mapSize( m ) == 4 );
  
  s = v->toString( v );
  assert( strcmp( s, "76" ) == 0 );
  free( s );
  
  // Remove the value at a key
  assert( mapRemove( m, "x" ) );
  assert( mapSize( m ) == 3 );
  v = mapGet( m, "x" );
  assert( v == NULL );

  // Remove the value at a two-character key
  assert( mapRemove( m, "ab" ) );
  v = mapGet( m, "ab" );
  assert( v == NULL );

  // Try to remove a value that's not in the map.
  assert( mapRemove( m, "wxyz" ) == false );

  // Free memory for the map.
  freeMap( m );

  return EXIT_SUCCESS;
}
