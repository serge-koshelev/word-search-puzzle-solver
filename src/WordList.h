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

#ifndef WORD_LIST_HH
#define WORD_LIST_HH

#include <string>
#include <vector>

class Puzzle;

/// @class WordList
/// @brief Container class to keep list of words to be searched in puzzle
class WordList
{
public:
  /// @brief Default constructor
  WordList() { ; }

  /// @brief Destructor
  ~WordList() { ; }

  /// @brief Get number of words in the list
  int size() const { return static_cast<int>( _wordList.size() ); }

  /// @brief Get word for the given position
  const std::string& operator[]( int pos ) const { return _wordList[pos]; }

  /// @brief Read puzzle from file
  /// @param fileName name of the file with words
  /// @return number of words read from file
  int loadFromFile( const std::string & fileName );

private:
  std::vector<std::string> _wordList; /// keep all possible letters to be used in puzzle
};

#endif