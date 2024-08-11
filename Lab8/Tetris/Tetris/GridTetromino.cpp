#include "GridTetromino.h"

GridTetromino::GridTetromino()
{
	_gridLoc = Point(0, 0);
}

Point GridTetromino::getGridLoc() const
{
	return _gridLoc;
}

void GridTetromino::setGridLoc(int x, int y)
{
	_gridLoc.setXY(x, y);
}

void GridTetromino::setGridLoc(Point point)
{
	_gridLoc = point;
}

void GridTetromino::move(int xOffset, int yOffset)
{
	_gridLoc.setXY(_gridLoc.getX() + xOffset, _gridLoc.getY() + yOffset);
}


std::vector<Point> GridTetromino::getBlockLocsMappedToGrid() const
{
	std::vector<Point> mappedPoints;
	for (auto& point : _blockLocs) {
		mappedPoints.emplace_back(point.getX() + _gridLoc.getX(), point.getY() + _gridLoc.getY());
	}

	return mappedPoints;
}
