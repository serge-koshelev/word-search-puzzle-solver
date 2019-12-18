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
#include "PuzzleSolver.h"
#include "PuzzleGenerator.h"

namespace
{
  // The fixture for testing class PuzzleSolverTest.
  class PuzzleSolverTest : public ::testing::Test {
  protected:
    // You can remove any or all of the following functions if their bodies would
    // be empty.

    PuzzleSolverTest()
    {
      // You can do set-up work for each test here.
    }

    ~PuzzleSolverTest() override
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

  TEST( PuzzleSolverTest, searchOneWord ) {
    //arrange
    PuzzleGenerator gen;

    std::vector<std::string> wordList = {
      "Find", "Random", "Sleuth", "Backward", "Vertical", 
      "Diagonal", "Wikipedia", "Horizontal", "Word Search"
    };

    //act
    auto wikiPuzzle = gen.generateWikiPuzzle();
    PuzzleSolver solver;
    PuzzleIterator it( wikiPuzzle, Position( {0,0}), SouthEast );
    
    //assert
    for ( auto s : wordList )
    {
      EXPECT_TRUE( solver.findWordInPuzzle( wikiPuzzle, s, it ) );
      //std::cout << s << ": -> " << it << std::endl;
    }
  }
}
