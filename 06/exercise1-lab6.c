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

/* n is the size of the array */
void print_array(int *a, int n) {
   if (n > 0) {
      printf("%d ", a[0]);
      print_array(a + 1, n - 1);
   }
}


int main(void) {
   int my_array[ARRAY_MAX];
   int count = 0;
   /* Scans for user input for the array*/
   while (count < ARRAY_MAX && 1 == scanf("%d", &my_array[count])) {
      count++;
   }
   insertion_sort(my_array, count);

   print_array(my_array, count);

   return EXIT_SUCCESS;
}
