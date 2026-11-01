#include "inverted.h"

int main()
{

  hashTable *hash_t = malloc(sizeof(hashTable) * 26);

  for (int i = 0; i < 26; i++)
  {
    hash_t[i].index = i;
    hash_t[i].link = NULL;
  }

  int f = createDatabase(hash_t, "input.txt");
  f = createDatabase(hash_t, "input2.txt");

  if (f == 0)
    return printf("Failed");

  displayDatabase(hash_t);

  f = searchDatabase(hash_t, "apple");
  if (f == 0)
    return printf("Failed");

  f = saveDatabase(hash_t, "backup.txt");

  if (f == 0)
    return printf("Failed");

  
}