#include "inverted.h"

int searchDatabase(hashTable *hash_t, char *target){

  int idx = target[0] - 'a';

  if(hash_t[idx].link == NULL) {
    printf("Data Not found!!\n");
    return 0;
  }

  mainNode *mnode = hash_t[idx].link;

  while(mnode && strcmp(mnode->word, target)){
    mnode = mnode->mainLink;
  }

  if(mnode == NULL) {
    printf("Target Not Found!!\n");
  }

  printf("Target - %s, File Count : %d, ", target, mnode->file_cnt);
  subNode *snode = mnode->subLink;

  while(snode){
    printf("File name - %s, %d Times, ", snode->file_name, snode->word_cnt);
    snode = snode->subLink;
  }

  return 1;

}