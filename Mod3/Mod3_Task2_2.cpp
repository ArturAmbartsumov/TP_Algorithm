//============================================================================
// Name        : Mod3_Task1_4.cpp
// Author      : Artur Ambartsumov
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Декартево дерево. Сравнение ширины.
//============================================================================

#include <iostream>
#include <queue>
#include <cstdio>

using namespace std;

struct node_t {
  int Key;
  int Priority;
  node_t *left;
  node_t *right;
  node_t(int key = 0, int priority = 0) : Key(key), Priority(priority) {
      left = NULL;
      right = NULL;
  }
};

struct tree_t {
  node_t *root;
  tree_t() {root = NULL;}
};

struct node_and_lvl {
    int level;
    node_t *node;
    node_and_lvl() { level = 0; node = NULL; }
};

//==================================================================================

node_t* Merge(node_t* left, node_t* right) {
    if( left == NULL || right == NULL ) {
        return left == NULL ? right : left;
    }
    if( left->Priority > right->Priority ) {
        left->right = Merge(left->right, right);
        return left;
    }
    right->left = Merge(left, right->left);
    return right;
}

void Split(node_t* currentNode, int key, node_t*& left, node_t*& right) {
    if( currentNode == NULL ) {
        left = NULL;
        right = NULL;
    } else if( currentNode->Key <= key ) {
        // Сокращенный вариант - Split(currentNode->Right, key, currentNode->Right, right);
        node_t* tempLeft = 0;
        node_t* tempRight = 0;
        Split(currentNode->right, key, tempLeft, tempRight);
        right = tempRight;
        left = currentNode;
        left->right = tempLeft;
    } else {
         // Сокращенный вариант - Split(currentNode->Left, key, left, currentNode->Left);
         node_t* tempLeft = 0;
         node_t* tempRight = 0;
         Split(currentNode->left, key, tempLeft, tempRight);
         left = tempLeft;
         right = currentNode;
         right->left = tempRight;
    }
}

node_t* Insert(node_t* root, int key, int priority) {
    node_t* node = new node_t(key, priority);
    node_t* splitLeft = 0;
    node_t* splitRight = 0;
    Split(root, key, splitLeft, splitRight);
    return Merge(Merge(splitLeft, node), splitRight);
}

node_t* Delete(node_t* root, int key)
{
        node_t* splitLeft = 0;
        node_t* splitRight = 0;
        Split(root, key - 1, splitLeft, splitRight);
        node_t* splitRightLeft = 0;
        node_t* splitRightRight = 0;
    Split(splitRight, key, splitRightLeft, splitRightRight);
    delete splitRightLeft;
        return Merge(splitLeft, splitRightRight);
}

//=====================================================================================

node_t* tree_find(node_t* node, int data) {
    node_t *current_node = node;

    while (current_node != NULL) {
      if (current_node->Key > data) {
        if (current_node->left != NULL) {
          current_node = current_node->left;
        } else {
          return current_node;
        }
      } else if (current_node->Key < data) {
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
    tree.root->Key = data;
  } else if (node->Key >= data) {
    node->left = new node_t;
    node->left->Key = data;
  } else { // node->Key < data
    node->right = new node_t;
    node->right->Key = data;
  }
}

//=====================================================================================

//Обход дерева в ширину и проверка его максимальной ширины
int tree_traverse(node_t *node) {
    if (node == NULL) return 0;
    int max_width = 1;
    queue<node_and_lvl> q;

    node_and_lvl current_node;
    current_node.node = node;

    q.push(current_node);
    while(!q.empty()) {

        //Записываем первый и последний элементы
        current_node = q.front();
        node_and_lvl last_node = q.back();

        //Сравниваем уровень первого и последнего
        if (current_node.level == last_node.level) {
            int width = q.size();
            //Сравниваем текущую ширину с максимальной
            if (max_width < width) max_width = width;
        }

        //Достаём из очереди элемент
        q.pop();

        //Обработка элемента
        //printf("%d ", current_node.node->Key);
        //printf("%d  ", current_node.level);

        //Добавление в очередь потомков текущего элемента
        if(current_node.node->left != NULL) {
            node_and_lvl left_node;
            left_node.node = current_node.node->left;
            left_node.level = current_node.level + 1;
            q.push(left_node);
        }
        if(current_node.node->right != NULL) {
            node_and_lvl right_node;
            right_node.node = current_node.node->right;
            right_node.level = current_node.level + 1;
            q.push(right_node);
        }
    }
    //printf("\n%d\n", max_width);
    return max_width;
}

int main() {
    tree_t naive_tree;
    node_t* treap_root = NULL;
    int N = 0;
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        int x;
        int y;
        scanf("%d%d", &x, &y);
        tree_add(naive_tree, x);
        if(treap_root == NULL) {
                treap_root = new node_t(x, y);
        } else {
                treap_root = Insert(treap_root, x, y);
        }
    }
    int a = tree_traverse(naive_tree.root);
    int b = tree_traverse(treap_root);
    printf("%d", (b - a));

    return 0;
}
