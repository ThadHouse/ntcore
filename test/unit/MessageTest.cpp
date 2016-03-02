/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2015. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Message.h"

#include "gtest/gtest.h"

namespace nt {

class MessageTest : public ::testing::Test {}

TEST_F(MessageTest, ConstructParameterless) {
  Message msg;
  ASSERT_TRUE(msg.type() == kUnknown);
  ASSERT_TRUE(msg.id() == 0u);
  ASSERT_TRUE(msg.str() == kUnknown);
  ASSERT_TRUE(msg.flags() == 0u);
  ASSERT_TRUE(msg.seq_num_uid() == 0u);
  ASSERT_TRUE(msg.val() == nullptr);
}

}  // namespace nt