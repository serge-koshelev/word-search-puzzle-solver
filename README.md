Simple word search puzzle solver

Full description could be found on Wikipedia:
https://en.wikipedia.org/wiki/Word_search

To build code you need CMake > 3.10 and C++ compiler
Code was tested with VS2019

Build
	# Clone github repository:
	git clone https://github.com/serge-koshelev/word-search-puzzle-solver.git

   	# create build folder inside cloned code and change current directory
	mkdir build
	cd build

	# Linux using GNU make and g++
	  # generate makefiles
	  # it will automaticly download googletest framework from internet
	  cmake ..
	  # build
	  make
	  # install to build/bin folder
	  make install


	# Windows 
     # generate project and solution files for VS 2019
	  # it will automaticly download googletest framework from internet
	  cmake -G "Visual Studio 2019" ..
	  # build
	  # Open solution file in VS 2019 and build target ALL_BUILD
	  # install to build/bin folder
	  # build target INSTALL in solution


    # To run interactivly just start application 
    cd bin
	 ./WordPuzzle_run.exe  # on Linux
	 .\WordPuzzle_run.exe  # on Windows
