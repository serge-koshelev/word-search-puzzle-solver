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

#include <iostream>
#include <random>
#include <stdexcept>

#include "PuzzleGenerator.h"
#include "Puzzle.h"

std::string PuzzleGenerator::LettersPool = "ABCDEFGHIGKLMNOPQRSTUVWXYZ";


PuzzleGenerator::PuzzleGenerator() {}

std::shared_ptr<Puzzle> PuzzleGenerator::generateRandomPuzzle( int seed, int rows, int columns )
{
  std::default_random_engine                 generator( seed );
  std::uniform_int_distribution<int>         distribution( 0, (int)LettersPool.length() - 1 );
  std::shared_ptr<Puzzle> puzzle( new Puzzle( rows, columns ) );

  for ( int i = 0; i < rows; ++i )
  {
    for ( int j = 0; j < columns; ++j )
    {
      auto randomNumber = distribution( generator );
      puzzle->set( Position({i, j}), LettersPool[randomNumber] );
    }
  }
  return puzzle;
}

std::shared_ptr<Puzzle> PuzzleGenerator::generateWikiPuzzle()
{
  char pzl[10][10] = {{ 'W', 'V', 'E', 'R', 'T', 'I', 'C', 'A', 'L', 'L' },
                      { 'R', 'O', 'O', 'A', 'F', 'F', 'L', 'S', 'A', 'B' },
                      { 'A', 'C', 'R', 'I', 'L', 'I', 'A', 'T', 'O', 'A' },
                      { 'N', 'D', 'O', 'D', 'K', 'O', 'N', 'W', 'D', 'C' },
                      { 'D', 'R', 'K', 'E', 'S', 'O', 'O', 'D', 'D', 'K' },
                      { 'O', 'E', 'E', 'P', 'Z', 'E', 'G', 'L', 'I', 'W' },
                      { 'M', 'S', 'I', 'I', 'H', 'O', 'A', 'E', 'R', 'A' },
                      { 'A', 'L', 'R', 'K', 'R', 'R', 'I', 'R', 'E', 'R' },
                      { 'K', 'O', 'D', 'I', 'D', 'E', 'D', 'R', 'C', 'D' },
                      { 'H', 'E', 'L', 'W', 'S', 'L', 'E', 'U', 'T', 'H' }};

  std::shared_ptr<Puzzle> puzzle( new Puzzle( 10, 10 ) );
  for ( int i = 0; i < 10; ++i )
  {
    for ( int j = 0; j < 10; ++j )
    {
      puzzle->set( Position( {i,j} ), pzl[i][j] );
    }
  }
  return puzzle;
}
