#include <stdio.h>
#include <stdlib.h>

void max_min(int *a, int n, int *max, int *min){
   int i;
   int maxs = a[i];
   int mins = a[i];
   for(i=0; i < n; i++){
      if(a[i]>maxs){
         maxs = a[i];
      }
      else if(a[i]<mins){
         mins = a[i];
      }
   }
   *max = maxs;
   *min = mins;
}

int main(void){
   int my_array[] = { 5, 2, 7, 3, 4 };
   int biggest, smallest;
   max_min(my_array, 5, &biggest, &smallest);
   printf("max value is %d, min value is %d\n", biggest, smallest);
}
