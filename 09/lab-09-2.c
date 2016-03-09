#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main ( int argc, char *argv[] ){
   int num = atoi(argv[1]);
   int i, n;
   for (i = 1; i < num; i++) {
      n = rand()%100 + 1;
      printf("%d\n", n);
   }
   return EXIT_SUCCESS;
}
