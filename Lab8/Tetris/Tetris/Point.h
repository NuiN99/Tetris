#pragma once
#include <string>

class Point
{
    friend class TestSuite;
public:
    // default constructor
    Point();

    // constructor
    Point(int x, int y);

    // getter for _x
    int getX() const;

    // getter for _y
    int getY() const;

    // setter for _x
    void setX(int x);

    // getter for _y
    void setY(int y);

    // setter for _x and _y
    void setXY(int x, int y);

    // swaps _x and _y
    void swapXY();

    // multiplies _x by a factor
    void multiplyX(int factor);

    // multiplies _y by a factor
    void multiplyY(int factor);

    // add to X and return it
    int getAddX(int increment);

    // add to Y and return it
    int getAddY(int increment);

    // return a string in the form "[x,y]" to represent the state of the Point instance
    std::string toString() const;

    // comparison operator overload
    bool operator==(const Point& other) const {
        return (_x == other.getX()) && (_y == other.getY());
    }

private:
    int _x, _y;
};
