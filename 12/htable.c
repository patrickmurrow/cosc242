#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#include "htable.h"

struct htablerec {
   unsigned int capacity;
   unsigned int num_keys;
   char **keys;
   unsigned int *frequencies;
};

static unsigned int htable_word_to_int(char *word) {
   unsigned int result = 0;
   while (*word != '\0') {
      result = (*word++ + 31 * result);
   }
   return result;
}

static unsigned int htable_step(htable h, unsigned int i_key) {
   return 1 + (i_key % (h->capacity - 1));
}

htable htable_new(int capacity) {
   unsigned int i;
   htable result = emalloc(sizeof * result);
   result->capacity = capacity;
   result->num_keys = 0;
   result->frequencies = emalloc(result->capacity * sizeof result->frequencies[0]);
   result->keys = emalloc(result->capacity * sizeof result->keys[0]);
   for (i = 0; i < result->capacity; i++){
      result->frequencies[i] = 0;
      result->keys[i] = NULL;
   }
   return result;
}

char htable_insert(htable h, char *str){
   unsigned int num = htable_word_to_int(str);
   unsigned int i;
   unsigned int index = htable_step(h, num);
   if (NULL == h->keys[index]){
      h->keys[index] = emalloc((strlen(str) + 1) * sizeof str[0]);
      strcpy(h->keys[index], str);
      h->frequencies[index] = 1;
      h->num_keys++;
      return 1;
   }
   else if (strcmp(str, h->keys[index])==0){
      h->frequencies[index]++;
      return h->frequencies[index];
   }
   else if (strcmp(str, h->keys[index])!=0){
      for (i = index; i < h->capacity; i++){
         if (i == h->capacity){
            i = i%h->capacity;
         }
         if (NULL == h->keys[i]){
            h->keys[i] = emalloc((strlen(str) + 1) * sizeof str[0]);
            strcpy(h->keys[i], str);
            h->frequencies[i] = 1;
            h->num_keys++;
            return 1;
         }
         if (strcmp(str, h->keys[i])==0){
            h->frequencies[i]++;
            return h->frequencies[i];
         }
      }
   }
   return 0;
}

int htable_search(htable h, char *key){
   unsigned int collisions = 0;
   unsigned int num = htable_word_to_int(key);
   unsigned int index = htable_step(h, num);
   while (!(NULL == h->keys[index]) && (strcmp(key, h->keys[index])!=0)
          && index < h->capacity){
      index = (index+1)%h->capacity;
      collisions++;
      if (collisions == h->capacity){
         return 0;
      }
   }
   return h->frequencies[index];
}
              

void htable_print(htable h, FILE *file) {
   unsigned int i;
   for (i = 0; i < h->capacity; i++) {
      if (h->frequencies[i]!=0){
         fprintf(file, "%s\n%d\n", h->keys[i],h->frequencies[i]);
      }
   }
}


void htable_free(htable h) {
      free(h->keys);
      free(h->frequencies);
      free(h);
}
