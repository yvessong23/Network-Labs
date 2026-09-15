#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 5

typedef struct{ // Hash structure
	char *key;
	int status; // Empty vs Not Empty
} bucket;

// Hash function
// Take in input, count str size, mod to array size
// Return index

int hash(char *input){
	int strSize;
	int count = 0;
	while((strSize = *input++)){
		count++;
	}
	int index = count % SIZE;	
	printf("Index (hash result): %d\n", index);
	return index;
}

// Insert bucket into hash table
// Probe if collision exists
void insert_and_probe(bucket *table, char *input, int size){
	//int size = 0;
	int capacity = SIZE;
	int ini_index = hash(input); // Start with initial index
	int index = ini_index;
	int i = index;
	while (table[index].status == 1){ // Bucket occupied, linear probe
		index = ((ini_index + i++) % SIZE);
		printf("Occupied bucket, moving to next index %d\n",((index+1)%SIZE));
		if (index == ini_index){
			break;
		}
	}
	
	if (size < capacity){
		table[index].status = 1;
		table[index].key = strdup(input);
		size++;
		printf("Key %s inserted into bucket %d\n", input, index);
	}
	return;
}

int main(int argc, char **argv) {
	// Read from file to command line
	char *input = strdup(argv[1]);
	FILE *f = fopen(input, "r");
	if (!f) perror("Could not open file!\n");
	char strings[100];
	bucket *table = malloc(sizeof(bucket) * SIZE);
	//printf("Occupied bucket, moving to next index");
	int size = 0;
	while ((fgets(strings, 100, f) != NULL)){ // Does not clear whitespace
		strings[strcspn(strings, "\n")] = '\0';
		insert_and_probe(table, strings, size);
	}
}
