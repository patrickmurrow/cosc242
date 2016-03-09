#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main(void) {
   double d = 0;
   queue my_queue = queue_new();
   char op;

   while (1 == scanf(" %c", &op)) {
      if ('+' == op) {
         if (1 == scanf("%lg", &d)){
            enqueue(my_queue, d);
         }
      }else if ('-' == op) {
         printf("%.2f\n", dequeue(my_queue));
      }
      else if ('*' == op) {
         queue_print(my_queue);
      }
      else if ('?' == op) {
         printf("Size: %d\n", queue_size(my_queue));
      }
   }
   queue_free(my_queue);
   
   return EXIT_SUCCESS;
}
