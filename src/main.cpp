
/*
		unsigned char ex[SIZE][SIZE] = { 
			{0, 2, 0, 0, 0, 0, 0, 7, 0} ,
			{0, 0, 9, 8, 0, 2, 4, 0, 0} ,
			{4, 8, 0, 0, 0, 0, 0, 2, 5} ,
			{0, 0, 7, 3, 0, 4, 1, 0, 0} ,
			{3, 0, 0, 0, 0, 0, 0, 0, 4} ,
			{0, 0, 2, 5, 0, 6, 8, 0, 0} ,
			{5, 7, 0, 0, 0, 0, 0, 8, 6} ,
			{0, 0, 4, 7, 0, 1, 2, 0, 0} ,
			{0, 9, 0, 0, 0, 0, 0, 4, 0} 
		};

		unsigned char ex_solution[SIZE][SIZE] = { 
			{1, 2, 5, 9, 4, 3, 6, 7, 8} ,
			{7, 6, 9, 8, 5, 2, 4, 1, 3} ,
			{4, 8, 3, 1, 6, 7, 9, 2, 5} ,
			{8, 5, 7, 3, 9, 4, 1, 6, 2} ,
			{3, 1, 6, 2, 7, 8, 5, 9, 4} ,
			{9, 4, 2, 5, 1, 6, 8, 3, 7} ,
			{5, 7, 1, 4, 2, 9, 3, 8, 6} ,
			{6, 3, 4, 7, 8, 1, 2, 5, 9} ,
			{2, 9, 8, 6, 3, 5, 7, 4, 1} 
		};


*/
//
// The following code is public domain (written in 2005 by Nick Smallbone)
// It can be found at http://www.8325.org/sudoku/
//

// It works by keeping track of which numbers can be used to fill the remaining
// cells in each row, column and block. It then will only fill a cell with a
// number that is valid for that row, column and block.

// On every recursion, it chooses the cell with the least possible number
// available to choose from. This has the rather nice effect that impossible
// cells are noticed straight away without any special cases, and cells with
// only one possibility are filled in straight away.
#include <stdio.h>
#include <iostream>
#include "sudoku_lib.h"
#include "config.h"

using namespace std;


int main() {

	fprintf(stdout,"Sudoku Resolver Version %d.%d\n",
						S_VERSION_MAJOR,
						S_VERSION_MINOR);

	Puzzle p;

	unsigned char ex[SIZE][SIZE] = { 
			{0, 2, 0, 0, 0, 0, 0, 7, 0} ,
			{0, 0, 9, 8, 0, 2, 4, 0, 0} ,
			{4, 8, 0, 0, 0, 0, 0, 2, 5} ,
			{0, 0, 7, 3, 0, 4, 1, 0, 0} ,
			{3, 0, 0, 0, 0, 0, 0, 0, 4} ,
			{0, 0, 2, 5, 0, 6, 8, 0, 0} ,
			{5, 7, 0, 0, 0, 0, 0, 8, 6} ,
			{0, 0, 4, 7, 0, 1, 2, 0, 0} ,
			{0, 9, 0, 0, 0, 0, 0, 4, 0} 
		};

	//readPuzzle(p);
	readPuzzle((unsigned char *)ex,p);

	outputSolution(p);
	
	return 0;
}	