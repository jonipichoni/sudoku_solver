#include <stdio.h>
#include <iostream>
#include <cassert>

#include "sudoku_lib.h"

using namespace std;

// No bit we'll be using is above this - 1 000 000 000
static const bitfield maskMax = 1 << gridSize;

// A bitfield with all bits set - 0 111 111 111
static const bitfield allSet = maskMax - 1;

// Returns the size of the set
unsigned int bitCount(bitfield bits) {
	unsigned result = 0;
	bitfield mask = 1;

	//@TODO LUT!
	while(mask != maskMax) {
		if (bits & mask)
			result++;
		mask *= 2;
	}

	return result;
}

// Returns a bitfield representing {num}
bitfield bitFor(unsigned int num) {
	//@TODO LOOKUP table
	return 1 << (num - 1);
}


Puzzle::Puzzle() {
	// Better initialise the arrays
	unsigned i, j;

	// Improve initialization
	for (i = 0; i < gridSize; i++) rows[i] = allSet;
	for (i = 0; i < gridSize; i++) cols[i] = allSet;

	for (i = 0; i < blockSize; i++)
		for (j = 0; j < blockSize; j++)
			blocks[i][j] = allSet;

	for (i = 0; i < gridSize; i++)
		for (j = 0; j < gridSize; j++)
			cells[i][j] = invalid;
}

// Return the set of values which could be at (i, j)
inline bitfield Puzzle::candidates(unsigned i, unsigned j) {
	// @TODO - DONT terminate
	assert(cells[i][j] == invalid);

	return rows[i] & cols[j] & 
		blocks[i/blockSize][j/blockSize];
}

// Fill in the cell at (i, j)
inline void Puzzle::set(unsigned i, unsigned j, unsigned n) {
	bitfield bit = bitFor(n);

	// Check this is a valid value for the cell
	assert((candidates(i, j) & bit) != 0);

	// No other cells in the row, column or block
	// can now have this value
	rows[i] &= ~bit;
	cols[j] &= ~bit;
	blocks[i/blockSize][j/blockSize] &= ~bit;
	cells[i][j] = n;
}

// Erase the cell at (i, j)
inline void Puzzle::unset(unsigned i, unsigned j, unsigned n) {
	bitfield bit = bitFor(n);

	// Make sure it was already set
	assert(cells[i][j] == n);

	rows[i] |= bit;
	cols[j] |= bit;
	blocks[i/blockSize][j/blockSize] |= bit;
	cells[i][j] = invalid;
}

// Find the cell with the lowest number of candidates
// in the specified rectangular area.
// It searches in iMin <= i < iMax
// and jMin <= j < jMax
// Return false if the grid is full.
bool Puzzle::findMin(unsigned iMin, unsigned iMax, unsigned jMin, unsigned jMax,
	unsigned &outI, unsigned &outJ)
{
	bool found = false;
	unsigned count = 0;

	for (unsigned i = iMin; i < iMax; i++)
		for (unsigned j = jMin; j < jMax; j++)
			if (cells[i][j] == invalid &&	
				(!found || bitCount(candidates(i, j)) < count))
			{
				count = bitCount(candidates(i, j));
				outI = i;
				outJ = j;
				found = true;
			}

	return found;
}

// Returns the value of a certain cell, or invalid
inline unsigned Puzzle::getCell(unsigned i, unsigned j) { return cells[i][j]; }

// Tries to solve the puzzle in-place. It returns true if it could fill in
// all the squares between iMin and iMax and jMin and jMax, false otherwise.
// If destructive is false it will reverse all its changes once it
// finds a solution or gives up.
// If checkBlocks is true it will try to fill in each 3x3 block separately
// before it starts - if it can't do that then it can't solve the puzzle

bool solve(Puzzle &puzzle, unsigned iMin, unsigned iMax,
	unsigned jMin, unsigned jMax, bool destructive, bool checkBlocks)
{
	// Check that each block can be filled if we've been asked to
	if (checkBlocks) {
		for (unsigned i = 0; i < blockSize; i++)
			for (unsigned j = 0; j < blockSize; j++)
				if (!solve(puzzle,
					i*blockSize, i*blockSize + blockSize,
					j*blockSize, j*blockSize + blockSize, 
					false, false))
						return false;
	}

	// Guess a good cell to brute-force with
	unsigned i;
	unsigned j;

	if (!puzzle.findMin(iMin, iMax, jMin, jMax, i, j))
		// We must have finished
		return true;

	// Iterate through the possible values this cell could have
	unsigned num = 1;
	unsigned mask = bitFor(num);

	while(mask != maskMax) {
		if (puzzle.candidates(i, j) & mask) {

			// Try this number
			puzzle.set(i, j, num);

			bool solved = (solve(puzzle, iMin, iMax, jMin, jMax, 
				destructive, checkBlocks));

			// Reverse the changes if needed
			if (!solved || !destructive)
				puzzle.unset(i, j, num);

			if (solved)
				return true;

		}
			

		// Advance to the next number
		mask *= 2;
		num++;
	}

	// None of the possibilities for cell (i,j) work
	return false;
}

// Reads in a puzzle from standard input
void readPuzzle(Puzzle &p) {
	for (unsigned i = 0; i < gridSize; i++) {
		for (unsigned j = 0; j < gridSize; j++) {
			char c;
			cin >> c;
			if (c >= '1' && c <= '9') {
				c = c - '0';
				// Refuse to input an invalid puzzle

				if ((p.candidates(i, j) & bitFor(c)) == 0)
					return; //@todo return something
				else
					p.set(i, j, c);
			} else if (c == '.') {
			} else return; //@todo return something
		}

		//cin >> endl;
	}
}

// Reads in a puzzle from standard input
void readPuzzle(unsigned char* values,Puzzle &p) {
	for (unsigned i = 0; i < gridSize; i++) {
		for (unsigned j = 0; j < gridSize; j++) {

			char c = values[i* gridSize + j];

			std::cout << "Value at i: "<< i << " j: " << j << " array pos: " << i* gridSize + j << "val:" << (int)c << std::endl;

			if (c >= 1 && c <= 9) {
				// Refuse to input an invalid puzzle
				if ((p.candidates(i, j) & bitFor(c)) == 0)
					return; //@todo return something
				else
					p.set(i, j, c);
			} else if (c == 0) {
			} else return; // @todo return something
		}

		//cin >> endl;
	}
}

// Prints out a (hopefully) completed puzzle
void printPuzzle(Puzzle &p) {
	for (unsigned i = 0; i < gridSize; i++) {
		for (unsigned j = 0; j < gridSize; j++) {
			if (p.getCell(i, j) == p.invalid)
				cout << " ";
			else
				cout << p.getCell(i, j);
		}

		cout << endl;
	}
}

// Solve and print out a puzzle
void outputSolution(Puzzle &p) {
	if (solve(p, 0, gridSize, 0, gridSize, true, true))
		printPuzzle(p);
}