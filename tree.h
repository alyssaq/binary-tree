/*
* Binary search tree (BST)
* @author: Alyssa Quek 2013
*/

#ifndef TREE_H
#define TREE_H

#include <string>
#include <queue>

struct Node {
  int val;
  Node *left;
  Node *right;
};

namespace TraversalType {
  enum Traversal_E { PREORDER, INORDER, POSTORDER, DEPTHFIRST, LEVELORDER, LEVELORDER_SEP };
}

class Tree {
  Node *root_;
  int size_;

  Node* createNode(int val);
  void deleteNode(Node *node);
 
  // Traversals as per defined in TraversalType enum
  void preorderTraversal(Node *tree, std::string &str) const; 
  void inorderTraversal(Node *tree, std::string &str) const;
  void postorderTraversal(Node *tree, std::string &str) const;

  void depthFirstTraversal(Node *tree, std::string &str) const;
  void levelorderTraversal(Node *tree, std::string &str) const;
  void levelorderWithSeparatorTraversal(Node *tree, std::string &str) const;
  //Level-order Traversal (Breadth-first) 
  // but only deals with a queue level of nodes
  void populateQueueWithNextLvlNodes(std::queue<Node *> &q, std::string &str) const;

public:
  Tree();
  ~Tree();
  bool isEmpty() const;
  unsigned long size() const;
  void add(int val);
  void add(Node* newNode);
  
  std::string traversal(int traversalEnum = 1) const;
};

#endif