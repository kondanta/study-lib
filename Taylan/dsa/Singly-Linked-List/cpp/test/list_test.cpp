#include <gtest/gtest.h>
#include <climits>
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
TEST_F(ListTest, InitTestWithWrongValue){
  int value = INT_MAX;
  _lst->initList(value);
  // For checking MAX value causes anything
  EXPECT_PRED2([](int expected, int actual){
		 return expected != actual;
	       }, 0, _lst->getHeadValue());
}

TEST_F(ListTest, InitWithIntMaxPlusOneReturnsINTMAXMinus){
  int value = INT_MAX + 1; // will cause an overflow
  _lst->initList(value);
  EXPECT_PRED2([](int expected, int actual){
		 return expected != actual;
	       },_lst->getHeadValue(), -2147483648);
}

TEST_F(ListTest, InitWithINTOverflowShouldReturnZERO){
  int value = INT_MAX + 1;
  _lst->initList(value);
  EXPECT_EQ(0, _lst->getHeadValue());
}

TEST_F(ListTest, InsertingANodeInFrontOfTheList){
  _lst->initList(2);
  EXPECT_EQ(2, _lst->getHeadValue());
  _lst->insertFront(5);
  EXPECT_EQ(5, _lst->getHeadValue());
  EXPECT_EQ(2, _lst->getTailValue());
}

TEST_F(ListTest, ValueAtIndexZeroShouldBeEqualToTheGetHeadValue){
  _lst->initList(5);
  EXPECT_EQ(_lst->getHeadValue(), _lst->valueAt(0));
}

TEST_F(ListTest, ValueAtIndexShouldBeEqualToTheTailValue){
  _lst->initList(5);
  _lst->append(7);
  EXPECT_EQ(_lst->getTailValue(), _lst->valueAt(1));
}

TEST_F(ListTest, ValueAtShouldBeWorkWithAnySizeOfList){
  _lst->initList(0);
  for(int i = 1; i < 101; ++i){
    _lst->append(i);
  }
  EXPECT_EQ(_lst->getTailValue(), _lst->valueAt(100));
  EXPECT_EQ(_lst->getHeadValue(), _lst->valueAt(0));
  EXPECT_EQ(99, _lst->valueAt(99));
}

TEST_F(ListTest, ShouldPopHeadAndReturnItsValue){
  _lst->initList(5);
  _lst->append(7);
  // ASSERTION
  EXPECT_EQ(5, _lst->popHead());
}

TEST_F(ListTest, SizeShouldBeDecreasedAfterHeadPop){
  _lst->initList(5);
  int popVal = _lst->popHead();
  EXPECT_PRED3([](int expected, int actual, int size){
		return expected == actual && size == 0;
	       }, 5, popVal, _lst->size());
}

TEST_F(ListTest, ShouldReturnToTheTailValueAndPopTail){
  _lst->initList(5);
  _lst->append(7);
  EXPECT_EQ(7, _lst->popTail());
}

TEST_F(ListTest, SizeShouldBeDecreasedAfterTailPop){
  _lst->initList(5);
  _lst->append(7);
  int popVal = _lst->popTail();
  EXPECT_PRED3([](int expected, int actual, int size){
		return expected == actual && size == 1;
	       }, 7, popVal, _lst->size());
}

TEST_F(ListTest, InsertIndexZERO){
  _lst->initList(5);
  _lst->insert(0, 7);
  EXPECT_EQ(7, _lst->getHeadValue());
}

TEST_F(ListTest, SizeShouldBeIncreasedAfterInsertion){
  _lst->initList(3);
  _lst->insert(0, 7);
  EXPECT_PRED3([](int expected, int actual, int size){
		 return expected == actual && size == 2;
	       },7, _lst->getHeadValue(), _lst->size());
}

TEST_F(ListTest, IfKthIndexNotExistsInsertTail){
  _lst->initList(7);
  _lst->append(3);
  _lst->insert(4, 4);
  EXPECT_EQ(4, _lst->getTailValue());
}

TEST_F(ListTest, InsertKthPosition){
  _lst->initList(10);
  for(int i = 1; i < 5; ++i){
    _lst->append(i);
  }
  _lst->insert(3, 12); // [0] -> [1] -> [2]
                      // this inserts into index 3
  EXPECT_EQ(12, _lst->valueAt(3));
}

TEST_F(ListTest, ShouldEraseTheHead){
  _lst->initList(10);
  _lst->append(7);
  _lst->erase(0);
  EXPECT_EQ(7, _lst->getHeadValue());
}

TEST_F(ListTest, ShouldEraseTailIfIndexIsBiggerThanSize){
  _lst->initList(10);
  _lst->append(5);
  _lst->erase(20);
  EXPECT_EQ(10, _lst->getTailValue());
}

TEST_F(ListTest, ShouldEraseFromKthPosition){
  _lst->initList(0);
  for (int i = 1; i < 10; ++i) {
    _lst->append(i);
  }
  _lst->erase(3);
  EXPECT_EQ(4, _lst->valueAt(3));
  EXPECT_EQ(9, _lst->size());
}

TEST_F(ListTest, ShouldReverseTheList){
  _lst->initList(0);
  for (int i = 1; i < 10; ++i) {
    _lst->append(i);
  }
  _lst->reverse();
  EXPECT_EQ(0, _lst->getTailValue());
  EXPECT_EQ(9, _lst->getHeadValue());
}

TEST_F(ListTest, ShouldReturnToHeadValueFromBackIfIndexBiggerThanSize){
  _lst->initList(3);
  _lst->append(7);
  EXPECT_EQ(3, _lst->kthValueFromTail(200));
}

TEST_F(ListTest, ShouldReturnToValueFromBack){
  _lst->initList(0);
  for (int i = 1; i < 10; ++i) {
    _lst->append(i);
  }
  EXPECT_EQ(0, _lst->kthValueFromTail(10));
}

