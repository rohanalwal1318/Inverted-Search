#include "inverted.h"

int deleteHashTable(hashTable *hash_t){

  if(hash_t == NULL) return 0;

  for(int i = 0; i < 26; i++){

    mainNode *mnode = hash_t[i].link;

    while(mnode){

      /* free all the subnodes of this word */
      subNode *snode = mnode->subLink;
      while(snode){
        subNode *snext = snode->subLink;
        free(snode->file_name);
        free(snode);
        snode = snext;
      }

      /* free the mainnode itself */
      mainNode *mnext = mnode->mainLink;
      free(mnode->word);
      free(mnode);
      mnode = mnext;
    }

    hash_t[i].link = NULL;
  }

  /* finally the table itself */
  free(hash_t);

  return 1;
}
