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
  size_++;

  return node;
}

Tree::Tree() {
  root_ = NULL;
  size_ = 0;
}

void Tree::deleteNode(Node *node) {
  if (node == NULL) return;
  deleteNode(node->left);
  deleteNode(node->right);

  delete node;
}

Tree::~Tree() {
  deleteNode(root_);
}

bool Tree::isEmpty() const {
  return (root_ == NULL);
}

//(root-left-right)
void Tree::preorder_travesal(Node *tree, string &str) {
  if (tree == NULL) return;
  str = str + int2str(tree->val) + " ";
  preorder_travesal(tree->left, str);
  preorder_travesal(tree->right, str);
}

//(left-root-right). Depth-first 
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

//Breadth-first traversal
void Tree::levelorder_travesal(Node *tree, string &str) {
  if (tree == NULL) return;
  queue<Node *> q, nextLvlQ;
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

//Deals with nodes at a level in the tree
void Tree::populateQueueWithNextLvlNodes(queue<Node *> &q, string &str) {
  while(q.front() != NULL) {
    Node *node = q.front();
    str = str + int2str(node->val) + " ";
    if (node->left != NULL) 
      q.push(node->left);
    if (node->right != NULL)
      q.push(node->right);
    q.pop();
  }
  q.pop();
  str.resize (str.size () - 1); //remove trailing space. pop_back() in C++11
  str += "\n";
}

//Breadth-first traversal with new-line between each level
void Tree::levelorder_withSeparator_travesal(Node *tree, string &str) {
  if (tree == NULL) return;
  queue<Node *> q;
  Node *node = tree;
  q.push(node);

  while(!q.empty()) {
    q.push(NULL);
    populateQueueWithNextLvlNodes(q, str);
  }
}

string Tree::traversal(int traversalEnum) {
  string str = "";
  if (isEmpty()) return str;

  switch (traversalEnum) {
    case TraversalType::PREORDER:
      preorder_travesal(root_, str);
      break;
    case TraversalType::INORDER:
      inorder_travesal(root_, str);
      break;
    case TraversalType::POSTORDER:
      postorder_travesal(root_, str);
      break; 
    case TraversalType::LEVELORDER_SEP:
      levelorder_withSeparator_travesal(root_, str);
      break;
    default:
      levelorder_travesal(root_, str);
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
  if (isEmpty()) {
    root_ = newNode;
  } else {
    Node *parent = findPredecessorToAdd(NULL, root_, newNode);

    if (newNode->val < parent->val) {
      parent->left = newNode;
    } else {
      parent->right = newNode;
    }
  }
}

void Tree::add(int val) {
  Node *newNode = createNode(val);
  add(newNode);
}

unsigned long Tree::size() const{
  return size_;
}

