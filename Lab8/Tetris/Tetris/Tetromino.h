#ifndef TETROMINO_H
#define TETROMINO_H

#include <vector>
#include "Point.h"

enum TetColor { RED, ORANGE, YELLOW, GREEN, BLUE_LIGHT, BLUE_DARK, PURPLE };
enum TetShape { S, Z, L, J, O, I, T, COUNT };

class Tetromino
{
    friend class TestSuite;
public:

    // default constructor
    Tetromino();

    // constructor
    Tetromino(TetColor color, TetShape shape);

    // rotate the shape 90 degrees around [0,0] (clockwise)
    void rotateClockwise();

    // print a grid to display the current shape
    void printToConsole() const;

    // getter for _shape
    TetShape getShape() const;

    // getter for _color
    TetColor getColor() const;

    // set the shape and update _blockLocations accordingly
    void setShape(TetShape shape);

    void setColorFromShape(TetShape shape);

    // returns true if the point argument or an identical version of it is contained in the _blockLocations vector
    bool containsPoint(const Point point) const;

    static TetShape getRandomShape();

protected:
    TetColor _color;
    TetShape _shape;
    std::vector<Point> _blockLocs;
};

#endif // !1
