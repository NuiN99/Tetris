#include "Point.h"

Point::Point() : _x(0), _y(0) { }
Point::Point(const int x, const int y) : _x(x), _y(y) { }

void Point::setXY(const int x, const int y)
{
    _x = x;
    _y = y;
}

void Point::swapXY()
{
    const int x = _x;
    _x = _y;
    _y = x;
}

int Point::getX() const { return _x; }

int Point::getY() const { return _y; }

void Point::setX(const int x) { _x = x; }

void Point::setY(const int y) { _y = y; }

void Point::multiplyX(const int factor) { _x *= factor; }

void Point::multiplyY(const int factor) { _y *= factor; }

int Point::getAddX(int increment)
{
    _x += increment;
    return _x;
}

int Point::getAddY(int increment)
{
    _y += increment;
    return _y;
}

std::string Point::toString() const
{
    return "[" + std::to_string(_x) + "," + std::to_string(_y) + "]";
}



