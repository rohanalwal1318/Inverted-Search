#include "inverted.h"
#include <ctype.h>

/* Read one full line (any length) from the file, NULL on end of file */
static char *readLine(FILE *fptr){

  size_t cap = 256, len = 0;
  char *buf = malloc(cap);
  int c;

  if(buf == NULL) return NULL;

  while((c = fgetc(fptr)) != EOF && c != '\n'){
    if(len + 1 >= cap){
      cap *= 2;
      char *tmp = realloc(buf, cap);
      if(tmp == NULL){
        free(buf);
        return NULL;
      }
      buf = tmp;
    }
    buf[len++] = (char)c;
  }

  if(c == EOF && len == 0){
    free(buf);
    return NULL;
  }

  /* drop trailing \r / spaces (file edited on Windows etc.) */
  while(len > 0 && (buf[len-1] == '\r' || buf[len-1] == ' ' || buf[len-1] == '\t')) len--;
  buf[len] = '\0';

  return buf;
}

/* 1 if the string is a (small) positive or zero number made only of digits */
static int isNumber(const char *s){

  size_t n = strlen(s);

  if(n == 0 || n > 9) return 0;

  for(size_t i=0; i<n; i++){
    if(!isdigit((unsigned char)s[i])) return 0;
  }

  return 1;
}

/* Load ONE saved line  #index;word;file_count;file1;count1;...;#  into the hash table
   returns 1 if loaded, 0 if the line is malformed (nothing is touched in that case) */
static int loadLine(hashTable *hash_t, char *line){

  size_t len = strlen(line);
  int ntok = 1;

  if(len < 3 || line[0] != '#' || line[len-1] != '#' || line[len-2] != ';') return 0;

  /* split the line at every ';' */
  for(size_t i=0; i<len; i++){
    if(line[i] == ';') ntok++;
  }

  char **tok = malloc(sizeof(char *) * ntok);
  if(tok == NULL) return 0;

  int t = 0;
  tok[t++] = line;
  for(size_t i=0; i<len; i++){
    if(line[i] == ';'){
      line[i] = '\0';
      tok[t++] = line + i + 1;
    }
  }

  /* tokens : 0 -> #index | 1..p-1 -> word | p -> file_count | pairs (file, count) | last -> # */
  int n = ntok - 1;
  int idx = -1, fc = 0, p = -1;

  if(strcmp(tok[ntok-1], "#") != 0 || tok[0][0] != '#' || !isNumber(tok[0] + 1)){
    free(tok);
    return 0;
  }

  idx = atoi(tok[0] + 1);

  /* find file_count from the right side, so a word that itself contains ';' still loads right */
  for(int cand = (n - 3) / 2; cand >= 1; cand--){
    int pos = n - 1 - 2 * cand;
    int ok = (pos >= 2) && isNumber(tok[pos]) && atoi(tok[pos]) == cand;

    for(int k=0; ok && k<cand; k++){
      char *fname = tok[pos + 1 + 2*k];
      char *fcnt = tok[pos + 2 + 2*k];
      if(fname[0] == '\0' || !isNumber(fcnt) || atoi(fcnt) < 1) ok = 0;
    }

    if(ok){
      fc = cand;
      p = pos;
      break;
    }
  }

  if(p < 0 || idx < 0 || idx >= 26){
    free(tok);
    return 0;
  }

  /* word = everything between the index and file_count (tokens are contiguous in the line) */
  size_t wlen = (size_t)(tok[p] - 1 - tok[1]);
  char *word = malloc(wlen + 1);

  if(word == NULL){
    free(tok);
    return 0;
  }

  memcpy(word, tok[1], wlen);
  word[wlen] = '\0';
  for(size_t i=0; i<wlen; i++){
    if(word[i] == '\0') word[i] = ';'; /* give back the ';' that was split */
  }

  /* the word must belong to the index it was saved under */
  if(wlen == 0 || tolower((unsigned char)word[0]) - 'a' != idx){
    free(word);
    free(tok);
    return 0;
  }

  /* find the word in the table, or add a new mainnode at the end of its list */
  mainNode *mnode = hash_t[idx].link, *prev = NULL;

  while(mnode && strcmp(mnode->word, word)){
    prev = mnode;
    mnode = mnode->mainLink;
  }

  if(mnode == NULL){
    mnode = malloc(sizeof(mainNode) * 1);
    if(mnode == NULL){
      free(word);
      free(tok);
      return 0;
    }
    mnode->file_cnt = 0;
    mnode->mainLink = NULL;
    mnode->subLink = NULL;
    mnode->word = word;

    if(prev) prev->mainLink = mnode;
    else hash_t[idx].link = mnode;
  }
  else{
    free(word);
  }

  /* add every (file, count) pair, a file already present for this word is skipped (no double count) */
  for(int k=0; k<fc; k++){
    char *fname = tok[p + 1 + 2*k];
    int cnt = atoi(tok[p + 2 + 2*k]);

    subNode *s = mnode->subLink, *sprev = NULL;

    while(s && strcmp(s->file_name, fname)){
      sprev = s;
      s = s->subLink;
    }

    if(s != NULL) continue;

    subNode *snode = malloc(sizeof(subNode) * 1);
    if(snode == NULL) continue;

    snode->file_name = copyString(fname);
    snode->word_cnt = cnt;
    snode->subLink = NULL;

    if(sprev) sprev->subLink = snode;
    else mnode->subLink = snode;

    mnode->file_cnt++;
  }

  free(tok);
  return 1;
}

int updateDatabase(hashTable *hash_t, char *file){

  /* open the saved database file in read mode */
  FILE *fptr = fopen(file, "r");

  if(fptr == NULL) return 0;

  int loaded = 0, bad = 0;
  char *line;

  while((line = readLine(fptr)) != NULL){

    /* skip empty lines */
    if(line[0] == '\0'){
      free(line);
      continue;
    }

    if(loadLine(hash_t, line)) loaded++;
    else bad++;

    free(line);
  }

  fclose(fptr);

  if(bad) printf("Skipped %d line(s) that are not in the saved database format\n", bad);

  return loaded > 0;

}
