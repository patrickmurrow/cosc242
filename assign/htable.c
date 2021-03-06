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
   int *stats;
   hashing_t method;
};

/**
 * Creates a hashtable by initialising the contents of a struct htablerec
 * to the default values. Allocates memory for pointers to the arrays.
 * Note: default values: NULL for the keys, -1 for stats and 0 for 
 * frequencies and num_keys, assigns the given parameters to the 
 * corresponding struct values.
 *
 * @param capacity the maximum size of the hashtable. 
 * @param method the collision resolution strategy.
 * 
 * @return result the created hashtable.
 */
htable htable_new(int capacity, hashing_t method) {
   unsigned int i = 0;
   htable result = emalloc(sizeof *result);
   
   result->capacity = capacity;
   result->method = method;
   result->num_keys = 0;
   result->frequencies = emalloc(result->capacity 
                                 * sizeof result->frequencies[0]);
   result->stats = emalloc(result->capacity 
                           * sizeof result->stats[0]);
   result->keys = emalloc(result->capacity 
                          * sizeof result->keys[0]);
   
   for (i = 0; i < result->capacity; i++) {
      result->stats[i] = -1;
      result->keys[i] = NULL;
      result->frequencies[i] = 0;
   }

   return result;
}

/**
 * Frees the memory that was allocated to a hash table by calling free 
 * on the elements of the struct. 
 * Note: Each key in the pointer holding the keys is also freed.
 *
 * @param h - the hash table.
 */
void htable_free(htable h) {
   unsigned int i;

   for (i = 0; i < h->capacity; i++) {
      if (NULL != h->keys[i]) {
         free(h->keys[i]);
      }
   }

   free(h->stats);
   free(h->keys);
   free(h->frequencies);
   free(h);
}

/**
 * Converts a String to an Integer.
 *
 * @param word the String that is to be converted
 *
 * @return the result of the conversion - an Integer 
 */
static unsigned int htable_word_to_int(char *word) {
   unsigned int result = 0;
    
   while (*word != '\0') {
      result = (*word++ + 31 * result);
   }
    
   return result;
}

/**
 * Calculates the step needed after each collision for a specific key
 *
 * @param h - the hash table.
 * @param i_key - the key in Integer form
 * 
 * @return the Integer used each time for step
 */
static unsigned int htable_step(htable h, unsigned int i_key) {
   if (h->method == DOUBLE_H) {
      return 1 + (i_key % (h->capacity - 1));
   }
   return 1;
}

/**
 * Inserts a String into a hash table using a hashing strategy when there is
 * an existing String in the desired insertion position. Counts how many 
 * times there was an existing String in the position where a key was to 
 * be inserted, i.e. collisions. Updates how many times the same String 
 * is added to the hash table by updating the corresponding cell in 
 * the frequency array.
 *
 * @param h - the hash table.
 * @param key - the String to be inserted into the hash table.
 * 
 * @return 1 if inserted, 0 for a collision, value of frequency if string 
 * already exists.
 */
int htable_insert(htable h, char *key){
   unsigned int index = htable_word_to_int(key) % h->capacity;
   unsigned int step = htable_step(h, htable_word_to_int(key));
   unsigned int collisions = 0;

   /* The hash table is full */
   if (h->num_keys == h->capacity) {
      return 0;
   }

   for (;;) {
      /* There is no string at the current index, so copy the string to 
         the position, set the corresponding cell in the frequency 
         array to 1 */
      if (NULL == h->keys[index]) {
         h->keys[index] = emalloc(sizeof(key) + 1);
         strcpy(h->keys[index], key);
         h->frequencies[index] = 1;
         h->stats[h->num_keys++] = collisions;
         return 1;
      }

      /* The exact same string is at that position, so increment the 
         frequency for the corresponding cell in the frequency array */
      if(strcmp(h->keys[index], key) == 0){
         h->frequencies[index]++;
         return h->frequencies[index];
      }

      /* step the index because a position was not found for the key */
      index = (index + step) % h->capacity; 
      collisions++;
   }
}

/**
 * Searches for a String inside the hash table by starting at the initial 
 * position where the String should be. 
 * Note: Steps if there is a collison.
 *
 * @param h - the hash table.
 * @param key - the String to search for in the hash table.
 * 
 * @return the frequency of String in the hash table if it exists.
 */
int htable_search(htable h, char *str) {
   unsigned int index = htable_word_to_int(str) % h->capacity;
   unsigned int step = htable_step(h, htable_word_to_int(str));
   unsigned int collisions = 0;

   for (;;) {
      if (NULL == h->keys[index]) {
         return 0;
      }
      if (strcmp(h->keys[index], str) == 0) {
         return h->frequencies[index];
      }
      collisions++;
      index = (index + step) % h->capacity;
      if (collisions == h->capacity) {
         return 0;
      }
   }
}

/**
 * Prints the keys of the hash table alongside their frquencies
 *
 * @param h - the hash table.
 * @param f - function that takes an Integer and a String as input.
 * 
 */
void htable_print(htable h, void f(int freq, char *word)){
   unsigned int i;

   for (i=0; i<h->capacity; i++) {
      if (h->frequencies[i] > 0) {
         f(h->frequencies[i], h->keys[i]);
      }
   }
}

/**
 * Prints out the entire contents of the hash table, including the 
 * position of the key in the hash table, the frequency of the key,
 * the number of collisions, and the key itself.
 * Note: The collisions are set out in sequential order and are not
 * related to the neighbouring figures
 *
 * @param h - the hash table.
 * @param stream - a stream to print the data to.
 */
void htable_print_entire_table(htable h, FILE *stream){
   unsigned int i;
   char *word;

   fprintf(stream, "  Pos  Freq  Stats  Word\n");
   fprintf(stream, "----------------------------------------\n");
   
   for (i=0; i < h->capacity; i++) {
      if (NULL == h->keys[i]) {
         word = "\0";
      }
      else {
         word = h->keys[i];
      }
      fprintf(stream, "%5d %5d %5d   %s\n", i, h->frequencies[i], 
              h->stats[i], word);
   }
}

/**
 * Prints out a line of data from the hash table to reflect the state
 * the table was in when it was a certain percentage full.
 * Note: If the hashtable is less full than percent_full then no data
 * will be printed.
 *
 * @param h - the hash table.
 * @param stream - a stream to print the data to.
 * @param percent_full - the point at which to show the data from.
 */
static void print_stats_line(htable h, FILE *stream, int percent_full) {
   unsigned int current_entries = h->capacity * percent_full / 100;
   double average_collisions = 0.0;
   int at_home = 0;
   int max_collisions = 0;
   unsigned int i = 0;

   if (current_entries > 0 && current_entries <= h->num_keys) {
      for (i = 0; i < current_entries; i++) {
         if (h->stats[i] == 0) {
            at_home++;
         } 
         if (h->stats[i] > max_collisions) {
            max_collisions = h->stats[i];
         }
         average_collisions += h->stats[i];
      }
    
      fprintf(stream, "%4d %10d %10.1f %10.2f %11d\n", percent_full, 
              current_entries, at_home * 100.0 / current_entries,
              average_collisions / current_entries, max_collisions);
   }
}


/**
 * Prints out a table showing what the following attributes were like
 * at regular intervals (as determined by num_stats) while the
 * hashtable was being built.
 *
 * @li Percent At Home - how many keys were placed without a collision
 * occurring.
 * @li Average Collisions - how many collisions have occurred on
 *  average while placing all of the keys so far.
 * @li Maximum Collisions - the most collisions that have occurred
 * while placing a key.
 *
 * @param h the hashtable to print statistics summary from.
 * @param stream the stream to send output to.
 * @param num_stats the maximum number of statistical snapshots to print.
 */
void htable_print_stats(htable h, FILE *stream, int num_stats) {
   int i;

   fprintf(stream, "\n%s\n\n", 
           h->method == LINEAR_P ? "Linear Probing" : "Double Hashing"); 
   fprintf(stream, "Percent   Current   Percent    Average      Maximum\n");
   fprintf(stream, " Full     Entries   At Home   Collisions   Collisions\n");
   fprintf(stream, "-----------------------------------------------------\n");
   
   for (i = 1; i <= num_stats; i++) {
      print_stats_line(h, stream, 100 * i / num_stats);
   }
   
   fprintf(stream, "-----------------------------------------------------\n\n");
}

