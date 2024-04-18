#include "map.h"
#include <stdlib.h>
#include <string.h>

#include "value.h"

/** Lowest-numbered symbol ina  key. */
#define FIRST_SYM '!'

/** Number of possible symbols in a key. */
#define SYM_COUNT ( '~' - '!' + 1 )

/** Short name for the node used to build this tree. */
typedef struct NodeStruct Node;

/** Node in the trie data structure. */
struct NodeStruct {
  /** If the substring to the root of the tree up to this node is a
      key, this is the value that goes with it. */
  Value *val;
  
  /** Array of pointers to child nodes. */
  Node *child[ SYM_COUNT ];
};

/** Representation of a trie implementation of a map. */
struct MapStruct {
  /** Root node of this tree. */
  Node *root;
};

/**
* Creates and mallocs space for a new node then initializes the values and returns the node
* @return node that has been malloced and initialzed
*/
static Node *newNode() {
  Node *node = (Node *) malloc(sizeof(Node));
  node->val = NULL;
  for (int i = 0; i < SYM_COUNT; i++) {
    node->child[i] = NULL;
  }
  return node;
}

Map *makeMap() {
    Map *map = malloc(sizeof(Map));
    map->root = NULL;
    return map;
}

/**
* A helper function to recursively traverse the map
* @param root root of trie
* @param size current size of trie
*/ 
static void traverse(Node *root, int *size) {
  if (root == NULL) {
    return;
  }

  if (root->val != NULL) {
    (*size)++;
  }

  for (int i = 0; i < SYM_COUNT; i++) {
    traverse(root->child[i], size);
  }
}

int mapSize(Map *m) {
  if (m == NULL || m->root == NULL) {
    return 0;
  }

  int size = 0;

  traverse(m->root, &size);

  return size;
}

void mapSet(Map *m, const char *key, Value *val) {

  if (m->root == NULL) {
    m->root = newNode();
  }

  Node *currentNode = m->root;
  for (int i = 0; i < strlen(key); i++) {
    int index = key[i] - '!';
    if (currentNode->child[index] == NULL) {
      currentNode->child[index] = newNode();
    }
    currentNode = currentNode->child[index];
  }

  currentNode->val = val;
}

Value *mapGet(Map *m, const char *key) {

  if (m->root == NULL) {
    return NULL;
  }

  Node *currentNode = m->root;
  for (int i = 0; i < strlen(key); i++) {
    int index = key[i] - '!';
    if (currentNode->child[index] == NULL) {
      return NULL;
    }
    currentNode = currentNode->child[index];
  }

  return currentNode->val;
}

bool mapRemove(Map *m, const char *key) {

  Node *currentNode = m->root;
  Node **childNode = NULL;
  for (int i = 0; i < strlen(key); i++) {
    int index = key[i] - '!';
    if (currentNode->child[index] == NULL) {
      return false;
    }
    childNode = &(currentNode->child[index]);
    currentNode = *childNode;
  }

  if (currentNode->val != NULL) {
    currentNode->val->destroy(currentNode->val);
    currentNode->val = NULL;
  }

  return true;
}

/**
* Helper function to free an individual node in the tree
*/
static void freeNode(Node *node) {
  for (int i = 0; i < SYM_COUNT; i++) {
    if (node->child[i] != NULL) {
      freeNode(node->child[i]);
      node->child[i] = NULL;
    }
  }
  if (node->val != NULL) {
    node->val->destroy(node->val);
  }
  free(node);
}

void freeMap(Map *m) {
  if (m == NULL || m->root == NULL) {
    free(m);
    return;
  }

  freeNode(m->root);
  m->root = NULL;

  free(m);
}


