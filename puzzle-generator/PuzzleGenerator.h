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

#include <string>
#include <vector>

/// @class PuzzleGenerator
/// @brief Randomly generates M rows by N columns word puzzle
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

  /// @brief Constructor of puzzle generator
  /// @param rows word puzzle rows number
  /// @param columns word puzzle columns number
  PuzzleGenerator( int rows, int columns );

  std::vector<std::string> * GeneratePuzzle( int seed );

private:
  int  _rowsNumber;
  int  _columnsNumber;

  static std::string  LettersPool; /// keep all possible letters to be used in puzzle
};

#endif