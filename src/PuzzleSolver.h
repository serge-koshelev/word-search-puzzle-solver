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

#ifndef PUZZLE_SOLVER_HH
#define PUZZLE_SOLVER_HH

#include <memory>
#include <string>

class Puzzle;
class PuzzleIterator;

/// @class PuzzleSolver
/// @brief Solves puzzle or do some operations needed for solve
class PuzzleSolver
{
public:
  /// @brief Default constructor
  PuzzleSolver();

  /// @brief search one word in puzlle. On success where will contain starting point iterator
  bool findWordInPuzzle( std::shared_ptr<Puzzle>, const std::string & word2Search, PuzzleIterator & where );

private:
};

#endif