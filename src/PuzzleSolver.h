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
#include <utility>

class Puzzle;
class PuzzleIterator;
class WordList;

enum class SearchAlgorithm
{
  BruteForce,
  DoubleHash
};

/// @class PuzzleSolver
/// @brief Solves puzzle or do some operations needed for solve
class PuzzleSolver
{
public:
  /// @brief Default constructor
  PuzzleSolver( SearchAlgorithm algo = SearchAlgorithm::BruteForce );

  /// @brief search one word in puzlle using brute force algorithm.
  /// @return On success valid iterator which contains the starting point, invalid iterator otherwise 
  PuzzleIterator findWordInPuzzleBruteForce( std::shared_ptr<Puzzle>, const std::string & word2Search );

  
  /// @brief search one word in puzlle using 2 first letters from word to find direction
  /// @return On success valid iterator which contains the starting point, invalid iterator otherwise 
  PuzzleIterator findWordInPuzzleDoubleHash( std::shared_ptr<Puzzle>, const std::string& word2Search );

  /// @brief search list of words in puzzle
  /// @return list of found words and their locations
  std::vector<std::pair<std::string, PuzzleIterator>> PuzzleSolver::solvePuzzle( std::shared_ptr<Puzzle> puzzle, const WordList& words2search );

private:
  SearchAlgorithm _searchAlgo;
};

#endif