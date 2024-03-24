/**
* @file inventory.h
* @author krvadla Kavya Vadla
* the header file of inventory.c that reads and manages the records read in at startup
*/

#include <stdbool.h>
/**Initializing value for genre*/
#define GENRE_INITIAL 12
/**Initializing value for title and artist*/
#define TITLEART_INITIAL 30
/**
* A Record of music will have a field for its id number, number of copies, genre, title, and artist
*/
typedef struct Record {
    int id, copies;
    char genre[GENRE_INITIAL];
    char title[TITLEART_INITIAL];
    char artist[TITLEART_INITIAL];
} Record;

/**
* An Inventory holds a list of records in sorted order, it has a field for the number of records held 
* and also a field for the capacity of an Inventory that can be resized but starts at 5
*/
typedef struct Inventory {
    int count, capacity;
    Record **list;
} Inventory;

/**
* This function dynamically allocates storage for the Inventory, initializes its fields (to store a resizable array) and returns a pointer to the new Inventory.
* @return a pointer to the new Inventory
*/
Inventory *makeInventory();

/**
* This function frees the memory used to store the given Inventory, 
* including freeing space for all the Records, 
* freeing the resizable array of pointers and freeing space for the Inventory struct itself.
* @param inventory inventory to free memory from
*/
void freeInventory( Inventory *inventory );

/**
* This function reads all the records from a record file with the given name. 
* It makes an instance of the Record struct for a record in the file and stores a pointer to that Record in the resizable array in inventory 
* or updates the number of copies of a record with the same id that is already stored in the inventory.
* @param filename record file to read from 
* @param inventory inventory to store record in
*/
void readRecords( char const *filename, Inventory *inventory );

/**
* This function sorts the records in the given inventory.
* @param inventory inventory to sort 
* @param compare comparison function
*/
void sortRecords( Inventory *inventory, int (* compare) (void const *va, void const *vb ));

/**
* This function prints all or some of the records in the inventory
* @param inventory inventory to print records from
* @param test function used to figure out which records to print
*/
void listRecords( Inventory *inventory, bool (*test)( Record const *record, char const *str ), char const *str );

