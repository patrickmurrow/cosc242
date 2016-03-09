#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_MAX 2000000
int my_array[ARRAY_MAX];
int w[ARRAY_MAX];

void *emalloc(size_t s) {
   void *result = malloc(s);
   if (NULL == result) {
      fprintf(stderr, "Memory allocation failed!\n");
      exit(EXIT_FAILURE);
   }
   return result;
}

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

void merge_sort(int *a, int *w, int n){
   int i = 0, m = (n/2);
   if (n < 40) {
      insertion_sort(a, n);
   }
   else{
      merge_sort(a, w, m);
      merge_sort(a + m, w + m, n-m);
      merge(a, w, n);
      for (i = 0; i < n; i++){
         a[i] = w[i];
      }
   }
}

int main(void) {
   clock_t start, end;
   int i, count = 0;
   
   while (count < ARRAY_MAX && 1 == scanf("%d", &my_array[count])) {
      count++;
   }

   start = clock(); /* Clock Start*/
   merge_sort(my_array, w, count);
   end = clock(); /* Clock End*/
   
   for (i = 0; i < count; i++) {
      printf("%d ", my_array[i]);
   }
   fprintf(stderr, "%d %f\n", count, (end - start) / (double)CLOCKS_PER_SEC);
   return EXIT_SUCCESS;
}

