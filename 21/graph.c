#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#include "graph.h"
#include "queue.h"


typedef enum { UNVISITED, VISITED_SELF, VISITED_DESCENDANTS } state_t;

struct vertex {
   int predecessor;
   int distance;
   state_t state;
   int finish;
};

struct graphrec {
   vertex *vertices;
   int **edges;
   int size;
};

/* Creates a new graph with specified size
 *
 * @param size of graph
 * @return result - new allocated graph
 */
graph graph_new(int size){
   int i = 0;
   graph result = emalloc(sizeof * result);
   result->size = size;
   result->vertices = emalloc(result->size * sizeof result->vertices[0]);
   result->edges = (int **)emalloc(result->size * sizeof(int*));
   for(i = 0; i < result->size; i++){
      result->edges[i] = (int *)malloc(result->size * sizeof(int));
   }
   return result;
}

/* Adds an edge to the graph in one direction
 *
 * @param g - graph, vertex u and v
 */
void graph_add_edge(graph g, int u, int v){
   g->edges[u][v] = 1;

}

/* Adds a bidirectional edge to the graph
 *
 * @param g - graph, vertex u and v
 */
void graph_bi_add_edge(graph g, int u, int v){
   g->edges[u][v] = 1;
   g->edges[v][u] = 1;

}

/* Prints adjacent vertices, distances and predecessors
 *
 * @param g - graph
 */
void graph_print(graph g){
   int i, x;
   printf("adjacency list:\n");
   for(i = 0; i < g->size; i++){
      printf("%d | ", i);
      for(x = 0; x < g->size; x++){
         if(g->edges[i][x] == 1){
            printf("%d ", x);
         }
      }
      printf("\n");
   }
   printf("\nvertex\tdistance pred\n");
   for(i = 0; i< g->size; i++){
      printf("%d\t%d\t %d\n", i, g->vertices[i].distance, g->vertices[i].predecessor);
   }
}

/* Performs a breadth first search on the tree
 *
 * @param g - graph, source - the vertex to find the distances from
 */
void graph_bfs(graph g, int source){
   queue q = queue_new();
   int i = 0;
   for (i = 0; i < g->size; i++){
      g->vertices[i].state = UNVISITED;
      g->vertices[i].distance = -1;
      g->vertices[i].predecessor = -1;
   }
   g->vertices[source].state = VISITED_SELF;
   g->vertices[source].distance = 0;
   enqueue(q, source);
   while(queue_size(q) > 0){
      int u = dequeue(q);
      for (i = 0; i < g->size; i++){
         if (g->edges[u][i] ==1 && g->vertices[i].state == UNVISITED){
            g->vertices[i].state = VISITED_SELF;
            g->vertices[i].distance = 1 + g->vertices[u].distance;
            g->vertices[i].predecessor = u;
            enqueue(q, i);
         }
      }
      g->vertices[u].state = VISITED_DESCENDANTS;
   }
}

/* Frees arrays and graph
 *
 * @param g - graph
 */
void graph_free(graph g){
   int i = 0;
   free(g->vertices);
   for (i = 0; i < g->size; i++){
      free(g->edges[i]);
   }
   free(g->edges);
   free(g);
}
