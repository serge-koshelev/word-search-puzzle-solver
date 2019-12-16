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

#ifndef PUZZLE_H
#define PUZZLE_H

#include <exception>
#include <map>
#include <memory>
#include <utility>
#include <vector>

typedef std::pair<size_t, size_t> Position;

/// @class Puzzle
/// @brief Container to puzzle implemented 
/// as 2D array of characters
class Puzzle
{
  public:
    Puzzle( size_t rowsNumber = 5, size_t columnsNumber = 5 );
    ~Puzzle() { ; }

    char* operator [] ( size_t i ) const { return _puzzle[i]; }
    
    char get( const Position& p ) const { return _puzzle[p.first][p.second]; }
    void set( const Position & p, char value );
     
    const std::vector<Position>& getPositions( char value ) { return _hash[value]; }

  protected:
    size_t                                 _rowsNumber;
    size_t                                 _columnsNumber;
    std::map <char, std::vector<Position>> _hash;

  private:
    std::unique_ptr<char[]>  _puzzle_memory;
    std::unique_ptr<char*[]> _puzzle;

    const static int _notInitializedValue = -1;
};

#endif
