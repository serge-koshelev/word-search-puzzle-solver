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

#include "WordList.h"

#include <fstream>
#include <iostream>

int WordList::loadFromFile( const std::string& fileName )
{
  _wordList.clear();  
  std::ifstream  infile( fileName );
  std::string    line;
  // read puzzle from file into temporary array of lines 
  while ( std::getline( infile, line ) )
  {
    if ( !line.empty() )
    {
      _wordList.push_back( line );
    }
  }
  return static_cast<int>( _wordList.size() );
}
