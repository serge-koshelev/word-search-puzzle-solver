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
#include <memory>
#include <utility>

#include "../cxxopts/cxxopts.hpp"

#include "PuzzleGenerator.h"
#include "Puzzle.h"
#include "PuzzleIterator.h"
#include "PuzzleSolver.h"

int InteractiveShell()
{
  // Read puzzle from console
  std::cout << "Please enter puzzle, line by line. Empty line means end of puzzle input" << std::endl;
  std::vector<std::string> inputPuzzle;
  size_t colSize = 0;
  while ( true )
  {
    std::string s = "";
    std::getline( std::cin, s );
    if ( s.empty() ) { break; }
    colSize = s.length() > colSize ? s.length() : colSize;
    inputPuzzle.push_back( s );
  }
  
  // convert input to puzzle object
  std::shared_ptr<Puzzle> userPuzzle( new Puzzle( static_cast<int>( inputPuzzle.size() )
                                                , static_cast<int>( colSize ) 
                                                ) );
  for ( int i = 0; i < inputPuzzle.size(); ++i )
  {
    const std::string& s = inputPuzzle[i];
    for ( int j = 0; j < s.length(); ++j )
    {
      userPuzzle->set( Position({i,j}), s[j] );
    }
  }

  // Search in puzzle
  std::cout << "You've entered this puzzle: " << *userPuzzle;
  std::cout << "Type any word and press Enter to search this word in puzzle" << std::endl;
  
  PuzzleSolver puzzleSolver;

  while ( true )
  {
    std::string word;
    std::getline( std::cin, word );
    if ( word.empty() ) { break; }

    auto it = puzzleSolver.findWordInPuzzle( userPuzzle, word );
    if ( it.isValid() ) { std::cout << "YES" << " " << it << std::endl; }
    else                { std::cout << "NO"  << std::endl; }
  }

  return 0;
}

int main( int argc, char** argv )
{
  cxxopts::Options options( "WordPuzzleSolver", "Words puzzle generator. Copyright( C ) 2019. Serge Koshelev" );
  options.add_options()
    ("g,generate", "Generate puzzle [random|wiki]", cxxopts::value<std::string>())
    ("r,rows", "For random puzzle defines the number of rows", cxxopts::value<std::string>())
    ("c,cols", "For random puzzle defines the number of columns", cxxopts::value<std::string>())
    ("p,puzzle", "Read puzzle from file", cxxopts::value<std::string>())
    ("d,dictionary", "Read list of words to search in puzzle from file", cxxopts::value<std::string>())
    ;
  
  auto result = options.parse( argc, argv );
  auto& arguments = result.arguments();

  // if no arguments is given, run interactiv
  if ( arguments.size() == 0 ) { return InteractiveShell(); }

/*
  std::cout << "Random generated word puzzle " << rows << "x" << cols << std::endl;
  PuzzleGenerator generator;
  auto puzzle = generator.generateRandomPuzzle( seed, rows, cols );
  std::cout << *puzzle;

  std::cout << "Word puzzle 10x10 from Wiki page about word search" << std::endl;
  auto wikiPuzzle = generator.generateWikiPuzzle();
  std::cout << *wikiPuzzle;
  */

  return 0;
}
