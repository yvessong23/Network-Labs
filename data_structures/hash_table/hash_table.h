// This file is the header file for a HashTable implementation 
// using Open addressing as a Collision Resolution strategy

#include <stdio.h>
#include <stdlib.h>

/*
 Status = 0,1,2
 0 = empty, 1 = occupied, 2 = keep search
*/
typedef struct HashNode *hashNode;
typedef struct hashTable *hashTable;


void add_v(hashTable *t, void *key, void *val);
void search_v(hashTable *t, void *key);
void del_v(hashTable *t, void *key, void *val);
void compare_nodes(hashNode *a, hashNode *b);


