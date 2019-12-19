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

#ifndef PUZZLE_GENERATOR_HH
#define PUZZLE_GENERATOR_HH

#include <memory>
#include <ostream>
#include <string>
#include <vector>

class Puzzle;

/// @class PuzzleGenerator
/// @brief Generates M rows by N columns word puzzle
/// using various algorithms
/// Something like this:
///   JLIBPNZQOAJD
///   KBFAMZSBEARQ
///   OAKTMICECTQG
///   ....
class PuzzleGenerator
{
public:
  /// @brief Default constructor
  PuzzleGenerator();

  /// @brief Generate random filled puzzle with given dimensions and random seed
  /// @param seed random seed for random generator
  /// @param rows word puzzle rows number
  /// @param columns word puzzle columns numbe
  std::shared_ptr<Puzzle> generateRandomPuzzle( int seed = 0, int rows = 10, int columns = 10 );

  /// @brief Generates puzzle which mentioned on Wiki page
  /// https://en.wikipedia.org/wiki/Word_search
  /// it is used for tests and benchmarks
  std::shared_ptr<Puzzle> generateWikiPuzzle();

  /// @brief Read puzzle from file 
  std::shared_ptr<Puzzle> loadPuzzleFromFile( const std::string & puzzleFileName );

private:
  static std::string  LettersPool; /// keep all possible letters to be used in puzzle
};

#endif