// A test program for removing nodes from the map
// as they become empty.

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

  int idx = 0;

  // Put a lot of key / value pairs in the map.
  char str[] = "a-b-c";
  for ( int a = 'a'; a <= 'z'; a++ )
    for ( int b = 'a'; b <= 'z'; b++ )
      for ( int c = 'a'; c <= 'z'; c++ ) {
        str[ 0 ] = a;
        str[ 2 ] = b;
        str[ 4 ] = c;
        char buffer[ 100 ];
        sprintf( buffer, "%d", idx );
        mapSet( m, str, parseInteger( buffer ) );
        idx += 1;
      }

  printf( "%d\n", mapSize( m ) );

  // Remove all those key/value pairs.
  for ( int a = 'a'; a <= 'z'; a++ )
    for ( int b = 'a'; b <= 'z'; b++ )
      for ( int c = 'a'; c <= 'z'; c++ ) {
        str[ 0 ] = a;
        str[ 2 ] = b;
        str[ 4 ] = c;
        mapRemove( m, str );
      }

  printf( "%d\n", mapSize( m ) );

  // Exit without freeing the map.
  // freeMap( m );

  return EXIT_SUCCESS;
}
