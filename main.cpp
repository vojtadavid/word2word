#include "catch_amalgamated.hpp"
#include "Word2Word.h"


TEST_CASE("simple")
{
  auto path = Word2Word::word2word("words.txt", "cat", "dog");
  REQUIRE(path.size() == 4);
  REQUIRE(path[0] == "cat");
  REQUIRE(path[1] == "cot");
  REQUIRE(path[2] == "cog");
  REQUIRE(path[3] == "dog");
}

TEST_CASE("start equals end")
{

  auto path = Word2Word::word2word("words.txt", "cat", "cat");
  REQUIRE(path.size() == 1);
  REQUIRE(path[0] == "cat");
}

TEST_CASE("sequence does not exists")
{

  auto path = Word2Word::word2word("words.txt", "xylographical", "xenodiagnoses");
  REQUIRE(path.size() == 1);
  REQUIRE(path[0] == "xenodiagnoses");
}

TEST_CASE("sequence does not exists switched")
{
  auto path = Word2Word::word2word("words.txt", "xenodiagnoses", "xylographical");
  REQUIRE(path.size() == 1);
  REQUIRE(path[0] == "xylographical");
}
