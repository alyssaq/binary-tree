// Unittests using Google C++ testing framework.
//
// Author: Alyssa Quek


#include "tree.h"
#include "gtest/gtest.h" // Google testing framework.
#include <list>
#include <string>
#include <sstream> //stringstream

static const std::string toString(std::list<int> list) {
  std::ostringstream sstream;
  std::copy(list.begin(), list.end(), std::ostream_iterator<int>(sstream, " "));
  std::string str = sstream.str();
  str.resize(str.size() - 1);
  
  return str;
}

TEST(TreeTest, emptyTree) {
  Tree t;
  EXPECT_TRUE(t.isEmpty());
  EXPECT_EQ(0, t.size());
}

TEST(TreeTest, add) {
  Tree one, many;
  one.add(1);
  EXPECT_FALSE(one.isEmpty());
  EXPECT_EQ(1, one.size());
  many.add(13);
  many.add(3);
  many.add(205);
  EXPECT_FALSE(many.isEmpty());
  EXPECT_EQ(3, many.size());
}

TEST(TreeTest, traversal) {
  Tree t;
  EXPECT_TRUE(t.isEmpty());
  EXPECT_EQ("", t.traversal(TraversalType::PREORDER));
  EXPECT_EQ("", t.traversal(TraversalType::INORDER)); // DFS
  EXPECT_EQ("", t.traversal(TraversalType::POSTORDER));
  EXPECT_EQ("", t.traversal(TraversalType::LEVELORDER)); //BFS
  EXPECT_EQ("", t.traversal(TraversalType::LEVELORDER_SEP)); //BFS

  t.add(13);
  t.add(3);
  t.add(20);
  t.add(7);
  t.add(15);
  t.add(1);
  t.add(4);
  //         13
  //     3        20
  //  1     7    15
  //      4
  EXPECT_EQ("13 3 1 7 4 20 15", t.traversal(TraversalType::PREORDER));
  EXPECT_EQ("1 3 4 7 13 15 20", t.traversal(TraversalType::INORDER)); //Recursive DFS
  EXPECT_EQ("1 4 7 3 15 20 13", t.traversal(TraversalType::POSTORDER));
  EXPECT_EQ("1 3 4 7 13 15 20", t.traversal(TraversalType::DEPTHFIRST)); //Non-recursive DFS
  EXPECT_EQ("13 3 20 1 7 15 4", t.traversal(TraversalType::LEVELORDER)); //BFS
  EXPECT_EQ("13\n3 20\n1 7 15\n4", t.traversal(TraversalType::LEVELORDER_SEP)); //BFS
}

TEST(TreeTest, getRoot) {
  Tree t;
  t.add(2);
  t.add(5);
  EXPECT_EQ(2, t.getRoot()->val);
  EXPECT_EQ(5, t.getRoot()->right->val);
}

TEST(TreeTest, Equality) {
  Tree t1;
  t1.add(3);
  t1.add(4);
  t1.add(5);
  Tree t2;
  t2.add(3);
  EXPECT_TRUE(t1 == t1);
  EXPECT_FALSE(t1 == t2);
  t2.add(4);
  t2.add(5);
  EXPECT_TRUE(t1 == t2);
}

TEST(TreeTest, toList) {
  Tree t1;
  t1.add(3);
  t1.add(4);
  t1.add(5);
  EXPECT_EQ("3 4 5", toString(t1.toList()));
}