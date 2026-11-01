#include "inverted.h"
#include <ctype.h>

char *getWord(FILE *fptr){

  char *buffer = malloc(sizeof(char) * 100);

  if(fscanf(fptr, "%99s", buffer) != 1){
    free(buffer);
    return NULL;
  }

  return buffer;
}

int createDatabase(hashTable *hash_t, char *file){
  
  /* Open the file */
  FILE *fptr = fopen(file, "r");

  if(fptr == NULL) {
    return 0;
  }

  /* get word from the file */
  char *word = getWord(fptr);

  while(word){

  /* Calculate index of a word*/
  int idx = tolower((unsigned char)word[0]) - 'a';

  /* skip words that do not start with a letter */
  if(idx < 0 || idx >= 26){
    free(word);
    word = getWord(fptr);
    continue;
  }

  /* if it found first */
  if(hash_t[idx].link == NULL){
    /* create a subnode */
    subNode *snode = malloc(sizeof(subNode) * 1);
    snode->file_name = file;
    snode->subLink = NULL;
    snode->word_cnt = 1;

    /* create a mainnode*/
    mainNode *mnode = malloc(sizeof(mainNode) * 1);
    mnode->file_cnt = 1;
    mnode->mainLink = NULL;
    mnode->subLink = snode;
    mnode->word = word;

    /* Point to the main node */
    hash_t[idx].link = mnode;
    word = getWord(fptr);
    continue;
  }

  /* check If the same word occured again */
  mainNode *temp = hash_t[idx].link, *prev = NULL;

  /* Find the word if present, to stop when the word is found or i end up the links */
  while(temp && strcmp(temp->word, word)){
    prev = temp;
    temp = temp->mainLink;
  }

  /* The word not found */
  if(temp == NULL && prev != NULL){
    /* create a subnode */
    subNode *snode = malloc(sizeof(subNode) * 1);
    snode->file_name = file;
    snode->subLink = NULL;
    snode->word_cnt = 1;

    /* create a mainnode*/
    mainNode *mnode = malloc(sizeof(mainNode) * 1);
    mnode->file_cnt = 1;
    mnode->mainLink = NULL;
    mnode->subLink = snode;
    mnode->word = word;

    prev->mainLink = mnode;
    word = getWord(fptr);
    continue;
  }

  /* check the word is found */
  else if(strcmp(temp->word, word) == 0){
    subNode *t2 = temp->subLink, *p2 = NULL;

    while(t2 && strcmp(t2->file_name, file)){
      p2 = t2;
      t2 = t2->subLink;
    }

    /* if found, increment word count i.e of same file */
    if(t2 != NULL){
        t2->word_cnt++;
        free(word);
        word = getWord(fptr);
        continue;
    }

    else{
      /*create a subnode */
      subNode *snodee = malloc(sizeof(subNode) * 1);
      snodee->file_name = file;
      snodee->subLink = NULL;
      snodee->word_cnt = 1;
      p2->subLink = snodee;
    }

    /* Increment the file count of main node */
    temp->file_cnt++;

  }
  free(word);
  word = getWord(fptr);
}

  fclose(fptr);
  return 1;
}
