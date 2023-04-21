#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
  TreeMap* tree = (TreeMap*) malloc(sizeof(TreeMap));
  tree->root = NULL;
  tree->lower_than = lower_than;
  return tree;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
  if (searchTreeMap(tree, key) == NULL){
    TreeNode *node = createTreeNode(key, value);
    
    TreeNode* current = tree->root;
    while(current != NULL){
      if(tree->lower_than(key, current->pair->key)){
        if (current->left == NULL){
          current->left = node;
          return;  
        }
        current = current->left;
      }
      else{
        if (current->right == NULL){
          current->right = node;
          return;
        }
        current = current->right;
      }
    }
  }
}

TreeNode * minimum(TreeNode * x){
  if (x == NULL) return NULL;
  TreeNode *minimun;

  while(x != NULL){
    minimun = x;
    x = x->left;
  }

    return minimun;
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
  if (tree->root == NULL) return NULL;
  
  TreeNode* current = tree->root;
  while(current != NULL){
    if(is_equal(tree, current->pair->key, key) == 1){
      tree->current = current;
      return current->pair;
    }
    if(tree->lower_than(current->pair->key, key)){
      current = current->right;
    }
    else{
      current = current->left;
    }
  }
  return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
