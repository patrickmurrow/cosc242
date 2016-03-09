#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_MAX 10000

void merge_sort(int *a, int *w, int n){
   int i =0, m = n/2;
   if (n<2) {
      return;
   }
   merge_sort(a, w, m);
   merge_sort(&a[m], w, n);
   merge(a, w, n);
   
   for (i = 0; i < n; i++){
      a[i] = w[i];
   }
}

merge(int *a, int *w, int len) {
   int m = len/2;
   int i = 0, j = len/2, k = 0;

   while (i < m && j < m)
      {
         if (a[i] < a[j])       
            w[k++] = a[i++];

         else        
            w[k++] = a[j++];               
      }

   while (i < m)  
      w[k++] = a[i++];


   while (j < m)    
      w[k++] = a[j++];

   return w;
}

int main(void) {
   int my_array[ARRAY_MAX];
   int w[ARRAY_MAX];
   clock_t start, end;
   int i, count = 0;
   /* Scans for user input for the array*/
   while (count < ARRAY_MAX && 1 == scanf("%d", &my_array[count])) {
      count++;
   }

   start = clock(); /* Clock Start*/
   merge_sort(my_array, w,count);
   end = clock(); /* Clock End*/

   /* Prints out the sorted array*/
   for (i = 0; i < count; i++) {
      printf("%d\n", my_array[i]);
   }
   fprintf(stderr, "%d %f\n", count, (end - start) / (double)CLOCKS_PER_SEC);
   return EXIT_SUCCESS;
}

