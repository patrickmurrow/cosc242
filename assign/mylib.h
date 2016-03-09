#ifndef MYLIB_H_
#define MYLIB_H_

#include <stddef.h>

/**
 * Allocates memory with a size given as a parameter
 *
 * @param s - size of memory to allocate
 *
 * @return result - allocated memory
 */
extern void *emalloc(size_t);

/**
 * Reallocates the memory with a size given as a parameter
 *
 * @param s - size of memory to reallocate
 * @param p - memory to reallocate
 *
 * @return p - allocated memory
 */
extern void *erealloc(void *, size_t);

/**
 * Gets words from a stream
 *
 * @param word
 * @param size of the word
 * @param stream - stream to get input from
 *
 * @return the word read from the stream
 */
extern int getword(char *word, int word_size, FILE *stream);

#endif
