#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "mylib.h"

struct queue {
   double *items;
   int head;
   int capacity;
   int num_items;
};

queue queue_new() {
   queue result = emalloc(sizeof * result);
   result->capacity = 5;
   result->head = 0;
   result->num_items = 0;
   result->items = emalloc(result->capacity * sizeof result->items[0]);
   return result;
}

void enqueue(queue q, double item) {
   int index = 0;
   if (q->num_items < q->capacity) {
      index = q->head + q->num_items % q->capacity;
      q->items[index] = item;
      q->num_items++;
   }
}

double dequeue(queue q) {
   int temp = q->head;
   if (q->num_items > 0) {
      q->head++;
      q->num_items--;
      return q->items[temp];
   }
   return 0;
}

void queue_print(queue q) {
   int i = 0;
   for (i = q->head; i<q->capacity; i++) {
      if (q->items[i] != 0){
         printf("%.2f\n", q->items[i]);
      }
   }
}

int queue_size(queue q) {
   return q->num_items;
}

queue queue_free(queue q) {
   free(q->items);
   free(q);
   return q;
}
