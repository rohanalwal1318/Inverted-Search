#include "inverted.h"

int displayDatabase(hashTable *hash_t)
{

  for (int i = 0; i < 26; i++)
  {

    if (hash_t[i].link != NULL)
    {
      mainNode *mnode = hash_t[i].link;
      while (mnode)
      {
        printf("Index: [%d], ", i);
        printf("Word: %s, ", mnode->word);
        printf("Files: %d, ", mnode->file_cnt);
        subNode *snode = mnode->subLink;
        while (snode)
        {
          printf("%s ", snode->file_name);
          printf("%d times, ", snode->word_cnt);
          snode = snode->subLink;
        }
        printf("\n");
        mnode = mnode->mainLink;
      }
    }
  }

  return 1;
}