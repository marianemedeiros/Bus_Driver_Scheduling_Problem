#include <stdio.h>
//#include <string.h>
#include <stdbool.h>

int HASH_SIZE;

typedef struct Hash {
   int data;   
   int key;
}Hash;

Hash* item;
Hash* dummyItem;

void freeHash(Hash** hash);
Hash** inicializeHash(int size);
int hashCode(int key);
Hash* search(int key, Hash** hashArray);
void insert(int key,int data, Hash** hashArray);
Hash* delete(Hash* item, Hash** hashArray);
void display(Hash** hashArray);