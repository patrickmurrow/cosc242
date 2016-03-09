#include <stdio.h>
#include <stdlib.h>
#include "htable.h"

int main(void) {
   FILE *fp;
   char str[200];
   htable my_htable = htable_new(11);
   fp=fopen("test.txt", "w");
   
   while (1 == scanf("%s", &str)) {
      htable_insert(my_htable, str);
   }
 
   htable_print(my_htable, fp);
   htable_free(my_htable);
   
   return EXIT_SUCCESS;
}
