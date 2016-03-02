/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2016. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "SequenceNumber.h"

#include "gtest/gtest.h"

namespace nt {
  
class SequenceNumberTest : public ::testing::Test {};

TEST_F(SequenceNumberTest, ConstructEmpty) {
  SequenceNumber s;
  ASSERT_TRUE(s.value() == 0u);
}

TEST_F(SequenceNumberTest, ConstructSetValue) {
  unsigned int v = 58u;
  SequenceNumber s(v);
  ASSERT_TRUE(s.value() == v);
}

TEST_F(SequenceNumberTest, ConstructCopy) {
  unsigned int v = 58u;
  SequenceNumber s(v);
  ASSERT_TRUE(s.value() == v);
  SequenceNumber s2(s);
  ASSERT_TRUE(s2.value() == v)
}

TEST_F(SequenceNumberTest, OperatorPlusPlusNonOverflow) {
  unsigned int v = 58u;
  SequenceNumber s(v);
  ASSERT_TRUE(s.value() == v);
  s++;
  ASSERT_TRUE(s.value() == v + 1);
}

TEST_F(SequenceNumberTest, OperatorPlusPlusOverflow) {
  unsigned int v = 0xffffu;
  SequenceNumber s(v);
  ASSERT_TRUE(s.value() == v);
  s++;
  ASSERT_TRUE(s.value() == 0);
}

TEST_F(SequenceNumberTest, OperatorEquals) {
  unsigned int v = 58u;
  SequenceNumber s(v);
  SequenceNumber s2(v);
  ASSERT_TRUE(s == s2);
}

TEST_F(SequenceNumberTest, OperatorNotEquals) {
  unsigned int v = 58u;
  SequenceNumber s(v);
  SequenceNumber s2(v+1);
  ASSERT_TRUE(s != s2);
}

TEST_F(SequenceNumberTest, OperatorLessThenOrEqualTo) {
  unsigned int v = 58u;
  SequenceNumber s(v);
  SequenceNumber s2(v+1);
  ASSERT_TRUE(s <= s2); // 58 <= 59
  s++;
  ASSERT_TRUE(s <= s2); // 59 <= 59
  s++;
  ASSERT_FALSE(s <= s2); // 60 <= 59 is false
}

TEST_F(SequenceNumberTest, OperatorGreaterThenOrEqualTo) {
  unsigned int v = 58u;
  SequenceNumber s(v);
  SequenceNumber s2(v+1);
  ASSERT_TRUE(s2 >= s); // 59 >= 58
  s++;
  ASSERT_TRUE(s2 >= s); // 59 >= 59
  s++;
  ASSERT_FALSE(s2 >= s); // 59 >= 60 is false
}

TEST_F(SequenceNumberTest, OperatorLessThen) {
  unsigned int v = 58u;
  SequenceNumber s(v);
  SequenceNumber s2(v+1);
  ASSERT_TRUE(s < s2); // 58 < 59
  s++;
  ASSERT_FALSE(s < s2); // 59 < 59 is false
  s++;
  ASSERT_FALSE(s <= s2); // 60 < 59 is false
}

TEST_F(SequenceNumberTest, OperatorGreaterThen) {
  unsigned int v = 58u;
  SequenceNumber s(v);
  SequenceNumber s2(v+1);
  ASSERT_TRUE(s2 > s); // 59 > 58
  s++;
  ASSERT_FALSE(s2 > s); // 59 > 59 is false
  s++;
  ASSERT_FALSE(s2 > s); // 59 > 60 is false
}

}  // namespace nt