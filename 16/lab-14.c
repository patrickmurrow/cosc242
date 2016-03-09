#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "rbt.h"

void print_key(char *s) {
   printf("%s ", s);
}


int main(void) {
   rbt b = rbt_new();
   char word[256];
   char op;
      while (2 == scanf(" %c %255s", &op, word)) {
         if ('+' == op) {
            b = rbt_insert(b, word);
         } else if ('?' == op) {
            printf( "%d\n", rbt_search(b, word));
         } else if ('-' == op) {
            rbt_delete(b, word);
         }
      }
      printf("Inorder\n");
      rbt_inorder(b, print_key);
      printf("\nPreorder\n");
      rbt_preorder(b, print_key);
      
      return EXIT_SUCCESS;
}
