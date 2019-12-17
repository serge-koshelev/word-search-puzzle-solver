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
#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include <cctype>


typedef std::pair<size_t, size_t> Position;

/// @class Puzzle
/// @brief Container to puzzle implemented
/// as 2D array of characters
class Puzzle
{
  public:
    /// @brief Constructor defines word puzzle dimensions
    Puzzle( size_t rowsNumber = 5, size_t columnsNumber = 5 );

    /// @brief Destructor
    ~Puzzle() { ; }

    /// @brief Get puzzle dimension in rows
    size_t rows()    const { return _rowsNumber; }

    /// @brief Get puzzle dimension in columns
    size_t columns() const { return _columnsNumber; }

    /// @brief Operator for direct access to puzzle cell
    /// Allows also to change puzzle cell, but without caching it
    char* operator [] ( size_t i ) const { return _puzzle[i]; }

    /// @brief Get word puzzle cell element for the given pozition
    char get( const Position& p ) const { return _puzzle[p.first][p.second]; }
    /// @brief Set word puzzle cell element for the given pozition
    /// Also adds cell value to cache
    void set( const Position & p, char value );

    /// @brief Get cachec pozitions for the given value
    const std::vector<Position>& getPositions( char value ) { return _hash[toupper(value)]; }

  protected:
    size_t                                 _rowsNumber;
    size_t                                 _columnsNumber;
    std::map <char, std::vector<Position>> _hash;

  private:
    std::unique_ptr<char[]>  _puzzle_memory;
    std::unique_ptr<char*[]> _puzzle;

    const static int _notInitializedValue = -1;
};

std::ostream& operator << ( std::ostream& os, const Puzzle& pz );

#endif
