#include <stdio.h>
#include <stdlib.h>

static void array_print(int *a, int n) {
   int i;
   for (i = 0; i < n; i++) {
      printf("%d\n", a[i]);
   }
}

void array_sort(int *a, int n) {
   int p = 0;
   int key = 0;
   int i = 0;
   for (p = 1; p < n; p++){
      key = a[p];
      for (i = p; i>=0; i--){
         if (a[i-1] > key){
            a[i] = a[i-1];
            a[i-1] = key;
         }
      }
   }
}

int main(void) {
   int capacity = 2;
   int itemcount = 0;
   int item;
   int *my_array = malloc(capacity * sizeof my_array[0]);
   if (NULL == my_array) {
      fprintf(stderr, "memory allocation failed.\n");
      exit(EXIT_FAILURE);
   }
   while (1 == scanf("%d", &item)) {
      if (itemcount == capacity) {
         capacity += capacity;
         my_array = realloc(my_array, capacity * sizeof my_array[0]);
         if (NULL == my_array) {
            fprintf(stderr, "memory reallocation failed.\n");
            exit(EXIT_FAILURE);
         }
      }
      my_array[itemcount++] = item;
   }
   array_sort(my_array, itemcount);
   array_print(my_array, itemcount);
   free(my_array);
   return EXIT_SUCCESS;
}
