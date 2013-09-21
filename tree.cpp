#include "tree.h"
#include <iostream>
#include <new>
#include <sstream>
#include <queue>

using namespace std;

inline string int2str(int n) {
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
void Tree::preorderTravesal(Node *tree, string &str) const {
  if (tree == NULL) return;
  str = str + int2str(tree->val) + " ";
  preorderTravesal(tree->left, str);
  preorderTravesal(tree->right, str);
}

//(left-root-right). Depth-first 
void Tree::inorderTravesal(Node *tree, string &str) const {
  if (tree == NULL) return;
  inorderTravesal(tree->left, str);
  str = str + int2str(tree->val) + " ";
  inorderTravesal(tree->right, str);
}

//(left-right-root)
void Tree::postorderTravesal(Node *tree, string &str) const {
  if (tree == NULL) return;
  postorderTravesal(tree->left, str);
  postorderTravesal(tree->right, str);
  str = str + int2str(tree->val) + " ";
}

//Breadth-first traversal
void Tree::levelorderTravesal(Node *tree, string &str) const {
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
void Tree::populateQueueWithNextLvlNodes(queue<Node *> &q, string &str) const {
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
void Tree::levelorderWithSeparatorTravesal(Node *tree, string &str) const {
  if (tree == NULL) return;
  queue<Node *> q;
  Node *node = tree;
  q.push(node);

  while(!q.empty()) {
    q.push(NULL);
    populateQueueWithNextLvlNodes(q, str);
  }
}

string Tree::traversal(int traversalEnum) const {
  string str = "";
  if (isEmpty()) return str;

  switch (traversalEnum) {
    case TraversalType::PREORDER:
      preorderTravesal(root_, str);
      break;
    case TraversalType::INORDER:
      inorderTravesal(root_, str);
      break;
    case TraversalType::POSTORDER:
      postorderTravesal(root_, str);
      break; 
    case TraversalType::LEVELORDER_SEP:
      levelorderWithSeparatorTravesal(root_, str);
      break;
    default:
      levelorderTravesal(root_, str);
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

