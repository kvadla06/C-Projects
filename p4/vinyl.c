/**
* @file vinyl.c
* @author krvadla Kavya Vadla
* top-level component, containing main() and code to parse user commands.
*/

#include "inventory.h"
#include "input.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/** Number to initialize array*/
#define ARRAY_INITAL 10
/** Initial capacity of order*/
#define ORDER_CAPACITY 5
/** Max Number of parameters in a user command*/
#define PARAM_MAX 3

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
    Record const *a = aptr;
    Record const *b = bptr;

    if (*a.id < *b.id) {
        return -1;
    } else if (*a.id > *b.id) {
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
    Record const *a = aptr;
    Record const *b = bptr;

    if (strcmp(*a.artist, *b.artist) < 0) {
        return -1;
    } else if (strcmp(*a.artist, *b.artist) > 0) {
        return 1;
    } else {
        if (strcmp(*a.title, *b.title) < 0) {
            return -1;
        } else if (strcmp(*a.title, *b.title) > 0) {
            return 1;
        } else {
            if (*a.id < *b.id) {
                return -1;
            } else if (*a.id > *b.id) {
                return 1;
            }
        }
    }
    return 0;
}

/**
* A test function that returns true no matter what, 
* used to print all the records in the inventory or order
* @param record pointer to a record that will be printed
* @param str pointer to a string, in this case NULL since all records will be printed
* @return returns true to print all records
*/
static bool testTrue(Record const *record, char const *str)
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
    if (strcmp(record.genre, str) == 0) {
        return true;
    }
    return false;
}

int main(int argc, char *argv[]) {
    if (argc < 1) {
        fprintf( stderr, "usage: vinyl record-file+\n");
        exit( EXIT_FAILURE );
    }

    Inventory *invent = makeInventory();
    Order order = { .count = 0;
                    .capacity = ORDER_CAPACITY;
                    .list = (OrderItem **)malloc(ORDER_CAPACITY * sizeof(OrderItem *));
    }
    for (int i = 1; argv[i]; i++) {
        FILE *fp;
        if ( ( fp = fopen( argv[i], "r" ) ) == NULL ) {
            fprintf( stderr, "Can't open file: %s\n", argv[i] );
            exit( EXIT_FAILURE );
        } else {
            readRecords(fp, invent);
        }
    }
    printf("cmd> \n");
    char *command;
    while ((command = readLine()) != NULL|| (strcmp(command, "quit")) != 0) {
        char *user;
        sscanf(command, "%s", user);
        switch (user) {
            case "list":
                printf("list\n");
                char *genre;
                char *param;
                int paramnum = sscanf(command, "%s %s %s", user, param, genre);
                if (paramnum == PARAM_MAX) {
                    if (strcmp(param, "genre") != 0) {
                        printf("Invalid command\n");
                        break;
                    } else {
                        sortRecords(invent, genreComp);
                        listRecords(invent, testGenre, genre);
                    }    
                } else if (paramnum == PARAM_MAX - 1) {
                    if (strcmp(param, "order") != 0) {
                        printf("Invalid command\n");
                        break;
                    } else {
                        listRecords(order, testTrue, NULL);
                    } 
                } else if (paramnum == 1) {
                    sortRecords(invent, idComp);
                    listRecords(invent, testTrue, NULL);
                }
                break;
            case "add":
                printf("add\n");
                int recid;
                int reccopy;
                int paramnum = sscanf(command, "%s %d %d", user, recid, reccopy); 
                if (paramnum != PARAM_MAX || reccopy < 0) {
                    printf("Invalid command\n");
                    break;
                }
                bool found = false;
                for (int i = 0; i < *invent.count; i++) {
                    if (*invent.list[i].id == recid) {
                        if (*invent.list[i].copies >= reccopy) {
                            Record recptr = **invent.list[i]
                            OrderItem orditem = { .rec = recptr;
                                                  .copies = reccopy;
                            }
                            OrderItem *ordptr = orditem;
                            order[order.count] = ordptr;
                            order.count++;
                            found = true;
                            if (order.count >= order.capacity) {
                                order.capacity *= 2;
                                order.list = (OrderItem *)realloc(order.list, order.capacity * sizeof(OrderItem *));
                            }
                        }
                    }
                }
                if (!found) {
                    printf("Invalid command\n");
                    break;
                }
                break;
            case "remove":
                printf("remove\n");
                int recid;
                int reccopy;
                int paramnum = sscanf(command, "%s %d %d", user, recid, reccopy); 
                if (paramnum != PARAM_MAX || reccopy < 0) {
                    printf("Invalid command\n");
                    break;
                }
                bool found = false;
                for (int i = 0; i < ordersize; i++) {
                    if (order[i].*rec.id == recid) {
                        if (order[i].copies >= reccopy) {
                            order[i].copies -= reccopy;
                            found = true;
                            if (order[i].copies == 0) {
                                order[i] = NULL;
                                for (int j = i; j < order.count - 1; j++) {
                                    order[j] = order[j + 1];
                                }
                                order.count--;
                            }
                        }
                    }
                }
                if (!found) {
                    printf("Invalid command\n");
                    break;
                }
                break;
            case "checkout":
                printf("checkout\n");
                for (int i = 0; i < order.count; i++) {
                    for (int j = 0; j < *invent.count; j++) {
                        if (order[i].*rec.id == *invent.list[j].id) {
                            *invent.list[j].copies -= order[i].copies;
                            break;
                        }
                    }
                }
                for (int i = 0; i < order.count; i++) {
                    free(order[i]);
                }
                order.list = (OrderItem **)malloc(ORDER_CAPACITY * sizeof(OrderItem *));
            default:
                printf("Invalid command\n");
        }
        printf("cmd> \n");
    }
    if ((strcmp(command, "quit")) == 0) {
        printf("quit\n");
    }
    freeInventory();
    for (int i = 0; i < order.count; i++) {
        free(order[i]);
    }
    free(order);
    return 0;
}