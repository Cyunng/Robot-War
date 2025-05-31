#ifndef GENERIC_ROBOT_H
#define GENERIC_ROBOT_H

#include "Robot.h"
#include "Battlefield.h"

#include <iostream>
#include <vector>
#include <map>

using namespace std;

class GenericRobot : public ThinkingRobot, public SeeingRobot, public ShootingRobot, public MovingRobot {
private:
    // Static member for auto-incrementing ID
    static int robotAutoIncrementInt_;

    // Combat Attributes
    int shells_ = 10;
    int fireRange_ = 1;

    // Vision Atrributes
    int lookRange_ = 1;
    int trackersLeft_ = 3;
    map<string, pair<int, int>> trackedRobots_; // Tracked enemies

    // Movement Attributes
    bool isHidden_ = false;
    int hideTurnsLeft_ = 0;

public:
    GenericRobot(string id, int x, int y);

    // Static getter
    static int robotAutoIncrementInt();

    virtual ~GenericRobot() {}

    // Position Management
    virtual void setLocation(int x, int y);

    // Action implementations
    virtual void actionThink(Battlefield* battlefield);
    virtual void actionLook(Battlefield* battlefield);
    virtual void actionFire(Battlefield* battlefield);
    virtual void actionMove(Battlefield* battlefield);
    virtual void actions(Battlefield* battlefield);

    // Upgrade System
    virtual Robot* upgrade();

    // Special Ability Accessors
    int getShellCount() const;

    int getMovementRange() const;

    bool isHidden() const;

    int getTrackersLeft() const;
};

#endif