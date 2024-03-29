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
#include <stdexcept>

#include "Puzzle.h"

Puzzle::Puzzle( int rowsNumber, int columnsNumber )
{
  _rowsNumber    = rowsNumber;
  _columnsNumber = columnsNumber;

  if ( _rowsNumber < 1 || _columnsNumber < 1 ) { throw std::invalid_argument( "Bad puzzle dimensions" ); }

  size_t totalRows    = static_cast<size_t>( _rowsNumber    ) + 2;
  size_t totalColumns = static_cast<size_t>( _columnsNumber ) + 2;

  _puzzle_memory = std::unique_ptr<char[]>( new char  [totalRows * totalColumns] );
  memset( _puzzle_memory.get(), NotInitializedValue, totalRows * totalColumns );

  _puzzle_rows = std::unique_ptr<char* []>( new char* [totalRows] );
  for ( int i = 0; i < _rowsNumber+2; ++i )
  {
    _puzzle_rows[i] = _puzzle_memory.get() + i * totalColumns + 1;
  }
  _puzzle = _puzzle_rows.get() + 1;
};

void Puzzle::set( const Position & p, char value )
{
  value = toupper( value );
  // if cell was initialized before, clean it old value from hash
  if ( get( p ) != NotInitializedValue )
  {
    char oldValue = _puzzle[p.first][p.second];
    auto endPosistion = _hash[oldValue].end();
    for ( auto vp = _hash[oldValue].begin(); vp != endPosistion; vp++ )
    {
      if ( *vp == p ) { _hash[oldValue].erase( vp ); break; }
    }
  }

  _puzzle[p.first][p.second] = value;
  _hash[value].push_back( p );
  return;
}

bool Puzzle::isEqual( const Puzzle& rhs )
{
  if ( _rowsNumber != rhs._rowsNumber || _columnsNumber != rhs._columnsNumber ) { return false; }

  for ( int i = 0; i < _rowsNumber; ++i )
  {
    for ( int j = 0; j < _columnsNumber; ++j )
    {
      if ( (*this)[i][j] != rhs[i][j] ) { return false; }
    }
  }
}

std::ostream& operator << ( std::ostream& os, const Puzzle& pz )
{
  for ( int i = 0; i < pz.rows(); ++i )
  {
    for ( int j = 0; j < pz.columns(); ++j )
    {
      os << pz[i][j] << " ";
    }
    os << std::endl;
  }

  return os;
}
