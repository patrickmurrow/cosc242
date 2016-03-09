#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "flexarray.h"


struct flexarrayrec {
   int capacity;
   int itemcount;
   int *items;
};

flexarray flexarray_new() {
   flexarray result = emalloc(sizeof *result);
   result->capacity = 2;
   result->itemcount = 0;
   result->items = emalloc(result->capacity * sizeof result->items[0]);
   return result;
}

void flexarray_append(flexarray f, int num) {
   if (f->itemcount == f->capacity) {
      f->capacity += f->capacity;
      f->items = erealloc(f->items, f->capacity * sizeof f->items[0]);
   }
   f->items[f->itemcount++] = num;
}

void flexarray_print(flexarray f) {
   int i;
   for (i = 0; i < f->itemcount; i++) {
      printf("%d\n", f->items[i]);
   }
}

void quick_sort(int *a, int len){
   int pivot = a[0];
   int temp;
   int i = -1;
   int j = len;
   if (len<2){
      return;
   }
   for(;;){
      do {
         i++;
      }while(a[i] < pivot);
      do {
         j--;
      }while(a[j] > pivot);
      if (i < j){
         temp = a[i];
         a[i] = a[j];
         a[j] = temp;
      }else{
         break;
      }
   }
   quick_sort(a, j+1);
   quick_sort(a+i, len-j-1);
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
  

void flexarray_sort(flexarray f) {
   /* int p = 0; */
   /* int key = 0; */
   /* int i = 0; */
   /* for (p = 1; p < f->itemcount; p++){ */
   /*    key = f->items[p]; */
   /*    for (i = p; i>=0; i--){ */
   /*       if (f->items[i-1] > key){ */
   /*          f->items[i] = f->items[i-1]; */
   /*          f->items[i-1] = key; */
   /*       } */
   /*    } */
   /* } */
   quick_sort(f->items, f->itemcount); 
}

void flexarray_free(flexarray f) {
   free(f);
}
