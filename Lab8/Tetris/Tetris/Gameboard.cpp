#include "Gameboard.h"

#include <cassert>
#include <iomanip>
#include <iostream>

Gameboard::Gameboard() {
    empty();
}

void Gameboard::empty() {
    for (int i = 0; i < MAX_Y; ++i) {
        fillRow(i, EMPTY_BLOCK);
    }
}

void Gameboard::printToConsole() const
{
    for (int y = 0; y < MAX_Y; ++y) {
        for (int x = 0; x < MAX_X; ++x) {
            const int content = _grid[y][x];
            if (content == EMPTY_BLOCK) {
                std::cout << std::setw(2) << '.';
            }
            else {
                std::cout << std::setw(2) << content;
            }
        }
        std::cout << std::endl;
    }
}


int Gameboard::getContent(const Point point) const
{
    assert(isValidPoint(point));
    return _grid[point.getY()][point.getX()];
}

int Gameboard::getContent(const int x, const int y) const
{
    assert(isValidPoint(x, y));
    return _grid[y][x];
}

void Gameboard::setContent(const Point point, const int content) {
    if (isValidPoint(point)) {
        _grid[point.getY()][point.getX()] = content;
    }
}

void Gameboard::setContent(const int x, const int y, const int content) {
    if (isValidPoint(x, y)) {
        _grid[y][x] = content;
    }
}

void Gameboard::setContent(const std::vector<Point>& points, int content) {
    for (const Point& point : points) {
        setContent(point, content);
    }
}

bool Gameboard::areAllLocsEmpty(const std::vector<Point>& points) const
{
    for (const Point& point : points) {
        if (isValidPoint(point) && getContent(point) != EMPTY_BLOCK) {
            return false;
        }
    }
    return true;
}

int Gameboard::removeCompletedRows() {
    const std::vector<int> completedRows = getCompletedRowIndices();
    const int completedRowCount = completedRows.size();
    if (completedRowCount > 0) {
        removeRows(completedRows);
    }
    return completedRowCount;
}

Point Gameboard::getSpawnLoc() const
{
    return _spawnLoc;
}

bool Gameboard::isValidPoint(Point point)
{
    return isValidPoint(point.getX(), point.getY());
}

bool Gameboard::isValidPoint(int x, int y) {
    return x >= 0 && x < MAX_X && y >= 0 && y < MAX_Y;
}

bool Gameboard::isRowCompleted(int rowIndex) const
{
    assert(rowIndex >= 0 && rowIndex < MAX_Y);
    for (int x = 0; x < MAX_X; ++x) {
        if (_grid[rowIndex][x] == EMPTY_BLOCK) {
            return false;
        }
    }
    return true;
}

void Gameboard::fillRow(const int rowIndex, const int content) {
    assert(rowIndex >= 0 && rowIndex < MAX_Y);
    for (int x = 0; x < MAX_X; ++x) {
        _grid[rowIndex][x] = content;
    }
}

std::vector<int> Gameboard::getCompletedRowIndices() const
{
    std::vector<int> completedRows;
    for (int y = 0; y < MAX_Y; ++y) {
        if (isRowCompleted(y)) {
            completedRows.push_back(y);
        }
    }
    return completedRows;
}

void Gameboard::copyRowIntoRow(int sourceRowIndex, int targetRowIndex) {
    assert(sourceRowIndex >= 0 && sourceRowIndex < MAX_Y);
    assert(targetRowIndex >= 0 && targetRowIndex < MAX_Y);
    for (int x = 0; x < MAX_X; ++x) {
        _grid[targetRowIndex][x] = _grid[sourceRowIndex][x];
    }
}

void Gameboard::removeRow(const int rowIndex) {
    assert(rowIndex >= 0 && rowIndex < MAX_Y);
    for (int y = rowIndex; y > 0; --y) {
        copyRowIntoRow(y - 1, y);
    }
    fillRow(0, EMPTY_BLOCK);
}

void Gameboard::removeRows(const std::vector<int>& rowIndexes) {
    for (const int rowIndex : rowIndexes) {
        removeRow(rowIndex);
    }
}
