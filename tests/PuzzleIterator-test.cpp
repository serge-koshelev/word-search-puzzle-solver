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
#include "PuzzleIterator.h"
#include "PuzzleGenerator.h"

namespace
{
  // The fixture for testing class PuzzleItertorTest.
  class PuzzleItertorTest : public ::testing::Test {
  protected:
    // You can remove any or all of the following functions if their bodies would
    // be empty.

    PuzzleItertorTest()
    {
      // You can do set-up work for each test here.
    }

    ~PuzzleItertorTest() override
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
  };

  TEST( PuzzleItertorTest, initialization ) {
    //arrange
    char expectedPuzzle[3][3] = { {'Q', 'P', 'B'},
                                  {'Q', 'Z', 'R'},
                                  {'D', 'Z', 'R'}
    };
    PuzzleGenerator gen;

    //act
    auto randomPuzzle = gen.generateRandomPuzzle( 0, 3, 3 );
    PuzzleIterator it1( randomPuzzle, Position( {1,1} ), North );
    PuzzleIterator it2 = it1;

    //assert
    EXPECT_EQ( Position( {1,1} ), it1.position() );
    EXPECT_EQ( Position( {1,1} ), (Position)it1 );

    EXPECT_EQ( North, it1.direction() );
    EXPECT_EQ( North, (Direction)it1 );

    EXPECT_EQ( expectedPuzzle[1][1], *it1 );

    EXPECT_EQ( it1, it2 );
  }

  TEST( PuzzleItertorTest, increment )
  {
    //arrange
    char expuzzle[3][3] = {{'I', 'B', 'C'},
                           {'H', 'A', 'D'},
                           {'G', 'F', 'E'}
    };

    //act
    std::shared_ptr<Puzzle> puzzle( new Puzzle( 3, 3 ) );
    for ( int i = 0; i < 3; ++i )
    {
      for ( int j = 0; j < 3; ++j )
      {
        puzzle->set( Position( {i,j} ), expuzzle[i][j] );
      }
    }

    PuzzleIterator it1( puzzle, Position( {1,1} ), North );
    PuzzleIterator it2( puzzle, Position( {1,1} ), NorthEast );
    PuzzleIterator it3( puzzle, Position( {1,1} ), East );
    PuzzleIterator it4( puzzle, Position( {1,1} ), SouthEast );
    PuzzleIterator it5( puzzle, Position( {1,1} ), South );
    PuzzleIterator it6( puzzle, Position( {1,1} ), SouthWest );
    PuzzleIterator it7( puzzle, Position( {1,1} ), West );
    PuzzleIterator it8( puzzle, Position( {1,1} ), NorthWest );

    //assert
    ASSERT_EQ( Position( {1,1} ), (Position)it1 );
    ASSERT_EQ( 'A', *it1 );

    // act
    it1++; it2++; it3++; it4++; it5++; it6++; it7++; it8++;

    //assert
    ASSERT_EQ( Position( {0,1} ), (Position)it1 );
    ASSERT_EQ( Position( {0,2} ), (Position)it2 );
    ASSERT_EQ( Position( {1,2} ), (Position)it3 );
    ASSERT_EQ( Position( {2,2} ), (Position)it4 );
    ASSERT_EQ( Position( {2,1} ), (Position)it5 );
    ASSERT_EQ( Position( {2,0} ), (Position)it6 );
    ASSERT_EQ( Position( {1,0} ), (Position)it7 );
    ASSERT_EQ( Position( {0,0} ), (Position)it8 );

    ASSERT_EQ( 'B', *it1 );
    ASSERT_EQ( 'C', *it2 );
    ASSERT_EQ( 'D', *it3 );
    ASSERT_EQ( 'E', *it4 );
    ASSERT_EQ( 'F', *it5 );
    ASSERT_EQ( 'G', *it6 );
    ASSERT_EQ( 'H', *it7 );
    ASSERT_EQ( 'I', *it8 );

    //act
    it1++; it2++; it3++; it4++; it5++; it6++; it7++; it8++;

    //assert
    ASSERT_EQ( Position( {-1, 1} ), (Position)it1 );
    ASSERT_EQ( Position( {-1, 3} ), (Position)it2 );
    ASSERT_EQ( Position( { 1, 3} ), (Position)it3 );
    ASSERT_EQ( Position( { 3, 3} ), (Position)it4 );
    ASSERT_EQ( Position( { 3, 1} ), (Position)it5 );
    ASSERT_EQ( Position( { 3,-1} ), (Position)it6 );
    ASSERT_EQ( Position( { 1,-1} ), (Position)it7 );
    ASSERT_EQ( Position( {-1,-1} ), (Position)it8 );

    ASSERT_EQ( Puzzle::NotInitializedValue, *it1 );
    ASSERT_EQ( Puzzle::NotInitializedValue, *it2 );
    ASSERT_EQ( Puzzle::NotInitializedValue, *it3 );
    ASSERT_EQ( Puzzle::NotInitializedValue, *it4 );
    ASSERT_EQ( Puzzle::NotInitializedValue, *it5 );
    ASSERT_EQ( Puzzle::NotInitializedValue, *it6 );
    ASSERT_EQ( Puzzle::NotInitializedValue, *it7 );
    ASSERT_EQ( Puzzle::NotInitializedValue, *it8 );
  }

  TEST( PuzzleItertorTest, distance )
  {
    //arrange
    PuzzleGenerator gen;
    auto            puzzle = gen.generateRandomPuzzle( 0, 5, 5 );

    for ( auto d = First; d != Last; ++d )
    {
      //act
      PuzzleIterator itCenter( puzzle, Position( { 2,2 } ), d );
      itCenter++;
      PuzzleIterator it( puzzle, Position( { 2,2 }), itCenter.position() );

      //assert
      ASSERT_TRUE( it.isValid() );
      ASSERT_EQ( it.direction(), d );
    }

    for ( auto d = First; d != Last; ++d )
    {
      //act
      PuzzleIterator itCenter( puzzle, Position( { 2,2 } ), d );
      itCenter++;
      itCenter++;
      PuzzleIterator it( puzzle, Position( { 2,2 } ), itCenter.position() );

      //assert
      ASSERT_FALSE( it.isValid() );
    }
  }
}
