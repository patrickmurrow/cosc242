#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_MAX 30000
/* Takes an index and swaps its value with the smallest value in the unsorted
  array*/
void selection_sort(int *a, int n) {
   int p = 0;
   for (p = 0; p < (n); p++){
      int smallest = a[p];
      int i = 0;
      for (i = 0; i < (n-1); i++){
         if (smallest < a[i]){
            smallest = a[i];
            swap(a, p, i);
         }
      }
   }
}
/* Swaps two values in array a*/
void swap(int *a, int y, int x){
   int temp;
   temp = a[x];
   a[x] = a[y];
   a[y] = temp;
}

int main(void) {
   int my_array[ARRAY_MAX];
   clock_t start, end;
   int i, count = 0;
/* Scans for user input for the array*/
while (count < ARRAY_MAX && 1 == scanf("%d", &my_array[count])) {
      count++;
   }
   
   start = clock(); /* Start Clock*/
   selection_sort(my_array, count);
   end = clock(); /* End Clock*/

/* Prints the sorted array*/
   for (i = 0; i < count; i++) {
      printf("%d\n", my_array[i]);
   }
   fprintf(stderr, "%d %f\n", count, (end - start) / (double)CLOCKS_PER_SEC);
   return EXIT_SUCCESS;
}
