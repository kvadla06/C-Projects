/**
* @file sha256.h 
* @author krvadla Kavya Vadla
* Header file for sha256.c
*/

#ifndef SHA256_H
#define SHA256_H

#include "sha256constants.h"

/** Type used to represent a byte. */
typedef unsigned char byte;

/** Type used to represent a 64-bit value. */
typedef unsigned long word64;

/** Number of bits in a byte. */
#define BBITS 8

/** Size of an input block in bytes. */
#define BLOCK_SIZE 64

/** Size of the hash, in words. */
#define HASH_WORDS 8

/** State of the SHA256 algorithm, including bytes of input data
    waiting to be hashed. */
typedef struct {
  /** Input data not yet hashed. */
  byte pending[ BLOCK_SIZE ];

  /** Number of byes currently in the pending array. */
  int pcount;
  
  /** Number of bytes that have been read in total*/
  int total;

  /** Current hash value. */
  word h[ HASH_WORDS ];
} SHAState;

/**
* This function rotates the given val right by the given number of bits and returns the result.
* @param val given value
* @param bits number of values to rotate the value by
* @return returned value that has been rotated 
*/
word rotate( word val, int bits );

/**
* This function computes the Σ0() function described in the sha256 algorithm.
* @param a word parameter
* @return word after computing the function
*/
word Sigma0( word a );

/**
* This function computes the Σ1() function described in the sha256 algorithm.
* @param a word parameter
* @return word after computing the function
*/
word Sigma1( word a );

/**
* This function computes the Ch() function described in the sha256 algorithm.
* @param e word parameter
* @param f word parameter
* @param g word parameter
* @return word after computing the function
*/
word ChFunction( word e, word f, word g );

/**
* This function computes the Ma() function described in the sha256 algorithm.
* @param a word parameter
* @param b word parameter
* @param c word parameter
* @return word after computing the function
*/
word MaFunction( word a, word b, word c );

/**
* This function extends the 64-byte block given in the pending array and stores the 64-word result in the w[] array.
* @param pending the 64-byte block to be extended
* @param w array to be stored to 
*/
void extendMessage( byte const pending[ BLOCK_SIZE ], word w[ BLOCK_SIZE ] );

/**
* This function performs the compression() operation for the SHA256 hash. 
* It processes a 64 byte blocks in the pending array of state, updating the h[] values in state. 
* This function is for internal use by the sha256 component. It is called by update() as it completes 64-byte blocks for processing.
* At the end of the input, it is called once or twice by the digest() function as it adds padding to the end of the input.
* @param state state of hash
*/
void compression( SHAState *state );

/**
* This function allocates an instance of SHAState on the heap and initializes its fields in preparation for processing an input file.
* In particular, the values of the h[] array should be initialized to match the initial_h[] array from sha256constants 
* and the pending array and length fields should show that no bytes are waiting to be processed.
*/
SHAState *makeState();

/**
* This function is called when a SHAState struct is no longer needed. It frees all the resources used by the state.
* @param state state to be freed
*/
void freeState( SHAState *state );

/**
* This function is called when new input data is available to be processed. 
* The input data is given as an array of bytes in the data array, with the len parameter indicating how many bytes are in the array. 
* This function can be called with any amount of data from the input, possibly more than 64 bytes or less. 
* This function collects input data into 64-byte blocks and processes each block via the compress function. 
* There may be leftover bytes after the last 64-byte block is processed. These are left in the pending array to be processed in a subsequent call to update() or digest().
* @param state struct to be updated
* @param data data to process
* @param len amt of bytes in array
*/
void update( SHAState *state, const byte data[], int len );

/** 
* This is called once, after all data has been read from the input and processed by the update() function.
* This adds padding to the input and processes the last block or two of the input and copies the final hash value to the given hash[] array.
* @param state hash value to be copied
*/

void digest( SHAState *state, word hash[ HASH_WORDS ] );





#endif
