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

#include <cstring>

#include "Puzzle.h"
#include "PuzzleIterator.h"
#include "PuzzleSolver.h"

PuzzleSolver::PuzzleSolver() {}

/// @brief recursive function to search the given word
bool findWord( PuzzleIterator it, const std::string & word2search, size_t pos )
{
  if ( word2search.length() == pos ) { return true; }
  if ( word2search[pos] == ' ' ) { return findWord( it, word2search, ++pos ); }
  if ( *it == toupper( word2search[pos] ) )
  {
    return findWord( ++it, word2search, ++pos );
  }
  return false;
}

PuzzleIterator PuzzleSolver::findWordInPuzzle( std::shared_ptr<Puzzle> pzl
                                             , const std::string&      word2Search 
                                             )
{
  if ( word2Search.empty() ) { return PuzzleIterator(); }

  // collect all positions in puzzle matched the 1st letter from word
  auto positions = pzl->getPositions( toupper( word2Search[0] ) );
  for ( auto p : positions )
  {
    for ( Direction d = First; d != Last; ++d )
    {
      PuzzleIterator it( pzl, p, d );
      // as first character is already matched, increment iterator
      if ( findWord( ++it, word2Search, 1 ) )
      {
        return PuzzleIterator( pzl, p, d );
      }
    }
  }

  return PuzzleIterator();
}
