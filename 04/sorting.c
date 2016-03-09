#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_MAX 30000
/* Takes an index and swaps its value with the value above it if the value
   is greater*/
void insertion_sort(int *a, int n) {
   int p = 0;
   int key = 0;
   for (p = 1; p < n; p++){
      key = a[p];
      int i = 0;
      for (i = p; i>=0; i--){
         if (a[i-1] > key){
            a[i] = a[i-1];
            a[i-1] = key;
         }
      }
   }
}
int main(void) {
   int my_array[ARRAY_MAX];
   clock_t start, end;
   int i, count = 0;
/* Scans for user input for the array*/
   while (count < ARRAY_MAX && 1 == scanf("%d", &my_array[count])) {
      count++;
   }

   start = clock(); /* Clock Start*/
   insertion_sort(my_array, count);
   end = clock(); /* Clock End*/

/* Prints out the sorted array*/
   for (i = 0; i < count; i++) {
      printf("%d\n", my_array[i]);
   }
   fprintf(stderr, "%d %f\n", count, (end - start) / (double)CLOCKS_PER_SEC);
   return EXIT_SUCCESS;
}
