#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>
#include "Point.h"

class Gameboard
{
	friend int main();
	friend class TestSuite;

public:
	static constexpr int MAX_X = 10;		// gameboard x dimension
	static constexpr int MAX_Y = 19;		// gameboard y dimension
	static constexpr int EMPTY_BLOCK = -1;	// contents of an empty block

private:

	// the gameboard - a grid of X and Y offsets.  
	int _grid[MAX_Y][MAX_X];

	// the gameboard offset to spawn a new tetromino at.
	Point _spawnLoc{ MAX_X / 2, 0 };

public:
	// constructor - empty() the grid
	Gameboard();

	// fill the board with EMPTY_BLOCK 
	void empty();

	// print the grid contents to the console (for debugging purposes)
	void printToConsole() const;

	// get the content at a given point 
	int getContent(Point point) const;

	// get the content at a given XY location
	int getContent(int x, int y) const;

	// set the content at a given point (ignore invalid points)
	void setContent(Point point, int content);

	// set the content at an x,y position (ignore invalid points)
	void setContent(int x, int y, int content);

	// set the content for a set of points (ignore invalid points)
	void setContent(const std::vector<Point>& points, int content);

	// Determine if (valid) all points passed in are empty
	bool areAllLocsEmpty(const std::vector<Point>& points) const;

	// Remove all completed rows from the board
	int removeCompletedRows();

	// A getter for the spawn location
	Point getSpawnLoc() const;

private:

	// Determine if a given Point is a valid grid location
	static bool isValidPoint(Point point);

	// Determine if a given XY is a valid grid location
	static bool isValidPoint(int x, int y);

	// return a bool indicating if a given row is full (no EMPTY_BLOCK in the row)
	bool isRowCompleted(int rowIndex) const;

	// fill a given grid row with specified content
	void fillRow(int rowIndex, int content);

	// scan the board for completed rows.
	std::vector<int> getCompletedRowIndices() const;

	// copy a source row's contents into a target row
	void copyRowIntoRow(int sourceRowIndex, int targetRowIndex);

	// remove row and copy all rows above down 1
	void removeRow(int rowIndex);

	// remove the given rows
	void removeRows(const std::vector<int>& rowIndexes);
};

#endif /* GAMEBOARD_H */

