#ifndef ROBOT_H
#define ROBOT_H

#include <iostream>
using namespace std;

struct Position {
    int x, y;

    Position(int x = 0, int y = 0) : x(x), y(y) {}

    bool operator == (const Position& other) const {
        return x == other.x && other.y;
    }
};

class Robot {
protected:
    string name;
    Position position;
    int lives;
    bool alive;
    bool hidden;

public:
    
};

#endif