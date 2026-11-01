#include "inverted.h"

int saveDatabase(hashTable *hash_t, char *fileName){

  /* open the file in write mode */
  FILE *fptr = fopen(fileName, "w");

  if(fptr == NULL) return 0;

  for (int i = 0; i < 26; i++)
  {

    if (hash_t[i].link != NULL)
    {
      mainNode *mnode = hash_t[i].link;
      while (mnode)
      {
        fprintf(fptr, "Index: [%d], ", i);
        fprintf(fptr, "Word: %s, ", mnode->word);
        fprintf(fptr, "Files: %d, ", mnode->file_cnt);
        subNode *snode = mnode->subLink;
        while (snode)
        {
          fprintf(fptr, "%s ", snode->file_name);
          fprintf(fptr, "%d times, ", snode->word_cnt);
          snode = snode->subLink;
        }
        fprintf(fptr, "\n");
        mnode = mnode->mainLink;
      }
    }
  }
   
  fclose(fptr); 
  
  return 1;

}