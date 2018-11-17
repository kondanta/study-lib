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
  _lst->insertBack(5);
  EXPECT_EQ(1, _lst->size());
}

TEST_F(ListTest, SizeShouldBeDynamic){
  for(int i = 0; i < 10; ++i){
    _lst->insertBack(i);
  }
  EXPECT_EQ(10, _lst->size());
}
TEST_F(ListTest, InsertBackToTheList){
  _lst->insertBack(5);
  EXPECT_FALSE(_lst->isEmpty());
}
