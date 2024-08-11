#include "Tetromino.h"
#include <iostream>
using namespace std;

Tetromino::Tetromino()
{
    _color = TetColor{};
    setShape(TetShape::S);
}
Tetromino::Tetromino(const TetColor color, const TetShape shape) : _color(color)
{
    setShape(shape);
    setColorFromShape(shape);
}

void Tetromino::rotateClockwise()
{
    if (_shape == TetShape::O) return;

    for (auto& point : _blockLocs)
    {
        point.multiplyX(-1);
        point.swapXY();
    }
}

void Tetromino::printToConsole() const
{
    for (int y = 3; y > -3; y--)
    {
        for (int x = -3; x <= 3; x++)
        {
            const Point point = Point(x, y);
            string pointString = containsPoint(point) ? "X" : "-";
            cout << pointString;
        }
        cout << endl;
    }
    cout << endl;
}

TetShape Tetromino::getShape() const { return _shape; }
TetColor Tetromino::getColor() const { return _color; }
void Tetromino::setShape(const TetShape shape)
{
    _blockLocs.clear();
    _shape = shape;
    _blockLocs.emplace_back(0, 0);

    switch (_shape)
    {
    case S:
        _blockLocs.emplace_back(-1, 0);
        _blockLocs.emplace_back(0, 1);
        _blockLocs.emplace_back(1, 1);
        break;
    case Z:
        _blockLocs.emplace_back(1, 0);
        _blockLocs.emplace_back(0, 1);
        _blockLocs.emplace_back(-1, 1);
        break;
    case L:
        _blockLocs.emplace_back(0, 1);
        _blockLocs.emplace_back(0, -1);
        _blockLocs.emplace_back(1, -1);
        break;
    case J:
        _blockLocs.emplace_back(0, 1);
        _blockLocs.emplace_back(0, -1);
        _blockLocs.emplace_back(-1, -1);
        break;
    case O:
        _blockLocs.emplace_back(0, 1);
        _blockLocs.emplace_back(1, 1);
        _blockLocs.emplace_back(1, 0);
        break;
    case I:
        _blockLocs.emplace_back(0, 2);
        _blockLocs.emplace_back(0, 1);
        _blockLocs.emplace_back(0, -1);
        break;
    case T:
        _blockLocs.emplace_back(-1, 0);
        _blockLocs.emplace_back(1, 0);
        _blockLocs.emplace_back(0, -1);
        break;
    }

    setColorFromShape(_shape);
}

void Tetromino::setColorFromShape(TetShape shape)
{
    switch (shape) {
    case Z: _color = RED; break;
    case O: _color = YELLOW; break;
    case S: _color = GREEN; break;
    case L: _color = ORANGE; break;
    case J: _color = BLUE_DARK; break;
    case I: _color = BLUE_LIGHT; break;
    case T: _color = PURPLE; break;
    default: _color = RED;
    }
}

bool Tetromino::containsPoint(const Point point) const
{
    return std::find(_blockLocs.begin(), _blockLocs.end(), point) != _blockLocs.end();
}

TetShape Tetromino::getRandomShape()
{
    int maxIndex = static_cast<int>(TetShape::COUNT);
    int randIndex = std::rand() % (maxIndex);
    return static_cast<TetShape>(randIndex);
}

