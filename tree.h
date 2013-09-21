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
  enum Traversal_E { PREORDER, INORDER, POSTORDER, LEVELORDER, LEVELORDER_SEP };
}

class Tree {
  Node *root_;
  int size_;

  Node* createNode(int val);
  void deleteNode(Node *node);
 
  // Travesals as per defined in TraversalType enum
  void preorderTravesal(Node *tree, std::string &str); 
  void inorderTravesal(Node *tree, std::string &str);
  void postorderTravesal(Node *tree, std::string &str);
  void levelorderTravesal(Node *tree, std::string &str);
  void levelorderWithSeparatorTravesal(Node *tree, std::string &str);
  //Level-order travesal (Breadth-first) 
  // but only deals with a queue level of nodes
  void populateQueueWithNextLvlNodes(std::queue<Node *> &q, std::string &str);
public:

  Tree();
  ~Tree();
  bool isEmpty() const;
  unsigned long size() const;
  void add(int val);
  void add(Node* newNode);
  
  std::string traversal(int traversalEnum = 1);
};

#endif