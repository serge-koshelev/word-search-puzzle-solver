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

#ifndef TIMER_HH
#define TIMER_HH

#include <chrono>

/// @brief Simple timer to mesure perfomance of algorithms
template<typename type = double, typename period = std::milli>
class Timer
{
  public:
    using clock       = std::chrono::high_resolution_clock;
    using duration    = std::chrono::duration<type, period>;
    using time_point  = std::chrono::time_point<clock, duration>;

    Timer() : _startTime( clock::now() ) { ; }

    Timer( const Timer& that ) = default;
    Timer( Timer&& temp ) = default;
    ~Timer() = default;
    Timer& operator=( const Timer& that ) = default;
    Timer& operator=( Timer&& temp ) = default;

    duration elapsedTime() { return clock::now() - _startTime; }
  
    void restart() { _startTime = clock::now(); }

  private:
    time_point _startTime;
};

#endif