/*
* Binary tree class
* @author: Alyssa Quek 2013
*/

#ifndef TREE_H
#define TREE_H

struct Node {
  int val;
  Node *left;
  Node *right;
};

class Tree {
  Node *root;
  int _size;
  Node* createNode(int val);
  void deleteNode(Node *node);

public:
  Tree();
  ~Tree();
  bool isEmpty();
  int size();
  void add(int val);
  void add(Node* newNode);

};

#endif