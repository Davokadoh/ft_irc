#include <gtest/gtest.h>
#include "Msg.hpp"
#include "parser.hpp"

TEST(ParserTest, ParsesBasicMessage)
{
  std::string raw = "CMD param1 param2";
  IrcMsg msg = parse(raw);
  EXPECT_EQ(msg.command, "CMD");
  EXPECT_EQ(msg.params.size(), 2);
  EXPECT_EQ(msg.params[0], "param1");
  EXPECT_EQ(msg.params[1], "param2");
}

TEST(ParserTest, ParsesMessageWithPrefix)
{
  std::string raw = ":nick!username@host CMD param1 param2";
  IrcMsg msg = parse(raw);
  EXPECT_EQ(msg.prefix, ":nick!username@host");
  EXPECT_EQ(msg.command, "CMD");
  EXPECT_EQ(msg.params.size(), 2);
  EXPECT_EQ(msg.params[0], "param1");
  EXPECT_EQ(msg.params[1], "param2");
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

/*
 * test(":test!~test@test.com PRIVMSG #channel :Hi!");
 * test(":Scionwest!Scionwest@555.55.55.555 PRIVMSG #mychannel :Hello everyone!");
 * test("NICK John");
 */
