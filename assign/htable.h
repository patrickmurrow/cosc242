#include <stdio.h>

#ifndef HTABLE_H_
#define HTABLE_H_

#include <stdio.h>

typedef struct htablerec *htable;
typedef enum hashing_e { LINEAR_P, DOUBLE_H } hashing_t;

/**
 * Frees the memory that was allocated to a hash table by calling free 
 * on the elements of the struct. 
 * Note: Each key in the pointer holding the keys is also freed.
 *
 * @param h - the hash table.
 */
extern void htable_free(htable h);

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
extern int htable_insert(htable h, char *str);

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
extern htable htable_new(int capacity, hashing_t method);

/**
 * Prints the keys of the hash table alongside their frquencies
 *
 * @param h - the hash table.
 * @param f - function that takes an Integer and a String as input.
 * 
 */
extern void htable_print(htable h, void f(int freq, char *word));

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
extern int htable_search(htable h, char *str);

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
extern void htable_print_entire_table(htable h, FILE *stream);

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
extern void htable_print_stats(htable h, FILE *stream, int num_stats);

#endif
