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

#ifndef PUZZLE_ITERATOR_H
#define PUZZLE_ITERATOR_H

#include <iostream>
#include <memory>
#include <stdexcept>

#include "Puzzle.h"

/// @brief Defines directions in 2D puzzle:
///     NW  N  NE 
///      \  ^  /
///       \ | /
///  W <--- 0 ---> E
///       / | \
///      /  V  \
///     SW  S  SE
typedef enum {
  First     = 0,
  North     = 0,
  NorthEast = 1,
  East      = 2,
  SouthEast = 3,
  South     = 4,
  SouthWest = 5,
  West      = 6,
  NorthWest = 7,
  Last      = 7,
  Undefined = 8
} Direction;

// to use Direction enum in loops. overload increment operator like this:
inline Direction& operator++( Direction& dirId )
{
  return dirId = static_cast<Direction>(static_cast<int>(dirId)+1);
}

/// @class PuzzleIterator
/// @brief Allows to exctract sequence of characters
/// from puzzle in choosen direction and position
class PuzzleIterator
{
  public:
    PuzzleIterator() :
      _bindedPuzzle( std::shared_ptr<Puzzle>( nullptr ) ),
      _position( Position({-1,-1}) ),
      _direction( Undefined ),
      _di( 0 ),
      _dj( 0 ) {}

    /// @brief Constructor initialize iterator for the given pozition and direction
    /// @param puzzle2Navigate puzzle binded with iterator
    /// @param startPoint iterator start position
    /// @param where2Go direction for iteration
    PuzzleIterator( std::shared_ptr<Puzzle> puzzel2Navigate, Position startPoint, Direction where2Go ) :
      _bindedPuzzle( puzzel2Navigate ),
      _position( startPoint ),
      _direction( where2Go )
    {
      if ( _position.first  <  0
        || _position.second <  0
        || _position.first  >= _bindedPuzzle->rows()
        || _position.second >= _bindedPuzzle->columns()
        )
      { throw std::invalid_argument( "Puzzle iterator initialization error: position outside puzzle" ); }
      
      initIncrementValues();
    }

    /// @brief Constructor initializes iterator from 2 positions
    /// if distance between positions more than 1, creates invalid iterator
    /// @param puzzle2Navigate puzzle binded with iterator
    /// @param startPoint iterator start position
    /// @param nextPoint position which points direction
    PuzzleIterator( std::shared_ptr<Puzzle> puzzel2Navigate, Position startPoint, Position nextPoint ) :
      _bindedPuzzle( puzzel2Navigate ),
      _position( startPoint ),
      _direction( Undefined ),
      _di( nextPoint.first - startPoint.first ),
      _dj( nextPoint.second - startPoint.second )
    {
      int distance = _di * _di + _dj * _dj;
      if ( distance > 2 ) // points are further than one increment step from each others. Invalid iterator
      {
        _bindedPuzzle.reset();
        _position = Position( { -1,-1 } );
        _di = 0;
        _dj = 0;
        return;
      }
      // deduce direction
      initDirectionFromIncrementValues();
    }

    bool isValid() { return _bindedPuzzle.get() != nullptr; }

    /// @brief Copy constructor
    PuzzleIterator( const PuzzleIterator& rhs ) :
      _bindedPuzzle( rhs._bindedPuzzle ),
      _position(     rhs._position ),
      _direction(    rhs._direction ),
      _di(           rhs._di ),
      _dj(           rhs._dj ) {}

    /// @brief Destructor
    ~PuzzleIterator() { ; }

    /// Get iterator direction
    Direction direction() const { return _direction; }

    /// @brief Cast to direction
    operator Direction() const { return _direction; }

    std::string directionName() const { 
      switch ( _direction )
      {
        case North     : return "North";
        case NorthEast : return "NorthEast";
        case East      : return "East";
        case SouthEast : return "SouthEast";
        case South     : return "South";
        case SouthWest : return "SouthWest";
        case West      : return "West";
        case NorthWest : return "NorthWest";
        case Undefined : 
        default        : return "Undefined";
      }
    }
    /// Get iterator position
    Position position() const { return _position; }

    /// @brief Cast to position
    operator Position() const { return _position; }
    
    /// @brief post increment iterator
    /// No out of boundary tests as search algorithm 
    /// will stop by boundary value in puzzle
    PuzzleIterator operator++() {
      _position.first += _di;
      _position.second += _dj;
      return *this;
    }

    /// @brief pre increment iterator
    /// No out of boundary tests as search algorithm 
    /// will stop by boundary value in puzzle
    PuzzleIterator operator++(int junk) {
      PuzzleIterator it = *this;
      _position.first += _di;
      _position.second += _dj;
      return it;
    }

    /// @brief Value operator
    char operator *() const { return _bindedPuzzle->get( _position ); }

    /// @brief Equal operator
    bool operator == ( const PuzzleIterator& rhs ) { return _position == rhs._position; }
    /// @brief Non equal operator
    bool operator != ( const PuzzleIterator& rhs ) { return _position != rhs._position; }

    friend std::ostream& operator << ( std::ostream& os, const PuzzleIterator& pzIt );
  
  protected:
    Direction               _direction;    /// iterator movement direction in 2D
    std::shared_ptr<Puzzle> _bindedPuzzle; /// Puzzle for this iterator
    Position                _position;     /// current iterator pozition
    int                     _di;           /// increment value in row direction
    int                     _dj;           /// increment value in column

    void initIncrementValues()
    {
      switch ( _direction )
      {
        case North     : _di = -1; _dj =  0; break;
        case NorthEast : _di = -1; _dj =  1; break;
        case East      : _di =  0; _dj =  1; break;
        case SouthEast : _di =  1; _dj =  1; break;
        case South     : _di =  1; _dj =  0; break;
        case SouthWest : _di =  1; _dj = -1; break;
        case West      : _di =  0; _dj = -1; break;
        case NorthWest : _di = -1; _dj = -1; break;
        case Undefined :
        default        : _di =  0; _dj =  0; break;
      }
    }

    void initDirectionFromIncrementValues()
    {
      switch ( _di )
      {
      case -1:
        switch ( _dj )
        {
          case -1: _direction = NorthWest; break;
          case  0: _direction = North;     break;
          case  1: _direction = NorthEast; break;
        }
        break;
      case 0:
        switch ( _dj )
        {
          case -1: _direction = West; break;
          case  1: _direction = East; break;
        }
        break;
      case 1:
        switch ( _dj )
        {
          case -1: _direction = SouthWest; break;
          case  0: _direction = South;     break;
          case  1: _direction = SouthEast; break;
        }
        break;
      }
    }
};

inline std::ostream& operator << ( std::ostream& os, const PuzzleIterator& pzIt )
{
  os << "[" << pzIt._position.first + 1 << "," << pzIt._position.second + 1 << "] ";
  os << pzIt.directionName() << std::endl;
  return os;
}

#endif
