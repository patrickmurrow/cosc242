#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include "mylib.h"

/**
 * Gets words from a stream
 *
 * @param word
 * @param size of the word
 * @param stream - stream to get input from
 *
 * @return the word read from the stream
 */
int getword(char *s, int limit, FILE *stream) {
   int c;
   char *w = s;

   assert(limit > 0 && s != NULL && stream != NULL);

   /* skip to the start of the word */
   while (!isalnum(c = getc(stream)) && EOF != c)
      ;
   if (EOF == c) {
      return EOF;
   } else if (--limit > 0) { /* reduce limit by 1 to allow for the \0 */
      *w++ = tolower(c);
   }
   while (--limit > 0) {
      if (isalnum(c = getc(stream))) {
         *w++ = tolower(c);
      } else if ('\'' == c) {
         limit++;
      } else {
         break;
      }
   }
   *w = '\0';
   return w - s;
}

/**
 * Allocates memory with a size given as a parameter
 *
 * @param s - size of memory to allocate
 *
 * @return result - allocated memory
 */
void *emalloc(size_t s){
   void *result = malloc(s);
   if (NULL == result) {
      fprintf(stderr, "memory allocation failed!\n");
      exit(EXIT_FAILURE);
   }
   return result;
}

/**
 * Reallocates the memory with a size given as a parameter
 *
 * @param s - size of memory to reallocate
 * @param p - memory to reallocate
 *
 * @return p - allocated memory
 */
void *erealloc(void *p, size_t s) {
   p = realloc(p, s);
   if (NULL == p) {
      fprintf(stderr, "memory allocation failed.\n");
      exit(EXIT_FAILURE);
   }
   return p;
}
