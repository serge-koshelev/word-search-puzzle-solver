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

namespace
{
  // The fixture for testing class Foo.
  class PuzzleTest : public ::testing::Test {
  protected:
    // You can remove any or all of the following functions if their bodies would
    // be empty.

    PuzzleTest()
    {
      // You can do set-up work for each test here.
    }

    ~PuzzleTest() override
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

  TEST( PuzzleTest, initialization ) {
    //arrange
    Puzzle puz( 5, 5 );
    //act
    //assert
    for (int i = 0; i < 5; ++i)
    {
      for (size_t j = 0; j < 5; ++j)
      {
        EXPECT_EQ( puz[i][j], -1 );
      }
    }
  }

  TEST( PuzzleTest, hashing ) {
    //arrange
    Puzzle puz( 5, 5 );
    //act
    puz.set( Position({0, 0}), 'A' );
    puz.set( Position({1, 1}), 'B' );
    puz.set( Position({2, 2}), 'C' );
    puz.set( Position({3, 3}), 'D' );
    puz.set( Position({4, 4}), 'E' );

    puz.set( Position({1, 0}), 'B' );
    puz.set( Position({0, 1}), 'B' );
    puz.set( Position({2, 0}), 'C' );
    puz.set( Position({2, 1}), 'C' );
    puz.set( Position({0, 2}), 'C' );
    puz.set( Position({1, 2}), 'C' );
    puz.set( Position({2, 3}), 'D' );
    puz.set( Position({3, 2}), 'D' );

    puz.set( Position({2, 1}), 'F' );

    //assert
    auto positionsList = puz.getPositions( 'A' );
    EXPECT_EQ( positionsList.size(), 1 );
    EXPECT_EQ( positionsList[0], Position({0, 0}) );

    positionsList = puz.getPositions( 'B' );
    EXPECT_EQ( positionsList.size(), 3 );
    EXPECT_EQ( positionsList[0], Position( {1, 1} ) );
    EXPECT_EQ( positionsList[1], Position( {1, 0} ) );
    EXPECT_EQ( positionsList[2], Position( {0, 1} ) );

    positionsList = puz.getPositions( 'C' );
    EXPECT_EQ( positionsList.size(), 4 );
    EXPECT_EQ( positionsList[0], Position( {2, 2} ) );
    EXPECT_EQ( positionsList[1], Position( {2, 0} ) );
    EXPECT_EQ( positionsList[2], Position( {0, 2} ) );
    EXPECT_EQ( positionsList[3], Position( {1, 2} ) );

    positionsList = puz.getPositions( 'D' );
    EXPECT_EQ( positionsList.size(), 3 );
    EXPECT_EQ( positionsList[0], Position( {3, 3} ) );
    EXPECT_EQ( positionsList[1], Position( {2, 3} ) );
    EXPECT_EQ( positionsList[2], Position( {3, 2} ) );

    positionsList = puz.getPositions( 'E' );
    EXPECT_EQ( positionsList.size(), 1 );
    EXPECT_EQ( positionsList[0], Position( {4, 4} ) );

    positionsList = puz.getPositions( 'F' );
    EXPECT_EQ( positionsList.size(), 1 );
    EXPECT_EQ( positionsList[0], Position( {2, 1} ) );
  }
}
