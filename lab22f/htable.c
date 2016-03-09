#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "htable.h"
#include "mylib.h"
struct htablerec {
   int capacity;
   int num_keys;
   char **keys;
};
static unsigned int htable_word_to_int(char *word) {
   unsigned int result = 0;
   while (*word != '\0') {
      result = (*word++ + 31 * result);
   }
   return result;
}

static unsigned int htable_hash(htable h, unsigned int i_key) {
   return i_key % h->capacity;
}

htable htable_new(int capacity) {
   int i = 0;
   htable result = emalloc(sizeof * result);
   result->capacity = capacity;
   result->num_keys = 0;
   result->keys = emalloc(result->capacity * sizeof result->keys[0]);
   for (i = 0; i < result->capacity; i++){
      result->keys[i] = NULL;
   }
   return result;
}

void htable_free(htable h) {
   int i = 0;
   for (i = 0; i < h->capacity; i++){
      free(h->keys[i]);
   }
   free(h->keys);
   free(h);
}

char htable_insert(htable h, char *str) {
   unsigned int num = htable_word_to_int(str);
   unsigned int index = num%h->capacity;
   if (h->num_keys == h->capacity){
      return 0;
   }
   for(;;){
      if (h->keys[index] == NULL){
         h->keys[index] = emalloc((strlen(str)+1) * sizeof str[0]);
         strcpy(h->keys[index], str);
         h->num_keys++;
         return 1;
      }
      if (strcmp(str, h->keys[index]) == 0){
         return 0;
      }
      index++;
      index = htable_hash(h, index);
   }
}

void htable_print(htable h, FILE *stream) {
   int i = 0;
   for (i = 0; i < h->capacity; i++) {
      fprintf(stream, "%2d %s\n", i, h->keys[i] == NULL ? "" : h->keys[i]);
   }
}
