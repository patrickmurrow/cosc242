#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int main (int argc, char **argv){
   printf("LCS: %d\n", LCS(argv[0], argv[1]));
}

int LCS(char *a, char *b){
   int i = strlen(a[0]);
   int j = strlen(b[1]);

   char *aa = NULL;
   char *bb = NULL;

   if (j == 0 || i == 0){  
      return 0;
   }

   strcpy(a, aa, i-1);
   aa[i-1] = '\0';

   strcpy(b, bb, i-1);
   bb[i-1] = '\0';

   if (strcmp(a[i], b[i]) == 0){
      return LCS(aa, bb) + 1;
   }

   else{
      if (LCS(aa, b) > LCS(a, bb)){
         return LCS(aa, b);
      }
      else{
         return LCS(a, bb);
      }
   }
}


         
