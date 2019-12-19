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
#include <stdexcept>
#include <utility>
#include <cctype>
#include "Timer.h"

#include "../cxxopts/cxxopts.hpp"

#include "PuzzleGenerator.h"
#include "Puzzle.h"
#include "PuzzleIterator.h"
#include "PuzzleSolver.h"
#include "WordList.h"

int InteractiveShell( std::shared_ptr<Puzzle> & userPuzzle )
{
  if ( !userPuzzle )
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
    userPuzzle.reset( new Puzzle( static_cast<int>(inputPuzzle.size()), static_cast<int>(colSize) ) );
    for ( int i = 0; i < inputPuzzle.size(); ++i )
    {
      const std::string& s = inputPuzzle[i];
      for ( int j = 0, colpos = 0; j < s.length(); ++j )
      {
        if ( std::isblank( s[j] ) ) { continue; }
        userPuzzle->set( Position( { i,colpos++ } ), s[j] );
      }
    }
  }

  // Search in puzzle
  std::cout << "You've entered this puzzle: " << std::endl << *userPuzzle << std::endl;
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
  try
  {
    cxxopts::Options options( "WordPuzzleSolver", "Words puzzle generator. Copyright( C ) 2019. Serge Koshelev" );
    options.add_options()
      ("g,generate",   "Generate puzzle [random|wiki]",                    cxxopts::value<std::string>())
      ("r,rows",       "For random puzzle defines the number of rows",     cxxopts::value<std::string>())
      ("c,cols",       "For random puzzle defines the number of columns",  cxxopts::value<std::string>())
      ("s,seed",       "For random puzzle defines seed value",             cxxopts::value<std::string>())
      ("p,puzzle",     "Read puzzle from file",                            cxxopts::value<std::string>())
      ("l,words-list", "Read list of words to search in puzzle from file", cxxopts::value<std::string>())
      ;
  
    auto result = options.parse( argc, argv );
    auto& arguments = result.arguments();

    // if no arguments is given, run interactiv
    if ( arguments.size() == 0 ) { return InteractiveShell( std::shared_ptr<Puzzle>() ); }

    PuzzleGenerator gen;

    // check if puzzle defined by file or some algorithm of puzzle generator
    std::shared_ptr<Puzzle> puzzle;
    if ( result.count( "generate" ) > 0 )
    {
      auto puzzleType = result["generate"].as<std::string>();
      if ( puzzleType == "wiki" )
      { 
         puzzle.swap( gen.generateWikiPuzzle() );
      }
      else
      {
        int rows = 10;
        int cols = 10;
        int seed = 0;
        if ( result.count( "seed" ) > 0 ) { seed = std::stoi( result["seed"].as <std::string>() ); }
        if ( result.count( "rows" ) > 0 && result.count( "cols" ) )
        {
          rows = std::stoi( result["rows"].as <std::string>() );
          cols = std::stoi( result["cols"].as <std::string>() );
        }
        else if ( result.count( "rows" ) > 0 ) { cols = rows = std::stoi( result["rows"].as <std::string>() ); }
        else if ( result.count( "cols" ) > 0 ) { rows = cols = std::stoi( result["cols"].as <std::string>() ); }
        puzzle.swap( gen.generateRandomPuzzle( seed, rows, cols ) );
      }
    }

    if ( result.count( "puzzle" ) > 0 )
    {
      auto puzzleFileName = result["puzzle"].as<std::string>();
      if ( puzzle ) { throw std::invalid_argument( "Puzzle is already defined as generated, can't read from file" ); }
      puzzle.swap( gen.loadPuzzleFromFile( puzzleFileName ) );
    }

    // load if words list is given by 
    std::shared_ptr<WordList> words2search;
    if ( result.count( "l" ) > 0 )
    {
      words2search.reset( new WordList() );
      words2search->loadFromFile( result["l"].as<std::string>() );
    }

    if ( !words2search ) { return InteractiveShell( puzzle ); }
    
    PuzzleSolver solver;
    Timer<> stopWatch;
    auto foundWords = solver.solvePuzzle( puzzle, *words2search );
    auto totTime = stopWatch.elapsedTime();

    std::cout << "Puzzle:" << std::endl << *puzzle << std::endl;
    std::cout << "Solver found the following words in puzzle:" << std::endl;

    for ( auto w : foundWords )
    {
      std::cout << "  " << w.first << " " << w.second;
    }

    std::cout << "Total words found: " << foundWords.size() << std::endl;
    std::cout << "Total time: " << totTime.count() / 1000.0 << " sec." << std::endl;
  }
  catch ( const std::exception & ex )
  {
    std::cerr << "Application exception: " << ex.what() << std::endl;
    return -1;
  }

  return 0;
}
