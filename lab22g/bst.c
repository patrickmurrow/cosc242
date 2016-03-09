#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"
#include "mylib.h"

struct bst_node {
   bst left;
   bst right;
   char *key;
};

int bst_search(bst b, char *str){
   if (NULL == b){
      return 0;
   }
   if (strcmp(str, b->key) == 0){
      return 1;
   }
   else if (strcmp(str, b->key) < 0){
      return bst_search(b->left, str);
   }
   else if (strcmp(str, b->key) > 0){
      return bst_search(b->right, str);
   }
   return 0;
}

bst bst_insert(bst b, char *str){
   if (NULL == b){
      b = emalloc(sizeof * b);
      b->key = emalloc((strlen(str)+1) * sizeof str[0]);
      b->left = NULL;
      b->right = NULL;
      strcpy(b->key, str);
      return b;
   }
   if (strcmp(str, b->key) == 0){
      return NULL;
   }
   else if (strcmp(str, b->key) < 0){
      b->left = bst_insert(b->left, str);
   }
   else if (strcmp(str, b->key) > 0){
      b->right = bst_insert(b->right, str);
   }
   return b;
}
   
bst bst_new(){
   return NULL;
}

void bst_inorder(bst b, void f(char *str)){
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

bst bst_free(bst b){
   if (b == NULL){
      return b;
   }
   free(b->key);
   bst_free(b->left);
   bst_free(b->right);
   free(b);
   return b;
}



