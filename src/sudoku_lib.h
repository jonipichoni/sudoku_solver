#ifndef SUDOKU_DLL_H
#define SUDOKU_DLL_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __WIN32__
#ifdef BUILD_LIB
#define SUDOKU_DLL __declspec(dllexport)
#else
#define SUDOKU_DLL __declspec(dllimport)
#endif
#else
#define SUDOKU_DLL       // Linux & other Unices : leave it blank !
#endif

//void __stdcall SUDOKU_DLL hello(const char *s);

//int SUDOKU_DLL Double(int x);

#ifdef __cplusplus
}
#endif
/*
// NOTE: this function is not declared extern "C"
void SUDOKU_DLL CppFunc(void);

// NOTE: this class must not be declared extern "C"
class SUDOKU_DLL MyClass
{
public:
        MyClass() {};
        virtual ~MyClass() {};
        void func(void);
};*/

// The size of the Sudoku game
static const unsigned blockSize = 3;
static const unsigned gridSize = blockSize * blockSize;

//
// Some functions for representing sets as bitfields
// (counting from 0)
//

typedef unsigned int bitfield;


class  SUDOKU_DLL Puzzle {
	// The value of any empty cell (i, j) comes from
	// rows[i] & cols[j] & blocks[i/3][j/3]
	bitfield rows[gridSize];
	bitfield cols[gridSize];
	bitfield blocks[blockSize][blockSize];

	// This contains invalid if the cell is empty,
	// its value otherwise.
	unsigned cells[gridSize][gridSize];

public:
	// This number is invalid, and represents an empty cell - 10
	static const unsigned invalid = gridSize + 1;

	Puzzle();

	// Return the set of values which could be at (i, j)
	inline bitfield candidates(unsigned i, unsigned j);

	// Fill in the cell at (i, j)
	inline void set(unsigned i, unsigned j, unsigned n);

	// Erase the cell at (i, j)
	inline void unset(unsigned i, unsigned j, unsigned n);

	// Find the cell with the lowest number of candidates
	// in the specified rectangular area.
	// It searches in iMin <= i < iMax
	// and jMin <= j < jMax
	// Return false if the grid is full.
	bool findMin(unsigned iMin, unsigned iMax, unsigned jMin, unsigned jMax,
		unsigned &outI, unsigned &outJ);

	// Returns the value of a certain cell, or invalid
	inline unsigned getCell(unsigned i, unsigned j);
};

// NOTE: this function is not declared extern "C"
void SUDOKU_DLL readPuzzle(unsigned char* values,Puzzle &p);

void SUDOKU_DLL outputSolution(Puzzle &p);

#endif  // SUDOKU_DLL_H