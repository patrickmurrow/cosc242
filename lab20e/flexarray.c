#include <stdio.h>
#include <stdlib.h>
#include "flexarray.h"

struct flexarrayrec {
int capacity;
int itemcount;
int *items;
};

void selection_sort(int *a, int n) {
   int x, i, p, key, temp;
   for (i = 0; i < (n-1); i++){
      key = i;
      for (p = i+1; p < n; p++){
         if (a[key] > a[p])
            key = p;
      }
      if (key != i){
         temp = a[i];
         a[i] = a[key];
         a[key] = temp;
      }
      if (i == ((n-1)/2)){
         for (x = 0; x <n; x++){
            fprintf(stderr, "%d\n", a[x]);
         }
      }
   }
}

void insertion_sort(int *a, int n) {
   int i, p, temp, x;
   for (i = 1; i < n; i++){
      p = i;
      while (p > 0 && a[p] < a[p-1]){
         temp = a[p];
         a[p] = a[p-1];
         a[p-1] = temp;
         p--;
      }
      if (i == ((n-1)/2)){
         for (x = 0; x <n; x++){
            fprintf(stderr, "%d\n", a[x]);
         }
      }
   }
}

flexarray flexarray_new() {
  flexarray result = malloc(sizeof *result);
  result->capacity = 2;
  result->itemcount = 0;
  result->items = malloc(result->capacity * sizeof result->items[0]);
  return result;
}
void flexarray_append(flexarray f, int num) {
  if (f->itemcount == f->capacity) {
    f->capacity += f->capacity;
    f->items = realloc(f->items, f->capacity * sizeof f->items[0]);
  }
  f->items[f->itemcount++] = num;
}
/* insert the item in the last free space */
void flexarray_print(flexarray f) {
  int i = 0;
  for (i = 0; i < f->itemcount; i++){
     printf("%d\n", f->items[i]);
  }
  
  
  /* a "for" loop to print out each cell of f->items */
}
void flexarray_sort(flexarray f) {
  selection_sort(f->items, f->itemcount);
  /* mergesort would be good */
}
void flexarray_free(flexarray f) {
  free(f->items);
  free(f);
  /* free the memory associated with the flexarray */
}
