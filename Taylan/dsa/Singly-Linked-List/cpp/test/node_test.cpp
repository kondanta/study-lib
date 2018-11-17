#include <gtest/gtest.h>
#include "node.hpp"

// TestCaseName, TestName
// ASSERT_EQ(6, squareRoot(36.0));
//TEST(SquareRootTest, PositiveNos) { 
//}
class NodeTest : public ::testing::Test {
protected:
  // void SetUp() override {
  //   // some logic
  // }
  Node<int> _obj;
};

TEST_F(NodeTest, IsNullInitially){
  EXPECT_EQ(nullptr, _obj.getNext());
}

TEST_F(NodeTest, HasNextInit){
  ASSERT_FALSE(_obj.hasNext());
}

TEST_F(NodeTest, HasNextHavingANextObj){
  Node<int> *o1 = new Node<int>();
  _obj.setNext(o1);
  ASSERT_TRUE(_obj.hasNext());
  delete o1;
}
