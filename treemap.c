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
          current->left->parent = current;
          tree->current = node;
          return;  
        }
        current = current->left;
      }
      else{
        if (current->right == NULL){
          current->right = node;
          current->right->parent = current;
          tree->current = node;
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
  if (searchTreeMap(tree, node->pair->key) != NULL){
    if (node->left == NULL && node->right == NULL){
      
      if(node->parent->left == node){
        node->parent->left = NULL;
      }
      if(node->parent->right == node){
        node->parent->right = NULL;
      }
      return;
    }
    if (node->left == NULL && node->right != NULL){
      node->right->parent = node->parent;
      return;
    }
    if (node->left != NULL && node->right == NULL){
      node->left->parent = node->parent;
      if(node->parent->left == node){
        node->parent->left = node->left;
      } else {
        node->parent->right = node->left;
      }
      return;
    }
    if (node->left != NULL && node->right != NULL){
      TreeNode *aux = minimum(node->right);
      node->pair = aux->pair;
      removeNode(tree,aux);
    }
  }
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
  TreeNode* node;
  if (tree->root == NULL) return NULL;
  TreeNode* current = tree->root;
    
  while(current != NULL){
    if(is_equal(tree, current->pair->key, key) == 1){
      return current->pair;
    }
    if(tree->lower_than(key,current->pair->key) == 1){
    node = current;
    current = current->left;
    }
    else{
    current = current->right;
    }
  }
  if(node != NULL) return node->pair;
  else return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
  if (tree->root == NULL) return NULL;
  else{
    TreeNode *min = minimum(tree->root);
    return min->pair;
  } 
}

Pair * nextTreeMap(TreeMap * tree) {
  if (tree->root == NULL) return NULL;

  TreeNode *current = tree->current;
  if (current == NULL) {
    current = minimum(tree->root);
    tree->current = current;
    return current->pair;
  }

  if (current->right != NULL) {
    current = minimum(current->right);
    tree->current = current;
    return current->pair;
  } else {
    TreeNode *parent = current->parent;
    while (parent != NULL && current == parent->right) {
      current = parent;
      parent = parent->parent;
    }
    if (parent == NULL) {
      return NULL;
    } else {
      tree->current = parent;
      return parent->pair;
    }
  }
}
