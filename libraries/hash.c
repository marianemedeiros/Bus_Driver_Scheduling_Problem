#include "hash.h"

void freeHash(Hash** hash){
   for (int i = 0; i < HASH_SIZE; i++){
      free(hash[i]);
   }
   //free(hash);
   free(dummyItem);
}

Hash** inicializeHash(int size){
   dummyItem = (Hash*) malloc(sizeof(Hash));
   dummyItem->data = -1;  
   dummyItem->key = -1; 
   
   HASH_SIZE = size;
   Hash** hashArray =  (Hash**) calloc(HASH_SIZE, sizeof(Hash*));
   return hashArray;
}

int hashCode(int key) {
   return key % HASH_SIZE;
}


Hash* search(int key, Hash** hashArray) {
   //get the hash 
   int hashIndex = hashCode(key);  
	
   //move in array until an empty 
   while(hashArray[hashIndex] != NULL) {
	
      if(hashArray[hashIndex]->key == key)
         return hashArray[hashIndex]; 
			
      //go to next cell
      ++hashIndex;
		
      //wrap around the table
      hashIndex %= HASH_SIZE;
   }        
	
   return NULL;        
}


void insert(int key,int data, Hash** hashArray) {

   Hash* item = (Hash*) malloc(sizeof(Hash));
   item->data = data;  
   item->key = key;

   //get the hash 
   int hashIndex = hashCode(key);

   //move in array until an empty or deleted cell
   while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != -1) {
      //go to next cell
      ++hashIndex;
		
      //wrap around the table
      hashIndex %= HASH_SIZE;
   }
	
   hashArray[hashIndex] = item;
}


Hash* delete(Hash* item, Hash** hashArray) {
   int key = item->key;

   //get the hash 
   int hashIndex = hashCode(key);

   //move in array until an empty
   while(hashArray[hashIndex] != NULL) {
	
      if(hashArray[hashIndex]->key == key) {
         Hash* temp = hashArray[hashIndex]; 
			
         //assign a dummy item at deleted position
         hashArray[hashIndex] = dummyItem; 
         return temp;
      }
		
      //go to next cell
      ++hashIndex;
		
      //wrap around the table
      hashIndex %= HASH_SIZE;
   }      
	
   return NULL;        
}

void display(Hash** hashArray) {
   int i = 0;
	
   for(i = 0; i<HASH_SIZE; i++) {
	
      if(hashArray[i] != NULL)
         printf(" (%d,%d)",hashArray[i]->key,hashArray[i]->data);
      else
         printf(" ~~ ");
   }
	
   printf("hash HASH_SIZE: %d\n", HASH_SIZE);
}

/*
int main() {
   dummyItem = (Hash*) malloc(sizeof(Hash));
   dummyItem->data = -1;  
   dummyItem->key = -1; 

   insert(1, 20);
   insert(2, 70);
   insert(42, 80);
   insert(4, 25);
   insert(12, 44);
   insert(14, 32);
   insert(17, 11);
   insert(13, 78);
   insert(37, 97);

   display();
   item = search(37);

   if(item != NULL) {
      printf("Element found: %d\n", item->data);
   } else {
      printf("Element not found\n");
   }

   delete(item);
   item = search(37);

   if(item != NULL) {
      printf("Element found: %d\n", item->data);
   } else {
      printf("Element not found\n");
   }
}
*/