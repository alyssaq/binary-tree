#include "tree.h"
#include <iostream>
#include <new>

using namespace std;

Node* Tree::createNode(int val) {
  Node *node = new (nothrow) Node;
  node->left = NULL;
  node->right = NULL;
  node->val = val;
  _size++;

  return node;
}

Tree::Tree() {
  root = NULL;
  _size = 0;
}

void Tree::deleteNode(Node *node) {
  if (node == NULL) return;

  deleteNode(node->left);
  deleteNode(node->right);
  cout << "deleting: " << node->val << endl;
  delete node;
}

Tree::~Tree() {
  deleteNode(root);
}

bool Tree::isEmpty() {
  return (root == NULL);
}

void traversal() {

}

Node* findPredecessor(Node *parent, Node *node, int val) {
  if (node == NULL || (node->val == val && parent == NULL)) return NULL;
  if (node->val == val && parent != NULL) return parent;
  cout << "val: " << node->val << endl;

  Node *leftNode = NULL, *rightNode = NULL;
  leftNode = findPredecessor(node, node->left, val);
  rightNode = findPredecessor(node, node->right, val);

  if (leftNode != NULL) return leftNode;
  if (rightNode != NULL) return rightNode;
  return NULL;
}

Node* findPredecessorToAdd(Node *parent, Node* node, Node* newNode) {
  if (node == NULL) return parent;
  Node *predecessor = NULL;
  if (newNode->val < node->val) {
    predecessor = findPredecessorToAdd(node, node->left, newNode);
  } else {
    predecessor = findPredecessorToAdd(node, node->right, newNode);
  }
  return predecessor;
}

void Tree::add(Node* newNode) {
  if (root == NULL) {
    root = newNode;
  } else {
    cout << "addNode: " << newNode->val << endl;
    Node *parent = findPredecessorToAdd(NULL, root, newNode);

    if (newNode->val < parent->val) {
      parent->left = newNode;
    } else {
      parent->right = newNode;
    }
  }
}

void Tree::add(int val) {
  if (root == NULL) {
    root = createNode(val);
  } else {
    Node *newNode = createNode(val);
    add(newNode);
  }
}

int Tree::size() {
  return _size;
}

//         13
//     10      18
//    5 11   8
void createTree() {
  Tree t;
  //t.add
}
