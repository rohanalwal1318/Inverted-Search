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
        /* #index;word;file_count;file1;count1;file2;count2;# */
        fprintf(fptr, "#%d;", i);
        fprintf(fptr, "%s;", mnode->word);
        fprintf(fptr, "%d;", mnode->file_cnt);
        subNode *snode = mnode->subLink;
        while (snode)
        {
          fprintf(fptr, "%s;", snode->file_name);
          fprintf(fptr, "%d;", snode->word_cnt);
          snode = snode->subLink;
        }
        fprintf(fptr, "#\n");
        mnode = mnode->mainLink;
      }
    }
  }
   
  if(fclose(fptr) != 0) return 0;
  
  return 1;

}