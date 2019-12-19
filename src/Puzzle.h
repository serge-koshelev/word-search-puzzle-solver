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


typedef std::pair<int, int> Position;

/// @class Puzzle
/// @brief Container to puzzle implemented
/// as 2D array of characters
class Puzzle
{
  public:
    const static int NotInitializedValue = -1;

    /// @brief Constructor defines word puzzle dimensions
    Puzzle( int rowsNumber = 5, int columnsNumber = 5 );

    /// @brief Destructor
    ~Puzzle() { ; }

    /// @brief Get puzzle dimension in rows
    int rows()    const { return _rowsNumber; }

    /// @brief Get puzzle dimension in columns
    int columns() const { return _columnsNumber; }

    /// @brief Operator for direct access to puzzle cell
    /// Allows also to change puzzle cell, but without caching it
    char* operator [] ( int i ) const { return _puzzle[i]; }

    /// @brief Equal operator
    bool operator == ( const Puzzle& rhs ) { return isEqual( rhs ); }

    /// @brief Non equal operator
    bool operator != ( const Puzzle& rhs ) { return !isEqual( rhs ); }

    /// @brief Get word puzzle cell element for the given pozition
    char get( const Position& p ) const { return _puzzle[p.first][p.second]; }
    /// @brief Set word puzzle cell element for the given pozition
    /// Also adds cell value to cache
    void set( const Position & p, char value );

    /// @brief Get cachec pozitions for the given value
    const std::vector<Position>& getPositions( char value ) { return _hash[toupper(value)]; }

  protected:
    int                                    _rowsNumber;
    int                                    _columnsNumber;
    std::map <char, std::vector<Position>> _hash;

    // compare puzzle for equality element by element
    bool isEqual( const Puzzle& rhs );

  private:
    // Memory allocated for puzzle distributed in the following way
    //
    // row pointers :    [ r1 r2 r3 ... rn ]
    //                     |   \  \       \
    //                     |    \  ------  ----------------------
    //                     |     \       \                       \
    //                     V      V       V                       V
    // all memory block: [ x x x x x x x x x x x x x x x x x x x x x x x x ]
    //  
    //  puzzle has false rows and columns which could be addressed with -1 or columnsNumber/rowsNumber
    //  to help search algorithm to stop on puzzle boundaries as values at those boundaries are _notInitializedValue
    //  puzzle looks like this:
    //   boundary columns
    //   \               --\
    //    |                 \
    //   -1 -1 -1 ... -1 -1 -1 <- boundary row
    //   -1  x  x ...  x  x -1
    //   -1  x  x ...  x  x -1 
    //   .....................
    //   -1  x  x ...  x  x -1
    //   -1  x  x ...  x  x -1
    //   -1 -1 -1 ... -1 -1 -1 <- boundary row
    //

    std::unique_ptr<char[]>  _puzzle_memory; // to keep all puzzle allocated memory
    std::unique_ptr<char*[]> _puzzle_rows;   // to keep array of pointers to rows
    char **                  _puzzle;        // to navigate inside puzzle taking in account outside boundaries
};

std::ostream& operator << ( std::ostream& os, const Puzzle& pz );

#endif
