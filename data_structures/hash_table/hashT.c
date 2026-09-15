#include "hash_table.c"
#include <stdio.h>
#include <stdlib.h>

// Add
// Remove
// Search

typedef struct {
	void *key;
	void *val;
	int status;
} hashNode;

typedef struct {
    uint32_t size;
    uint32_t capacity;
    uint8_t status;
	hashNode *node;
} hashTable;


hashTable *make_table(uint32_t capacity){
	hashTable *t = malloc(sizeof(hashTable)); // Create hashTable via size
	t->size = 0;
	t->status = 0;
	t->capacity = capacity;
	t->node = malloc(sizeof(hashNode) * capacity);
	return t;
}

uint32_t *hash_str(char *key){
	return;
}

uint32_t *hash_v(void *key){
	return;
}

void add_v(hashTable *t, void *key, void *val){
	// given the key, hash the function return the index
    hashNode *h = search_v(key); // search for bucket to insert hashNode
	// node[index].status == 0
	//	node[index]->1 & 
	// node[index] i

    // check if index is occupied, move to next if so
        //
    // return bucket

}

void *search_v(hashTable *h, void *key)
	// uint32_t index = hash(); // find index
	// while node[index].status == 1 or 2
	//	node[index] + 1 % capacity
	// check if index at table is avail, if so return
	//
	// keep looking until avail
}

int main(){ 

}
