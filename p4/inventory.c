/**
* @file inventory.c
* @author krvadla Kavya Vadla
* reads and manages the records read in at startup
*/

#include "inventory.h"
#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** Initial capacity of inventory*/
#define INVENT_CAPACITY 5

Inventory *makeInventory()
{
    Inventory *invent = (Inventory *)malloc(sizeof(Inventory));
    invent->count = 0;
    invent->capacity = INVENT_CAPACITY;
    invent->list = (Record **)malloc(sizeof(Record *) * invent->capacity);
    return invent;
}

void freeInventory( Inventory *inventory ) 
{
    for (int i = 0; i < inventory->count; i++) {
        free(inventory->list[i]);
    }
    free(inventory->list);
    free(inventory);
}

void readRecords( char const *filename, Inventory *inventory ) 
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Can't open file: %s\n", filename);
        exit(EXIT_FAILURE);
    }
    char *str;
    while ((str = readLine(fp)) != NULL) {
        Record *rec = (Record*)malloc(sizeof(Record));
        if (sscanf(str, "%d %s %d", &rec->id, rec->genre, &rec->copies) != 3) {
            fprintf( stderr, "Invalid record file: %s\n", filename);
            exit( EXIT_FAILURE );
        }
        strcpy(rec->artist, readLine(fp));
        strcpy(rec->title, readLine(fp));
    
    
        if (rec->id < 0 || rec->copies < 0) {
            fprintf( stderr, "Invalid record file: %s\n", filename);
            exit( EXIT_FAILURE );
        }
        bool found = false;
        if (inventory->count > 0) {
            for (int i = 0; i < inventory->count; i++) {
                if (inventory->list[i]->id == rec->id) {
                    if ((strcmp(inventory->list[i]->genre, rec->genre)) == 0 && (strcmp(inventory->list[i]->artist, rec->artist)) == 0 && (strcmp(inventory->list[i]->title, rec->title)) == 0 ) {
                        inventory->list[i]->copies += rec->copies;
                        found = true;
                        break;
                    } else {
                        fprintf( stderr, "Invalid record file: %s\n", filename);
                        exit( EXIT_FAILURE );
                    }
                }
            }
        }
    
    
        if (!found) {
            inventory->list[inventory->count] = rec;
            inventory->count++;
        }
        if (inventory->count >= inventory->capacity) {
            inventory->capacity *= 2;
            inventory->list = (Record **)realloc(inventory->list, inventory->capacity * sizeof(Record *));
        }
    }
    
    fclose(fp);
}

void sortRecords( Inventory *inventory, int (* compare) (void const *va, void const *vb ))
{
    qsort(inventory->list, inventory->count, sizeof(inventory->list[0]), compare);
}

void listRecords( Inventory *inventory, bool (*test)( Record const *record, char const *str ), char const *str )
{
    printf("%-3s %-30s %-30s %-12s %6s\n", "ID", "Artist", "Title", "Genre", "Copies");
    for (int i = 0; i < inventory->count; i++) {
        if (test(inventory->list[i], str)) {
            printf("%3d %-30s %-30s %-12s %6d\n", inventory->list[i]->id, inventory->list[i]->artist, inventory->list[i]->title, inventory->list[i]->genre, inventory->list[i]->copies);
        }
    }
}
