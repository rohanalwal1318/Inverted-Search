#include "inverted.h"

int checkDup(char dup[50][100], char *str, int n){

  /* First is already a unique */
  if(n == 0) return 0;

  for(int i=0; i<n; i++){
    if(strcmp(dup[i], str) == 0) return 1; /* if found return 0, already processed */
  }

  return 0;

}

char *getWord(FILE *fptr){

  char *buffer = malloc(sizeof(char) * 100);

  if(fscanf(fptr, "%99s", buffer) != 1){
    free(buffer);
    return NULL;
  }

  return buffer;
}

char *copyString(const char *str){

  char *copy = malloc(strlen(str) + 1);

  if(copy) strcpy(copy, str);

  return copy;
}