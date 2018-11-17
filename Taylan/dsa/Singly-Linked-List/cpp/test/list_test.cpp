#include <gtest/gtest.h>
#include "list.hpp"

class ListTest : public ::testing::Test {
public:
  List *_lst = new List();
};

TEST_F(ListTest, NullHeaderInitially){
  EXPECT_TRUE(_lst->isEmpty());
}

TEST_F(ListTest, InitialSizeShouldBeZero){
  EXPECT_EQ(0, _lst->size());
}

TEST_F(ListTest, SizeShouldBeOneWhenHeaderIsAvailable){
  _lst->append(5);
  EXPECT_EQ(1, _lst->size());
}

TEST_F(ListTest, SizeShouldBeDynamic){
  for(int i = 0; i < 10; ++i){
    _lst->append(i);
  }
  EXPECT_EQ(10, _lst->size());
}
TEST_F(ListTest, InsertBackToTheList){
  _lst->append(5);
  _lst->append(7);
  EXPECT_FALSE(_lst->isEmpty());
  EXPECT_EQ(7, _lst->getTailValue());
}

TEST_F(ListTest, TestIsAppendWork){
  for(int i = 0; i < 10; ++i){
    _lst->append(i*i);
  }
  EXPECT_EQ(81, _lst->getTailValue());
}

TEST_F(ListTest, GetListsHeadNodesValue){
  _lst->initList(2);
  int value = _lst->getHeadValue();
  EXPECT_EQ(2, value);
}

TEST_F(ListTest, InitList){
  ASSERT_TRUE(_lst->isEmpty());
  // then
  // Init list with a value;
  _lst->initList(2);
  ASSERT_FALSE(_lst->isEmpty());
  ASSERT_EQ(2, _lst->getHeadValue());
}
