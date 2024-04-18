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
#include <stdlib.h>

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
            char buffer[ 2 ];
            Value *v;
            int paramnum = sscanf(command, "%s %s %s%1s", user, key, val, buffer);
            bool invalid = false;
            for (int i = 0; i < strlen(key); i++) {
                if (key[i] < '!' || key[i] > '~' ) {
                    invalid = true;
                    break;
                }
            }
            if (invalid) {
                printf("invalid\n");
            } else {
                if (paramnum != PARAM_MAX) {
                    printf("invalid\n");
                } else if ((v = mapGet(map, key)) != NULL) {
                    Value *v2;
                    if ((v2 = parseInteger(val)) != NULL ) {
                        v->destroy(v);
                        mapSet(map, key, v2);
                    } else if ((v2 = parseDouble(val)) != NULL) {
                        mapSet(map, key, v2);
                    } else if ((v2 = parseString(val)) != NULL) {
                        mapSet(map, key, v2);
                    } 
                } else if (v == NULL) {
                    if ((v = parseInteger(val)) != NULL ) {
                        mapSet(map, key, v);
                    } else if ((v = parseDouble(val)) != NULL) {
                        mapSet(map, key, v);
                    } else if ((v = parseString(val)) != NULL) {
                        mapSet(map, key, v);
                    } else {
                        printf("invalid\n");
                   }
                }
            }
            printf("\n");
        } else if (strcmp(user, "get") == 0) {
            printf("%s\n", command);
            char key[INITIAL];
            char buffer[ 2 ];
            Value *v;
            int paramnum = sscanf(command, "%s %s%1s", user, key, buffer);
            if (paramnum != (PARAM_MAX - 1)) {
                printf("invalid\n");
            } else if ((v = mapGet(map, key)) == NULL) {
                printf("invalid\n");
            } else if (v != NULL) {
                char *str = v->toString(v);
                printf("%s\n", str);
                free(str);
            }
            printf("\n");
        } else if (strcmp(user, "remove") == 0) {
            printf("%s\n", command);
            char key[INITIAL];
            char buffer[ 2 ];
            Value *v;
            int paramnum = sscanf(command, "%s %s%1s", user, key, buffer);
            if (paramnum != (PARAM_MAX - 1)) {
                printf("invalid\n");
            } else if ((v = mapGet(map, key)) == NULL) {
                printf("invalid\n");
            } else if (v != NULL) {
                mapRemove(map, key);
            }
            printf("\n");
        } else if (strcmp(user, "plus") == 0) {
            printf("%s\n", command);
            char key[INITIAL];
            char val[INITIAL];
            char buffer[ 2 ];
            Value *v;
            Value *v2;
            int paramnum = sscanf(command, "%s %s %s%1s", user, key, val, buffer);
            
            if ((v = parseInteger(val)) == NULL ) {
                if ((v = parseDouble(val)) == NULL) {
                    if ((v = parseString(val)) == NULL) {
                    }
                }
            }
            if ((v2 = mapGet(map, key)) == NULL) {
                printf("invalid\n");
            }
            if (paramnum != PARAM_MAX) {
                printf("invalid\n");
            } else if (!v2->plus(v2, v)) {
                printf("invalid\n");
            }
            v->destroy(v);
            printf("\n");
        } else if (strcmp(user, "size") == 0) {
            printf("%s\n", command);
            char buffer[ 2 ];
            int paramnum = sscanf(command, "%s%1s", user, buffer); 
            if (paramnum != 1) {
                printf("invalid\n");
            } else {
                int size = mapSize(map);
                printf("%d\n", size);
            }
            printf("\n");
        } else {
            printf("invalid\n");
        }
        printf("cmd> ");
        free(command);
    }
    if (command != NULL) {
        if ((strcmp(command, "quit")) == 0) {
            printf("quit\n");
        }
    }
    free(command);
    freeMap(map);
    return 0;
}