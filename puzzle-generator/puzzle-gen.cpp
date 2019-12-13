//    Copyright( C ) 2019, Serge Koshelev.All rights reserved.
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

#include <iostream>
#include "PuzzleGenerator.h"

void Usage( const char * programName )
{
  std::cout << "Words puzzle generator. Copyright( C ) 2019. Usage:" << std::endl;
  std::cout << "  " << programName << " [<rows> [<cols> [<seed>]]]" << std::endl;
}

int main( int argc, char** argv )
{
  int rows = 10;
  int cols = 10;
  int seed = 0;

  try {
    if (argc > 1) { rows = std::atoi( argv[1] ); }
    if (argc > 2) { cols = std::atoi( argv[2] ); }
    if (argc > 3) { seed = std::atoi( argv[3] ); }
  }
  catch (...)
  {
    std::cout << "Ivalid arguments" << std::endl;
    Usage( argv[0] );

    return -1;
  }

  PuzzleGenerator generator( rows, cols );
  auto puzzle = generator.GeneratePuzzle( seed );
  for( auto ln : *puzzle )
  {
    std::cout << ln << std::endl;
  }

  return 0;
}