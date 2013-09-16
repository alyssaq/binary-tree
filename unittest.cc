// Unittests using Google C++ testing framework.
//
// Author: Alyssa Quek


#include "tree.h"
#include "gtest/gtest.h" // Google testing framework.

// Use the TEST macro to define your tests.
//
// TEST has two parameters: the test case name and the test name.
// After using the macro, you should define your test logic between a
// pair of braces.  You can use a bunch of macros to indicate the
// success or failure of a test.  EXPECT_TRUE and EXPECT_EQ are
// examples of such macros.  For a complete list, see gtest.h.
//
// <TechnicalDetails>
//
// In Google Test, tests are grouped into test cases.  This is how we
// keep test code organized.  You should put logically related tests
// into the same test case.
//
// The test case name and the test name should both be valid C++
// identifiers.  And you should not use underscore (_) in the names.
//
// Google Test guarantees that each test you define is run exactly
// once, but it makes no guarantee on the order the tests are
// executed.  Therefore, you should write your tests in such a way
// that their results don't depend on their order.
//
// </TechnicalDetails>

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
  t.add(13);
  t.add(3);
  t.add(20);
  t.add(7);
  t.add(15);
  t.add(1);
  t.add(4);
  //        13
  //    3        20
  //  1    7    15
  //     4
  EXPECT_EQ("13 3 1 7 4 20 15", t.traversal(TraversalType::PREORDER));
  EXPECT_EQ("1 3 4 7 13 15 20", t.traversal(TraversalType::INORDER)); // DFS
  EXPECT_EQ("1 4 7 3 15 20 13", t.traversal(TraversalType::POSTORDER));
  EXPECT_EQ("13 3 20 1 7 15 4", t.traversal(TraversalType::LEVELORDER)); //BFS
  EXPECT_EQ("13\n3 20\n1 7 15\n4", t.traversal(TraversalType::LEVELORDER_SEP)); //BFS
}
// Call RUN_ALL_TESTS() in main().
//
// We do this by linking in src/gtest_main.cc file, which consists of
// a main() function which calls RUN_ALL_TESTS() for us.⁄
//
// This runs all the tests you've defined, prints the result, and
// returns 0 if successful, or 1 otherwise.
//
// RUN_ALL_TESTS() macro magically knows about all the defined tests
