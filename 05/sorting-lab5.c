#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_MAX 10000
#define STRING_MAX 80
/* Takes an index and swaps its value with the value above it if the value
   is greater*/

void insertion_sort(char **wordlist, int n) {
   int i = 0;
   char *key;
   int p = 0;
   for (p = 1; p<n; p++){
      key = wordlist[p];
      for (i = p; i>0; i--){
         if (strcmp(wordlist[i-1], key) > 0){
            key = wordlist[i];
            wordlist[i] = wordlist[i-1];
            wordlist[i-1] = key;
         }
      }
   }
}

void *emalloc(size_t s) {
   void *result = malloc(s);
   if (NULL == result) {
      fprintf(stderr, "Memory allocation failed!\n");
      exit(EXIT_FAILURE);
   }
   return result;
}

                    
int main(void) {
   char word[STRING_MAX];
   char *wordlist[ARRAY_MAX];
   int i, count = 0;
   while (count < ARRAY_MAX && 1 == scanf("%79s", word)){
      wordlist[count] = emalloc((strlen(word)+1) * sizeof wordlist[0][0]);
      strcpy(wordlist[count], word);
      count++;
   }
   
   insertion_sort(wordlist, count);

   for (i = 0; i < count; i++) {
      printf("%s, ", wordlist[i]);
   }
   return EXIT_SUCCESS;
}
