//============================================================================
// Name        : Mod3_Task1_4.cpp
// Author      : Artur Ambartsumov
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Дерево. Level order.
//============================================================================

#include <iostream>
#include <queue>
#include <cstdio>

using namespace std;

struct node_t {
  int data;
  node_t *left;
  node_t *right;
  node_t() {data = 0; left = NULL; right = NULL;}
};

struct tree_t {
  node_t *root;
  tree_t() {root = NULL;}
};


node_t* tree_find(node_t* node, int data) {
  node_t *current_node = node;

  while (current_node != NULL) {
    if (current_node->data > data) {
      if (current_node->left != NULL) {
        current_node = current_node->left;
      } else {
        return current_node;
      }
    } else if (current_node->data < data) {
      if (current_node->right != NULL) {
        current_node = current_node->right;
      } else {
        return current_node;
      }
    } else {
      return current_node;
    }
  }

  return NULL;
}

void tree_add(tree_t &tree, int data) {
  node_t *node = tree_find(tree.root, data);
  if (node == NULL) {
    tree.root = new node_t;
    tree.root->data = data;
  } else if (node->data >= data) {
    node->left = new node_t;
    node->left->data = data;
  } else { // node->data < data
    node->right = new node_t;
    node->right->data = data;
  }
}

void print_int(int data) {
    printf("%d ", data);
}

void tree_traverse(node_t *node) {
  if (node == NULL) return;
  queue<node_t*> q;
    q.push(node);
    while(!q.empty()) {
        node_t* current_node = q.front();
        q.pop();
        printf("%d ", current_node->data);
        if(current_node->left != NULL)
            q.push(current_node->left );
        if(current_node->right != NULL)
            q.push(current_node->right);
    }
}

int main() {
    tree_t tree;
    int N = 0;
    scanf("%d", &N);
    for (int i = 0; i <N; ++i) {
        int temp;
        scanf("%d", &temp);
        tree_add(tree, temp);
    }
    tree_traverse(tree.root);

    return 0;
}
