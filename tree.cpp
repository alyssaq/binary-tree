#include "tree.h"
#include <iostream>
#include <new>
#include <sstream>
#include <queue>

using namespace std;

string int2str(int n) {
  ostringstream sstream;
  sstream << n;
  
  return sstream.str();
}

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

  delete node;
}

Tree::~Tree() {
  deleteNode(root);
}

bool Tree::isEmpty() {
  return (root == NULL);
}

//(root-left-right)
void Tree::preorder_travesal(Node *tree, string &str) {
  if (tree == NULL) return;
  str = str + int2str(tree->val) + " ";
  preorder_travesal(tree->left, str);
  preorder_travesal(tree->right, str);
}

//(left-root-right). DFS
void Tree::inorder_travesal(Node *tree, string &str) {
  if (tree == NULL) return;
  inorder_travesal(tree->left, str);
  str = str + int2str(tree->val) + " ";
  inorder_travesal(tree->right, str);
}

//(left-right-root)
void Tree::postorder_travesal(Node *tree, string &str) {
  if (tree == NULL) return;
  postorder_travesal(tree->left, str);
  postorder_travesal(tree->right, str);
  str = str + int2str(tree->val) + " ";
}

//Breadth-first search
void Tree::levelorder_travesal(Node *tree, string &str) {
  if (tree == NULL) return;
  queue<Node *> q;
  Node *node = tree;
  q.push(node);

  while(!q.empty()) {
    node = q.front();
    str = str + int2str(node->val) + " ";
    q.pop();
    if (node->left != NULL) 
      q.push(node->left);
    if (node->right != NULL)
      q.push(node->right);
  }
}

string Tree::traversal(int traversalEnum) {
  string str = "";

  switch (traversalEnum) {
    case TraversalType::PREORDER:
      preorder_travesal(root, str);
      break;
    case TraversalType::INORDER:
      inorder_travesal(root, str);
      break;
    case TraversalType::POSTORDER:
      postorder_travesal(root, str);
      break; 
    default:
      levelorder_travesal(root, str);
      break;
  }

  str.resize (str.size () - 1); //remove trailing space. pop_back() in C++11
  return str;
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
