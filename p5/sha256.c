/**
* @file @sha256.c
* @author krvadla Kavya Vadla
* This is where the sha256 algorithm is implemented. 
* It’s broken up into several small functions for the various steps, so these can be tested and debugged independently.
*/

#include "sha256.h"
#include <stdlib.h>
#include <string.h>

/** Number of bits in unsigned int */
#define NUM_BITS_UINT 32

#define WORD_SIZE 32

word rotate(word val, int bits) {
    word result = (val >> bits) | (val << (NUM_BITS_UINT - bits));
    return result;
}

word Sigma0(word a) {
    return rotate(a, 2) ^ rotate(a, 13) ^ rotate(a, 22);
}

word Sigma1(word e) {
    return rotate(e, 6) ^ rotate(e, 11) ^ rotate(e, 25);
}

word ChFunction(word e, word f, word g) {
    return (e & f) ^ (~e & g);
}

word MaFunction(word a, word b, word c) {
    word ab = a & b;
    word ac = a & c;
    word bc = b & c;
    word result = ab ^ ac ^ bc;

    return result;
}

SHAState *makeState() {
  SHAState *state = malloc(sizeof(SHAState));

  if (state == NULL) {
    return NULL;
  }

  for (int i = 0; i < HASH_WORDS; ++i) {
    state->h[i] = initial_h[i];
  }

  state->pcount = 0;

  return state;
}

void freeState(SHAState *state) {
    state->total = 0;
    if (state != NULL) {
        free(state);
    }
}

void extendMessage(byte const pending[BLOCK_SIZE], word w[BLOCK_SIZE]) {
    for (int i = 0; i < 16; i++) {
        w[i] = (pending[i * (BBITS/2)] << (BBITS*3)) | (pending[i * (BBITS/2) + 1] << 16) |
                (pending[i * (BBITS/2) + 2] << 8) | pending[i * (BBITS/2) + 3];
    }

    for (int i = 16; i < BLOCK_SIZE; i++) {
        word s0 = rotate(w[i - 15], 7) ^ rotate(w[i - 15], 18) ^
                   (w[i - 15] >> 3);
        word s1 = rotate(w[i - 2], 17) ^ rotate(w[i - 2], 19) ^
                   (w[i - 2] >> 10);
        w[i] = w[i - 16] + s0 + w[i - 7] + s1;
    }
}

void compression(SHAState *state) {
    word w[BLOCK_SIZE];
    extendMessage(state->pending, w);

    word a, b, c, d, e, f, g, h;
    int ind = 0;
    a = state->h[ind];
    ind++;
    b = state->h[ind];
    ind++;
    c = state->h[ind];
    ind++;
    d = state->h[ind];
    ind++;
    e = state->h[ind];
    ind++;
    f = state->h[ind];
    ind++;
    g = state->h[ind];
    ind++;
    h = state->h[ind];
    ind = 0;

    for (int i = 0; i < 64; i++) {
        word t1, t2;
        t1 = h + Sigma1(e) + ChFunction(e, f, g) + constant_k[i] + w[i];
        t2 = Sigma0(a) + MaFunction(a, b, c);
        h = g;
        g = f;
        f = e;
        e = d + t1;
        d = c;
        c = b;
        b = a;
        a = t1 + t2;
    }

    state->h[ind] += a;
    ind++;
    state->h[ind] += b;
    ind++;
    state->h[ind] += c;
    ind++;
    state->h[ind] += d;
    ind++;
    state->h[ind] += e;
    ind++;
    state->h[ind] += f;
    ind++;
    state->h[ind] += g;
    ind++;
    state->h[ind] += h;
}

void update( SHAState *state, const byte data[], int len ) {
    int i = 0;
    state->total += len;
    while( i < len ) {
        int bytesToAdd = BLOCK_SIZE - state->pcount;

        if( bytesToAdd > len - i ) {
            bytesToAdd = len - i;
        }

        memcpy( state->pending + state->pcount, data + i, bytesToAdd );
        state->pcount += bytesToAdd;
        
       

        if( state->pcount == BLOCK_SIZE ) {
            compression( state );
            state->pcount = 0;
        }

        i += bytesToAdd;
    }
}

void digest(SHAState *state, word hash[HASH_WORDS]) {
    int index = (state->pcount) % BLOCK_SIZE;
    if (index < BLOCK_SIZE - BBITS) {
        state->pending[state->pcount++] = 0x80;
        while (state->pcount < BLOCK_SIZE - BBITS) {
            state->pending[state->pcount++] = 0;
        }
    } else {
        state->pending[state->pcount++] = 0x80;
        while (state->pcount < BLOCK_SIZE) {
            state->pending[state->pcount++] = 0;
        }
        compression(state);
        memset(state->pending, 0, BLOCK_SIZE - BBITS);
    }

    // Write the total length of the input in bits
    word64 total_length = state->total * BBITS;
    byte *length_bytes = (byte *)&total_length;
    for (int i = 0; i < BBITS; i++) {
        state->pending[BLOCK_SIZE - BBITS + i] = length_bytes[BBITS - 1 - i];
    }
    compression(state);

    // Copy the final hash value to the given hash[] array
    for (int i = 0; i < HASH_WORDS; i++) {
        hash[i] = state->h[i];
    }
}
