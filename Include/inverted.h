#ifndef INVERTED_H
#define INVERTED_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* a subnode will hold word count, filename, a subnode link */
typedef struct subnode{
  int word_cnt;
  char *file_name;
  struct subnode *subLink;
}subNode;

/* a mainnode will hold file count, a word, mainLink and sublink */
typedef struct mainnode{
  int file_cnt;
  char *word;
  struct mainnode *mainLink;
  struct subnode *subLink;
}mainNode;


/* Hash table -> 1. index 2. Mainnode link*/
typedef struct Hash{
  int index;
  struct mainnode *link;
}hashTable;

/* Create Database need a hashtable and a filename */
int createDatabase(hashTable *hash_t, char *file);

/* Display database , will display all of the info */
int displayDatabase(hashTable *hash_t);

/* Save Database */
int saveDatabase(hashTable *hash_t, char *fileName);

/* search HashTable*/
int searchDatabase(hashTable *hash_t, char *target);

#endif
