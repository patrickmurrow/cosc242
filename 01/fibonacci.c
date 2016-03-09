#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main(void) {
   /* variable declarations */
   int i = 0;
   int g = 1;
   int f = 0;
   int j = 0;
   int count = 0;
   /* a familiar "for loop" */
   for(i = 0;i <= 40; i++) {
      printf("%10d", g); /* sqrt defined in math.h */
      count++;
      j = g;
      g = j + f;
      f = j;
      if (count%5==0){
         printf("\n");
      }
   }
   return EXIT_SUCCESS; /* defined in stdlib.h */
}
