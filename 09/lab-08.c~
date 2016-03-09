#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_MAX 10000

void merge(int *a, int *w, int len) {
   int m = len/2;
   int i = 0, j = m, k = 0;
   while (i < m && j < len)
      {
         if (a[i] < a[j])       
            w[k++] = a[i++];

         else        
            w[k++] = a[j++];               
      }

   while (i < m)  
      w[k++] = a[i++];


   while (j < len)    
      w[k++] = a[j++];

   
}

void merge_sort(int *a, int *w, int n){
   int i = 0, m = (n/2);
   if (n<2) {
      return;
   }
   merge_sort(a, w, m);
   merge_sort(a + m, w + m, n-m);
   merge(a, w, n);
   
   for (i = 0; i < n; i++){
      a[i] = w[i];
   }
}

int main(void) {
   int my_array[ARRAY_MAX];
   int w[ARRAY_MAX];
   int i, count = 0;
   
   while (count < ARRAY_MAX && 1 == scanf("%d", &my_array[count])) {
      count++;
   }

   merge_sort(my_array, w, count);
   
   for (i = 0; i < count; i++) {
      printf("%d ", my_array[i]);
   }
   return EXIT_SUCCESS;
}

