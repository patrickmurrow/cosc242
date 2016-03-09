#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_MAX 30000
/* Takes an index and swaps its value with the value above it if the value
   is greater*/
void insertion_sort(int *a, int n) {
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

void print_array(int *a, int n) {
   if (n > 0) {
      printf("%d ", a[0]);
      print_array(a + 1, n - 1);
   }
}


int binsearch(int *a, int n, int value){
   int mid = (n/2);
   if(n==0){
      return 0;
   }
   else if(value == a[mid]){
      return 1;
   }
   else if(value < a[mid]){
      return binsearch(&a[0], mid, value);
   }
   else{
      return binsearch(&a[mid], mid, value);
   }
}

int main(int argc, char **argv) {
   FILE *infile;
   int my_array[ARRAY_MAX];
   int num, count = 0;
   

   if (NULL == (infile = fopen(argv[1], "r"))){
      fprintf(stderr, "%s: can't find file %s\n", argv[0], argv[1]);
      return EXIT_FAILURE;
   }
   
   while (count < ARRAY_MAX && 1 == fscanf(infile, "%d", &my_array[count])) {
      count++;
   }
   fclose(infile);
   
   insertion_sort(my_array, count);

   while (1 == scanf("%d", &num)) {
      binsearch(my_array, count, num)== 1 ? printf("+\n") : printf("-\n");
   }

   return EXIT_SUCCESS;
}
