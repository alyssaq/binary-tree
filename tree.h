/*
* Binary tree class
* @author: Alyssa Quek 2013
*/

#ifndef TREE_H
#define TREE_H

#include <string>

struct Node {
  int val;
  Node *left;
  Node *right;
};

namespace TraversalType {
  enum Traversal_E { PREORDER, INORDER, POSTORDER, LEVELORDER };
}

class Tree {
  Node *root;
  int _size;

  Node* createNode(int val);
  void deleteNode(Node *node);
 
  // Travesals as per defined in TraversalType enum
  void preorder_travesal(Node *tree, std::string &str); 
  void inorder_travesal(Node *tree, std::string &str);
  void postorder_travesal(Node *tree, std::string &str);
  void levelorder_travesal(Node *tree, std::string &str);

public:

  Tree();
  ~Tree();
  bool isEmpty();
  int size();
  void add(int val);
  void add(Node* newNode);
  
  std::string traversal(int traversalEnum = 1);
};

#endif