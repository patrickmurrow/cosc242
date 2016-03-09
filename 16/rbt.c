#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rbt.h"
#include "mylib.h"

#define IS_BLACK(x) ((NULL == (x)) || (BLACK == (x)->colour))
#define IS_RED(x) ((NULL != (x)) && (RED == (x)->colour))

typedef enum { RED, BLACK } rbt_colour;

struct rbt_node {
   char *key;
   rbt_colour colour;
   rbt left;
   rbt right;
};

int rbt_search(rbt b, char *str){
   if (b == NULL){
      return 0;
   }
   else if (strcmp(str, b->key)==0){
      return 1;
   }
   else if (strcmp(str, b->key)<0){
      return rbt_search(b->left, str);
   }
   else if (strcmp(str, b->key)>0){
      return rbt_search(b->right, str);
   }
   return 0;
}

rbt rbt_insert(rbt b, char *str){
   if (b == NULL){
      b = emalloc(sizeof *b);
      b->key = emalloc((strlen(str)+1) * sizeof str[0]);
      strcpy(b->key, str);
      b->colour = RED;
   }
   else if (strcmp(str, b->key)==0){
      return b;
   }
   else if (strcmp(str, b->key)<0){
      b->left = rbt_insert(b->left, str);
   }
   else if (strcmp(str, b->key)>0){
      b->right = rbt_insert(b->right, str);
   }
   b = rbt_fix(b);
   return b;
}

rbt rbt_delete(rbt b, char *str) {
   if (0 == rbt_search(b, str)) {
      return b;
   }
   else if (strcmp(str, b->key)==0){
      if (b->left == NULL && b->right != NULL){
         free(b->key);
         free(b);
         b = b->right;
      }
      else if (b->left != NULL && b->right == NULL){
         free(b->key);
         free(b);
         b = b->left;
      }
      else if (b->left == NULL && b->right == NULL){
         free(b->key);
         free(b);
         b = NULL;
      }
      else {
         rbt temp  = b->right;
         while (temp->left != NULL){
            temp = temp->left;
         }
         b = temp;
         b = rbt_delete(b, temp->key);
      }
   }
   else if (strcmp(str, b->key)<0){
      b->left = rbt_delete(b->left, str);
   }
   else if (strcmp(str, b->key)>0){
      b->right = rbt_delete(b->right, str);
   }
   return b;
}


rbt rbt_new(){
   return NULL;
}


void rbt_inorder(rbt b, void f(char *)){
   if (b == NULL){
      return;
   }
   rbt_inorder(b->left, f);
   f(b->key);
   if (IS_RED(b)){
      f("-> RED ");
   }
   else if (IS_BLACK(b)){
      f("-> BLACK ");
   }
   rbt_inorder(b->right, f);
}

void rbt_preorder(rbt b, void f(char *)){
   if (b == NULL){
      return;
   }
   f(b->key);
   if (IS_RED(b)){
      f("-> RED ");
   }
   else if (IS_BLACK(b)){
      f("-> BLACK ");
   }
   rbt_preorder(b->left, f);
   rbt_preorder(b->right, f);

}

rbt right_rotate(rbt b) {
   rbt temp = b;
   b = b->left;
   temp->left = b->right;
   b->right = temp;
   return b;
}

rbt left_rotate(rbt b) {
   rbt temp = b;
   b = b->right;
   temp->right = b->left;
   b->left = temp;
   return b;
}

rbt rbt_fix(rbt b) {
   /*if (b->left != NULL && b->right != NULL) {*/
      if (IS_RED(b->left)){
         if (IS_RED(b->left->left)){
            if (IS_RED(b->right)){
               b->colour = RED;
               b->left->colour = BLACK;
               b->right->colour = BLACK;
            }
            else if (IS_BLACK(b->right)){
               b = right_rotate(b);
               b->colour = BLACK;
               b->right->colour = RED;
            }
         }
         else if (IS_RED(b->left->right)) {
            if (IS_RED(b->right)){
               b->colour = RED;
               b->left->colour = BLACK;
               b->right->colour = BLACK;
            }
            else if (IS_BLACK(b->right)) {
               b->left = left_rotate(b->left);
               b = right_rotate(b);
               b->colour = BLACK;
               b->right->colour = RED;
            }
         }
      }
      else if (IS_RED(b->right)){
         if (IS_RED(b->right->left)){
            if (IS_RED(b->left)){
               b->colour = RED;
               b->left->colour = BLACK;
               b->right->colour = BLACK;
            }
            else if (IS_BLACK(b->left)){
               b->right = right_rotate(b->right);
               b = left_rotate(b);
               b->colour = BLACK;
               b->left->colour = RED;
            }
         }
         else if (IS_RED(b->right->right)) {
            if (IS_RED(b->left)){
               b->colour = RED;
               b->left->colour= BLACK;
               b->right->colour = BLACK;
            }
            else if (IS_BLACK(b->right)) {
               b = left_rotate(b);
               b->colour = BLACK;
               b->left->colour = RED;
            }
         }
   
      }
      /*}*/
   return b;
}
   
