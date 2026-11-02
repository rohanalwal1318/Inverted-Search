#include "inverted.h"

int main(){

  /* Allocate memory for the hashtable */
  hashTable *hash_t = malloc(sizeof(hashTable) * 26);

  /* Initialize custom values */
  for(int i=0; i<26; i++){
    hash_t[i].index = i;
    hash_t[i].link = NULL;
  }

  char dup[50][100];

  int ch, j = 0, f = 0;

  while(1) {

    puts("1. Create Database");
    puts("2. Display Database");
    puts("3. Update Database");
    puts("4. Search");
    puts("5. Save Database");
    puts("6. Exit");

    printf("Enter the choice: ");
    scanf("%d", &ch);

    switch(ch){

      case 1 : {
        char str[100];
        printf("Enter the file name : ");
        scanf("%s", str);
        if(checkDup(dup, str, j)) {
          puts("This file has been already processed before!!");
          continue;
        }
        strcpy(dup[j++], str);
        f = createDatabase(hash_t, str);
        if(!f) {
          puts("Failed while creating Database !!");
          continue;
        }
        puts("Successfully Created Database!!");
        continue;
      }

      case 2: {
        f = displayDatabase(hash_t);
        if(!f) {
          puts("Failed while Displaying Database !!");
        }
        continue;
      }

      case 4: {
        char str[100];
        printf("Enter the word you want to search : ");
        scanf("%s", str);
        f = searchDatabase(hash_t, str);
        if(!f) {
          puts("Target Not found in the Database !!");
        }
        continue;
      }

      case 5: {
        char str[100];
        printf("Enter the filename to save with an extension without space: ");
        scanf("%s", str);
        f = saveDatabase(hash_t, str);
        if(!f) {
          puts("Failed while Displaying Database !!");
          continue;
        }
        printf("Created a %s File ..\n", str);
        continue;
      }

      case 6: {
        deleteHashTable(hash_t);
        puts("Exiting ....");
        exit(0);
      }
      
    }

  }

}