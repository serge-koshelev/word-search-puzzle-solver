//    Copyright(C) 2019, Serge Koshelev. All rights reserved.
//    mailto: serge.koshelev@gmail.com
//
//    This file is part of word-search-puzzle-solver.
//
//    It is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    word-search-puzzle-solver is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with Foobar.  If not, see <https://www.gnu.org/licenses/>.

#include "gtest/gtest.h"
#include "Puzzle.h"
#include "PuzzleGenerator.h"

namespace
{
  // The fixture for testing class Foo.
  class PuzzleGeneratorTest : public ::testing::Test {
  protected:
    // You can remove any or all of the following functions if their bodies would
    // be empty.

    PuzzleGeneratorTest()
    {
      // You can do set-up work for each test here.
    }

    ~PuzzleGeneratorTest() override
    {
      // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    void SetUp() override
    {
      // Code here will be called immediately after the constructor (right
      // before each test).
    }

    void TearDown() override
    {
      // Code here will be called immediately after each test (right
      // before the destructor).
    }

    // Class members declared here can be used by all tests in the test suite
    // for Foo.
  };

  TEST( PuzzleGeneratorTest, initialization ) {
    //arrange
    char expectedPuzzle[3][3] = { {'Q', 'P', 'B'},
                                  {'Q', 'Z', 'R'},
                                  {'D', 'Z', 'R'}
    };
    PuzzleGenerator gen( 3, 3 );

    //act
    auto randomPuzzle = gen.GenerateRandomPuzzle( 0 );

    //assert
    for (int i = 0; i < randomPuzzle->rows(); ++i)
    {
      for (size_t j = 0; j < randomPuzzle->columns(); ++j)
      {
        EXPECT_EQ( expectedPuzzle[i][j], randomPuzzle->get( Position( { i,j } ) ) );
      }
    }
  }

  TEST( PuzzleGeneratorTest, hashing )
  {
    //arrange
    PuzzleGenerator gen( 3, 3 );

    //act
    auto randomPuzzle = gen.GenerateRandomPuzzle( 0 );

    //assert
    ASSERT_EQ( 0, randomPuzzle->getPositions( 'A' ).size() );
    ASSERT_EQ( 1, randomPuzzle->getPositions( 'B' ).size() );
    ASSERT_EQ( 1, randomPuzzle->getPositions( 'D' ).size() );
    ASSERT_EQ( 1, randomPuzzle->getPositions( 'P' ).size() );
    ASSERT_EQ( 2, randomPuzzle->getPositions( 'R' ).size() );
    ASSERT_EQ( 2, randomPuzzle->getPositions( 'Q' ).size() );
    ASSERT_EQ( 2, randomPuzzle->getPositions( 'Z' ).size() );
  }
}