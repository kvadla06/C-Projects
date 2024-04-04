/**
* @file hash.c
* @author krvadla Kavya Vadla
* main file of the 256hash program
*/

#include "sha256.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    FILE *file = stdin;
    SHAState *state = makeState();
    byte input[BLOCK_SIZE];
    int read;
    if (argc > 2) {
        fprintf( stderr, "usage: hash [input_file]\n");
        exit( EXIT_FAILURE );
    }
    if (argc > 1) {
        file = fopen(argv[1], "rb");
        if (!file) {
            fprintf(stderr, "%s: No such file or directory\n", argv[1]);
            return 1;
        }
    }

    while ((read = fread(input, 1, BLOCK_SIZE, file)) > 0) {
        update(state, input, read);
    }

    word hash[HASH_WORDS];
    digest(state, hash);

    for (int i = 0; i < HASH_WORDS; i++) {
        printf("%08x", hash[i]);
    }
    printf("\n");

    freeState(state);
    if (file != stdin) {
        fclose(file);
    }

    return 0;
}