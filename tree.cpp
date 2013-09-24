#include "tree.h"
#include <iostream>
#include <new>
#include <sstream>
#include <queue>
#include <stack>

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
void Tree::preorderTraversal(Node *tree, string &str) const {
  if (tree == NULL) return;
  str = str + int2str(tree->val) + " ";
  preorderTraversal(tree->left, str);
  preorderTraversal(tree->right, str);
}

//(left-root-right). Depth-first 
void Tree::inorderTraversal(Node *tree, string &str) const {
  if (tree == NULL) return;
  inorderTraversal(tree->left, str);
  str = str + int2str(tree->val) + " ";
  inorderTraversal(tree->right, str);
}

//(left-right-root)
void Tree::postorderTraversal(Node *tree, string &str) const {
  if (tree == NULL) return;
  postorderTraversal(tree->left, str);
  postorderTraversal(tree->right, str);
  str = str + int2str(tree->val) + " ";
}

//Non-recursive DFS
void Tree::depthFirstTraversal(Node *tree, string &str) const {
  if (tree == NULL) return;
  //bool to indicate whether node has been checked
  stack<pair<bool, Node*> > stack; 
  Node *node = tree;
  stack.push(make_pair(false, node));

  while (!stack.empty()) {
    pair<bool, Node*> p = stack.top();
    node = p.second;
    stack.pop();

    if(p.first) {
      str += int2str(node->val) + " ";
    } else {
      if (node->right) 
        stack.push(make_pair(false, node->right));
      p.first = true;
      stack.push(p);
      if (node->left)
        stack.push(make_pair(false, node->left));
    }
  }
}

// Extract the front node of the given queue
//  Add its children into the queue
// @precondition: given queue has at least one Node 
// @return string: front node val 
string extractFrontNodeValAppendChildren(queue<Node *> &q) {
  Node *node = q.front();
  q.pop(); //remove the node from queue
  
  //Add children into the queue
  if (node->left != NULL) 
    q.push(node->left);
  if (node->right != NULL)
    q.push(node->right);

  return int2str(node->val);
}

//Breadth-first traversal
void Tree::levelorderTraversal(Node *tree, string &str) const {
  if (tree == NULL) return;
  queue<Node *> q, nextLvlQ;
  Node *node = tree;
  q.push(node);

  while(!q.empty()) {
    str += extractFrontNodeValAppendChildren(q) + " ";
  }
}

//Breadth-first traversal with new-line between each level
void Tree::levelorderWithSeparatorTraversal(Node *tree, string &str) const {
  if (tree == NULL) return;
  queue<Node *> q;
  Node *node = tree;
  q.push(node);

  while(!q.empty()) {
    q.push(NULL); //add a dud NULL node between each level
    while(q.front() != NULL) {
      str += extractFrontNodeValAppendChildren(q) + " ";
    }
    q.pop(); //remove dud NULL node
    str.resize (str.size () - 1); //remove trailing space. pop_back() in C++11
    str += "\n";
  }
}

string Tree::traversal(int traversalEnum) const {
  string str = "";
  if (isEmpty()) return str;

  switch (traversalEnum) {
    case TraversalType::PREORDER:
      preorderTraversal(root_, str);
      break;
    case TraversalType::INORDER:
      inorderTraversal(root_, str);
      break;
    case TraversalType::POSTORDER:
      postorderTraversal(root_, str);
      break; 
    case TraversalType::LEVELORDER_SEP:
      levelorderWithSeparatorTraversal(root_, str);
      break;
    case TraversalType::DEPTHFIRST:
      depthFirstTraversal(root_, str);
      break;
    default:
      levelorderTraversal(root_, str);
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

Node* findPredecessorToAdd(Node *parent, Node* node, int val) {
  if (node == NULL) return parent;
  Node *predecessor = NULL;
  if (val < node->val) {
    predecessor = findPredecessorToAdd(node, node->left, val);
  } else {
    predecessor = findPredecessorToAdd(node, node->right, val);
  }
  return predecessor;
}

void Tree::add(Node* newNode) {
  if (isEmpty()) {
    root_ = newNode;
  } else {
    int val = newNode->val;
    Node *parent = findPredecessorToAdd(NULL, root_, val);

    if (val < parent->val) {
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

