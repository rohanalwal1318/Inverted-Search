#include<stdio.h>

int main(){

  char *database = "vaishnavi penti"; /*a-z*/

  char target = 'i';
  char target1 = 'v';
  char target2 = 'z';

  int arr[26] = {0};

  for(int i=0; database[i]; i++)
    arr[database[i]-'a']++;

  
  if(arr[target-'a'])
    printf("%d\n", arr[target-'a']);

}