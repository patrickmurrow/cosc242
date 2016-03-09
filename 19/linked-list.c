#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "mylib.h"

typedef struct q_item *q_item;

struct q_item {
   double item;
   q_item next;
};

struct queue {
   q_item first;
   q_item last;
   int length;
};

queue queue_new() {
   queue result = emalloc(sizeof * result);
   result->first = NULL;
   result->last = NULL;
   result->length = 0;
   return result;
}

void enqueue(queue q, double item) {
   q_item node = emalloc(sizeof * node);
   node->item = item;
   node->next = NULL;
   if (NULL == q->first) {
      q->first = node;
      q->first->next = NULL;
      q->last = q->first;
      q->length++;
   }
   else if (NULL != q->first) {
      q->last->next = node;
      q->last = node;
      q->length++;
   }
}

double dequeue(queue q) {
   q_item node = emalloc(sizeof * node);
   node = q->first;
   if (q->length > 0) {
      q->length--;
      q->first = node->next;
      return node->item;
   }
   return 0;
}

void queue_print(queue q) {
   int i = 0;
   q_item node = emalloc(sizeof * node);
   node = q->first;
   printf("%.2f\n", node->item);
   for (i = 1; i<q->length; i++){
      printf("%.2f\n", node->next->item);
      node = node->next;
   }
}

int queue_size(queue q) {
   return q->length;
}

queue queue_free(queue q) {
   free(q->first);
   free(q->last);
   free(q);
   return q;
}
