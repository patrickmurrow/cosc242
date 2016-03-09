#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main(void) {
   int d = 0;
   int i = 0;
   int x = 0;
   graph my_graph = NULL;


   if (1 == scanf("%d", &d)) {
      my_graph = graph_new(d);
   }
   while (2 == scanf("%d%d", &i, &x)) {
      graph_bi_add_edge(my_graph, i, x);
   }
   graph_bfs(my_graph, 1);
   graph_print(my_graph);
   graph_free(my_graph);
   return EXIT_SUCCESS;
}
