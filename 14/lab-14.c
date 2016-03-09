#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "bst.h"

void print_key(char *s) {
   printf("%s ", s);
}

int main(void) {
   bst b = bst_new();
   char word[256];
   char op;
      while (2 == scanf(" %c %255s", &op, word)) {
         if ('+' == op) {
            b = bst_insert(b, word);
         } else if ('?' == op) {
            printf( "%d\n", bst_search(b, word));
         } else if ('-' == op) {
            bst_delete(b, word);
         }
      }
      printf("Inorder\n");
      bst_inorder(b, print_key);
      printf("\nPreorder\n");
      bst_preorder(b, print_key);
      
      return EXIT_SUCCESS;
}
