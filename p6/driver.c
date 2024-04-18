/**
* @file driver.c 
* @author krvadla Kavya Vadla
* top-level, main component. Using the other components, it reads and processes commands from standard input,
* updates the map as needed and prints responses to user commands.
*/

#include "map.h"
#include "input.h"
#include "value.h"
#include <string.h>
#include <stdbool.h>

/** Initial size for array*/
#define INITIAL 30

/** Max number of parameters for a command */
#define PARAM_MAX 3
int main(int argc, char *argv[])
{
    Map *map = makeMap();
    printf("cmd> ");
    char *command;
    while ((command = readLine(stdin)) != NULL && (strcmp(command, "quit")) != 0) {
        char user[INITIAL];
        sscanf(command, "%s", user);
        if (strcmp(user, "set") == 0) {
            printf("%s\n", command);
            char key[INITIAL];
            char val[INITIAL];
            Value *v;
            int paramnum = sscanf(command, "%s %s %s", user, key, val);
            if (paramnum != PARAM_MAX) {
                printf("invalid\n");
            } else if ((v = mapGet(map, key)) != NULL) {
                Value *v2;
                if ((v2 = parseInteger(val)) != NULL ) {
                    mapSet(m, key, v2);
                } else if ((v2 = parseDouble(val)) != NULL) {
                    mapSet(m, key, v2);
                } else if ((v2 = parseString(val)) != NULL) {
                    mapSet(m, key, v2);
                } else {
                    printf("invalid\n");
                }
            }

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
            printf("invalid\n");
        }
        printf("cmd> ");
        free(command);
    }
}