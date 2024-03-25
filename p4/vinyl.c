/**
* @file vinyl.c
* @author krvadla Kavya Vadla
* top-level component, containing main() and code to parse user commands.
*/

#include "inventory.h"
#include "input.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/** Number to initialize array*/
#define ARRAY_INITAL 15
/** Initial capacity of order*/
#define ORDER_CAPACITY 5
/** Max Number of parameters in a user command*/
#define PARAM_MAX 3
/** Max length for search parameter*/
#define SEARCH_MAX 15

/**
* An OrderItem has a field that points to a record in the inventory
* and also the number of copies the user would like to purchase
*/
typedef struct OrderItem {
    Record * rec;
    int copies;
} OrderItem;

/**
* An Order holds a list of records in sequence order, it has a field for the number of records held 
* and also a field for the capacity of an Order that can be resized but starts at 5
*/
typedef struct Order {
    int count, capacity;
    OrderItem **list;
} Order;

/**
* Compares two ints for the qsort function
* if a comes before b, -1 is returned 
* if a comes after b, 1 is returned
* if the two ints are equal, 0 is returned
* @param aptr a pointer to the first int as a void pointer
* @param bptr a pointer to the second int as a void pointer
* @return returns -1, 0, or 1 depending on how the ints should be sorted
*/
static int idComp(void const *aptr, void const *bptr)
{
    Record * const *a = aptr;
    Record * const *b = bptr;

    if ((*a)->id < (*b)->id) {
        return -1;
    } else if ((*a)->id > (*b)->id) {
        return 1;
    } 
    return 0;
}

/**
* Compares two strings for the qsort function
* if a comes before b, -1 is returned 
* if a comes after b, 1 is returned
* if the two strings are equal, 0 is returned
* @param aptr a pointer to the first string as a void pointer
* @param bptr a pointer to the second string as a void pointer
* @return returns -1, 0, or 1 depending on how the stringd should be sorted
*/
static int genreComp(void const *aptr, void const *bptr)
{
    Record * const *a = aptr;
    Record * const *b = bptr;

    if (strcmp((*a)->artist, (*b)->artist) < 0) {
        return -1;
    } else if (strcmp((*a)->artist, (*b)->artist) > 0) {
        return 1;
    } else {
        if (strcmp((*a)->title, (*b)->title) < 0) {
            return -1;
        } else if (strcmp((*a)->title, (*b)->title) > 0) {
            return 1;
        } else {
            if ((*a)->id < (*b)->id) {
                return -1;
            } else if ((*a)->id > (*b)->id) {
                return 1;
            }
        }
    }
    return 0;
}

/**
* A test function that returns true no matter what, 
* used to print all the records in the inventory 
* @param record pointer to a record that will be printed
* @param str pointer to a string, in this case NULL since all records will be printed
* @return returns true to print all records
*/
static bool testTrue(Record const *record, char const *str)
{
    return true;
}

/**
* A test function that returns true no matter what, 
* used to print all the records in the inventory or order
* @param record pointer to a record that will be printed
* @param str pointer to a string, in this case NULL since all records will be printed
* @return returns true to print all records
*/
static bool testTrueOrder(OrderItem  const *orderitem, char const *str)
{
    return true;
}

/**
* A test function that checks whether the string passed in matches the records genre, 
* used to print certain records in the inventory based on genre
* @param record pointer to a record that may or may not be printed
* @param str pointer to a string to check against the record genre
* @return returns true if str and genre are same, false if not
*/
static bool testGenre(Record const *record, char const *str) 
{
    if (strcmp(record->genre, str) == 0) {
        return true;
    }
    return false;
}

/**
* A test function that checks whether the string passed in is in the record's artist or title, 
* used to print certain records in the inventory based on search
* @param record pointer to a record that may or may not be printed
* @param str pointer to a string to check using search string
* @return returns true if strstr does not return null, false if returns null
*/
static bool testSearch(Record const *record, char const *artortit, char const *str) 
{
    char *check;
    if (strcmp(artortit, "artist") == 0) {
        if ((check = strstr(record->artist, str)) != NULL) {
            return true;
        } else {
            return false;
        }
    } else if (strcmp(artortit, "title") == 0) {
        if ((check = strstr(record->title, str)) != NULL) {
            return true;
        } else {
            return false;
        }
    }
    return false;
}

void listSearchRecords( Inventory *inventory, bool (*test)( Record const *record, char const *artortit, char const *str ), char const *artortit, char const *str )
{
    printf("%-3s %-30s %-30s %-12s %6s\n", "ID", "Artist", "Title", "Genre", "Copies");
    for (int i = 0; i < inventory->count; i++) {
        if (test(inventory->list[i], artortit, str)) {
            printf("%3d %-30s %-30s %-12s %6d\n", inventory->list[i]->id, inventory->list[i]->artist, inventory->list[i]->title, inventory->list[i]->genre, inventory->list[i]->copies);
        }
    }
}

/**
* This function prints all of the records in the order
* @param order inventory to print records from
* @param test function used to figure out which records to print
*/
static void listOrderRecords( Order *order, bool (*test)( OrderItem const *orderitem, char const *str ), char const *str )
{
    printf("%-3s %-30s %-30s %-12s %6s\n", "ID", "Artist", "Title", "Genre", "Copies");
    if (order->count != 0) {
        for (int i = 0; i < order->count; i++) {
            if (test(order->list[i], str)) {
                printf("%3d %-30s %-30s %-12s %6d\n", order->list[i]->rec->id, order->list[i]->rec->artist, order->list[i]->rec->title, order->list[i]->rec->genre, order->list[i]->copies);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf( stderr, "usage: vinyl record-file+\n");
        exit( EXIT_FAILURE );
    }

    Inventory *invent = makeInventory();
    Order *order = (Order *)malloc(sizeof(Order));
    order->count = 0;
    order->capacity = ORDER_CAPACITY;
    order->list = (OrderItem **)malloc(ORDER_CAPACITY * sizeof(OrderItem *));
    for (int i = 1; argv[i]; i++) {
        readRecords(argv[i], invent);
    }
    printf("cmd> ");
    char *command;
    while ((command = readLine(stdin)) != NULL && (strcmp(command, "quit")) != 0) {
        char user[ARRAY_INITAL];
        sscanf(command, "%s", user);
        if (strcmp(user, "list") == 0) {
            printf("%s\n", command);
            char genre[ARRAY_INITAL];
            char param[ARRAY_INITAL];
            int paramnum = sscanf(command, "%s %s %s", user, param, genre);
            if (paramnum == PARAM_MAX) {
                if (strcmp(param, "genre") != 0) {
                    printf("Invalid command\n");
                } else {
                    sortRecords(invent, genreComp);
                    listRecords(invent, testGenre, genre);
                }    
            } else if (paramnum == PARAM_MAX - 1) {
                if (strcmp(param, "order") != 0) {
                    printf("Invalid command\n");
                } else {
                    listOrderRecords(order, testTrueOrder, NULL);
                } 
            } else if (paramnum == 1) {
                sortRecords(invent, idComp);
                listRecords(invent, testTrue, NULL);
            }
            printf("\n");
        } else if (strcmp(user, "add") == 0) {
            printf("%s\n", command);
            int recid;
            int reccopy;
            int paramnum = sscanf(command, "%s %d %d", user, &recid, &reccopy); 
            if (paramnum != PARAM_MAX || reccopy < 0) {
                printf("Invalid command\n");
            } else {
                bool found = false;
                for (int i = 0; i < order->count; i++) {
                    if (order->list[i]->rec->id == recid) {
                        order->list[i]->copies += reccopy;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    for (int i = 0; i < invent->count; i++) {
                        if (invent->list[i]->id == recid) {
                            if (invent->list[i]->copies >= reccopy) {
                                Record *recptr = invent->list[i];
                                OrderItem *orditem = (OrderItem *)malloc(sizeof(OrderItem));
                                orditem->rec = recptr;
                                orditem->copies = reccopy;
                                order->list[order->count] = orditem;
                                order->count++;
                                found = true;
                                if (order->count >= order->capacity) {
                                    order->capacity *= 2;
                                    order->list = (OrderItem **)realloc(order->list, order->capacity * sizeof(OrderItem *));
                                }
                                break;
                                
                            }
                        }
                    }
                
                }
                
                if (!found) {
                    printf("Invalid command\n");
                }
            }
            printf("\n");
        } else if (strcmp(user, "remove") == 0) {
            printf("%s\n", command);
            int recid;
            int reccopy;
            int paramnum = sscanf(command, "%s %d %d", user, &recid, &reccopy); 
            if (paramnum != PARAM_MAX || reccopy < 0) {
                printf("Invalid command\n");
            } else {
                bool found = false;
                for (int i = 0; i < order->count; i++) {
                    if (order->list[i]->rec->id == recid) {
                        if (order->list[i]->copies >= reccopy) {
                            order->list[i]->copies -= reccopy;
                            found = true;
                            if (order->list[i]->copies == 0) {
                                free(order->list[i]);
                                for (int j = i; j < order->count - 1; j++) {
                                    order->list[j] = order->list[j + 1];
                                }
                                order->count--;
                            }
                        }
                    } 
                }
                if (!found) {
                    printf("Invalid command\n");
                }
            }
            printf("\n");
        } else if (strcmp(user, "checkout") == 0) {
            printf("%s\n", command);
            for (int i = 0; i < order->count; i++) {
                for (int j = 0; j < invent->count; j++) {
                    if (order->list[i]->rec->id == invent->list[j]->id) {
                        invent->list[j]->copies -= order->list[i]->copies;
                    }
                }
            }
            for (int i = 0; i < order->count; i++) {
                free(order->list[i]);
            }
            order->count = 0;
            free(order->list);
            order->list = (OrderItem **)malloc(ORDER_CAPACITY * sizeof(OrderItem *));
            printf("\n");
        } else if (strcmp(user, "search") == 0) {
            printf("%s\n", command);
            char artortit[ARRAY_INITAL];
            char search[ARRAY_INITAL + 1];
            bool invalid = false;
            int paramnum = sscanf(command, "%s %s %s", user, artortit, search); 
            if (paramnum != PARAM_MAX) {
                printf("Invalid command\n");
                invalid = true;
            } else if ((strcmp(artortit,"artist")) != 0 && (strcmp(artortit, "title")) != 0) {
                printf("Invalid command\n");
                invalid = true;
            } else if (search[0] != '\0') {
                for (int i = 0; search[i] != '\0'; i++) {
                    if (isspace(search[i]) != 0 ) {
                        printf("Invalid command\n");
                        invalid = true;
                        break;
                    }
                }
            }
            if (!invalid) {
                int len = 0;
                for (int i = 0; search[i] != '\0'; i++) {
                    len++;
                }
                if (len > SEARCH_MAX) {
                    printf("Invalid command\n");
                    invalid = true;
                }
            }
            if (!invalid) {
                sortRecords(invent, idComp);
                listSearchRecords(invent, testSearch, artortit, search);
            }
            printf("\n");
        } else {
            printf("Invalid command\n");
        }
        printf("cmd> ");
        free(command);
    }
    if (command != NULL) {
        if ((strcmp(command, "quit")) == 0) {
            printf("quit\n");
        }
    }
    freeInventory(invent);
    for (int i = 0; i < order->count; i++) {
        free(order->list[i]);
    }
    free(command);
    free(order->list);
    free(order);
    return 0;
}