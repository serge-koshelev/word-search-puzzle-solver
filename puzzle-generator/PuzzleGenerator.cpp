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

std::string PuzzleGenerator::LettersPool = "ABCDEFGHIGKLMNOPQRSTUVWXYZ";


PuzzleGenerator::PuzzleGenerator()
{
  _rowsNumber    = 10;
  _columnsNumber = 10;
}

PuzzleGenerator::PuzzleGenerator( int rows, int columns )
{
  _rowsNumber    = rows;
  _columnsNumber = columns;

  if ( rows < 0 || columns < 0 ) { throw std::invalid_argument( "Dimensions of puzzle must be positive" ); }
}

std::vector< std::string> * PuzzleGenerator::GeneratePuzzle( int seed )
{
  std::default_random_engine generator( seed );
  std::uniform_int_distribution<int> distribution( 0, (int)LettersPool.length()-1 );
  std::vector< std::string>* puzzle = new std::vector<std::string>( _rowsNumber );

  for ( int i = 0; i < _rowsNumber; ++i )
  {
    for ( int j = 0; j < _columnsNumber; ++j )
    {
      auto randomNumber = distribution( generator );
      (*puzzle)[i].append( 1, LettersPool[randomNumber] );
    }
  }
  return puzzle;
}

