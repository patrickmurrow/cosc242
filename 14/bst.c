#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"
#include "mylib.h"

struct bst_node {
   char *key;
   bst left;
   bst right;
};

int bst_search(bst b, char *str){
   if (b == NULL){
      return 0;
   }
   else if (strcmp(str, b->key)==0){
      return 1;
   }
   else if (strcmp(str, b->key)<0){
      return bst_search(b->left, str);
   }
   else if (strcmp(str, b->key)>0){
      return bst_search(b->right, str);
   }
   return 0;
}

bst bst_insert(bst b, char *str){
   if (b == NULL){
      b = emalloc(sizeof *b);
      b->key = emalloc((strlen(str)+1) * sizeof str[0]);
      strcpy(b->key, str);
      return b;
   }
   else if (strcmp(str, b->key)==0){
      return NULL;
   }
   else if (strcmp(str, b->key)<0){
      b->left = bst_insert(b->left, str);
   }
   else if (strcmp(str, b->key)>0){
      b->right = bst_insert(b->right, str);
   }
   return b;
}

bst bst_delete(bst b, char *str) {
   if (0 == bst_search(b, str)) {
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
         bst temp  = b->right;
         while (temp->left != NULL){
            temp = temp->left;
         }
         b = temp;
         b = bst_delete(b, temp->key);
      }
   }
   else if (strcmp(str, b->key)<0){
      b->left = bst_delete(b->left, str);
   }
   else if (strcmp(str, b->key)>0){
      b->right = bst_delete(b->right, str);
   }
   return b;
}


bst bst_new(){
   return NULL;
}


void bst_inorder(bst b, void f(char *)){
   if (b == NULL){
      return;
   }
   bst_inorder(b->left, f);
   f(b->key);
   bst_inorder(b->right, f);
}

void bst_preorder(bst b, void f(char *str)){
   if (b == NULL){
      return;
   }
   f(b->key);
   bst_preorder(b->left, f);
   bst_preorder(b->right, f);
}
   
   
bst bst_delete(bst b, char *str);
