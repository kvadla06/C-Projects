/**
* @file inventory.c
* @author krvadla Kavya Vadla
* reads and manages the records read in at startup
*/

#include "inventory.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/** Initial capacity of inventory*/
#define INVENT_CAPACITY 5

Inventory *makeInventory()
{
    Inventory invent = { .count = 0,
                         .capacity = INVENT_CAPACITY,
                         .list = (Record **)malloc(INVENT_CAPACITY * sizeof(Record *))};
    Inventory *invptr = &invent;
    return invptr;
}

void freeInventory( Inventory *inventory ) 
{
    for (int i = 0; i < inventory->count; i++) {
        free(inventory->list[i]);
    }
    free(inventory);
}

void readRecords( char const *filename, Inventory *inventory ) 
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Can't open file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    Record rec;
    if (fscanf(fp, "%d %s %d\n%[^\n]\n%[^\n]\n", &rec.id, rec.genre, &rec.copies, rec.artist, rec.title) != 5) {
        fprintf( stderr, "Invalid record file: %s\n", filename);
        exit( EXIT_FAILURE );
    }
    
    if (rec.id < 0 || rec.copies < 0) {
        fprintf( stderr, "Invalid record file: %s\n", filename);
        exit( EXIT_FAILURE );
    }

    Record *recptr = &rec;
    bool found = false;
    for (int i = inventory->count + 1; i >= 0; i--) {
        if (inventory->list[i]->id == rec.id) {
            if ((strcmp(inventory->list[i]->genre, rec.genre)) == 0 && (strcmp(inventory->list[i]->artist, rec.artist)) == 0 && (strcmp(inventory->list[i]->title, rec.title)) == 0 ) {
                inventory->list[i]->copies += rec.copies;
                found = true;
                break;
            } else {
                fprintf( stderr, "Invalid record file: %s\n", filename);
                exit( EXIT_FAILURE );
            }
        }
    }
    
    if (!found) {
        inventory->list[inventory->count] = recptr;
        inventory->count++;
    }

    if (inventory->count >= inventory->capacity) {
        inventory->capacity *= 2;
        inventory->list = (Record **)realloc(inventory->list, inventory->capacity * sizeof(Record *));
    }
    fclose(fp);
}

void sortRecords( Inventory *inventory, int (* compare) (void const *va, void const *vb ))
{
    qsort(inventory->list, inventory->count, sizeof(inventory->list[0]), compare);
}

void listRecords( Inventory *inventory, bool (*test)( Record const *record, char const *str ), char const *str )
{
    printf("%3s %-30s %-30s %-12s %6s\n", "ID", "Artist", "Title", "Genre", "Copies");
    for (int i = 0; i < inventory->count; i++) {
        if (test(inventory->list[i], str)) {
            printf("%3d %-30s %-30s %-12s %6d\n", inventory->list[i]->id, inventory->list[i]->artist, inventory->list[i]->title, inventory->list[i]->genre, inventory->list[i]->copies);
        }
    }
}
