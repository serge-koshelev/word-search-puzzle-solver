Simple word search puzzle solver

The full description of word search puzzle, could be found on Wikipedia:
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

          # Note:
	    Visual Studio 2019 also support cmake directily. You could open
	    clonned folder in Visual Studio and in Solution explorer switch view
	    to "CMake Targets View". In this case, Visual Studio itsel will run cmake
	    and configure the project. You could right click on WordPuzzle_run target and select "Build"
	    and then "Incstall"

    # To run interactivly just start application 
    cd bin
	 ./WordPuzzle_run  # on Linux
	 .\WordPuzzle_run.exe  # on Windows
	 
    # Examples for command line options:
    # Generate random puzzle 20x20 with seed 1 and search words from file uk.dic
    WordPuzzle_run.exe -g random -c 20 -r 20 -s 1 -l uk.dic
