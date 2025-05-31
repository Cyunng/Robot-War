#ifndef ROBOT_H
#define ROBOT_H

#include <iostream>
#include <vector>

using namespace std;

class Battlefield; // Forward declatration of Battlefield class

class Robot {
protected:
    int robotPositionX = -1;
    int robotPositionY = -1; // -1 means uninitialized

    string id_ = ""; // Display robot id on the Battlefield such as "GR01"
    string robotType_ = "";
    string robotName_ = ""; // Robot id underscore robot name such as "GR05_Star"

    int numOfLives_ = 3;
    int numOfKills_ = 0;

    int shells_ = 10;

    vector<string> availableUpgrades_;
    vector<string> usedUpgrades_;

    bool isAlive_ = true;

    bool isHidden_ = false;
    int hideTurnsLeft_ = 0;

public:
    Robot(string id = "", int x = -1, int y = -1);

    virtual ~Robot() {}

    // Getters (Acessors)
    int x() const {
        return robotPositionX;
    }

    int y() const {
        return robotPositionY;
    }

    string id() const {
        return id_;
    }

    string robotType() const {
        return robotType_;
    }

    string robotName() const {
        return robotName_;
    }

    int numOfLives() const {
        return numOfLives_;
    }

    int numOfKills() const {
        return numOfKills_;
    }

    int getShells() const {
        return shells_;
    }

    bool isAlive() const {
        return isAlive_;
    }

    // Setters (Mutators)
    void setX(int x) {
        robotPositionX = x;
    }

    void setY(int y) {
        robotPositionY = y;
    }

    void setId(string id) {
        id_ = id;
    }

    void setRobotType(string robotType) {
        robotType_ = robotType;
    }

    void setRobotName(string robotName) {
        robotName_ = robotName;
    }

    void setNumOfLives(int numOfLives) {
        numOfLives_ = numOfLives;
        isAlive_ = numOfLives > 0;
    }

    void setNumOfKills(int numOfKills) {
        numOfKills_ = numOfKills;
    }

    void setShells(int shells) {
        shells_ = shells;
    }

    //Game mechanics
    void reduceLife() {
        if (--numOfLives_ <=0) {
            numOfLives_ = 0;
            isAlive_ = false;
        }
    }

    void incrementKills() {
        numOfKills_++;
    }

    // Hiding methods

    virtual bool canHide() const {
        return false;
    }

    bool isHidden() const {
        return isHidden_;
    }

    void setHidden(bool hidden, int turns = 0) {
        isHidden_ = hidden;
        hideTurnsLeft_ = turns;
    }

    void decrementHideTurns() {
        if (hideTurnsLeft_ > 0) {
            hideTurnsLeft_--;
        }

        if (hideTurnsLeft_ == 0) {
            isHidden_ = false;
        }
    }

    //Upgrade System
    bool canUpgrade() const {
        return !availableUpgrades_.empty() && usedUpgrades_.size() < 3;
    }

    string getNextUpgrade();

    // Pure virtual functions
    virtual void setLocation(int x, int y) = 0;
    virtual void actions(Battlefield* battlefield) = 0; // Turn actions
    virtual Robot* upgrade() = 0; // Upgrade to new robot type

    // Overloading the << operator for Robot class
    friend ostream& operator<<(ostream &out, const Robot& r);
};

// Abstract ThinkingRobot interface
class ThinkingRobot : virtual public Robot {
public:
    virtual ~ThinkingRobot() {}
    virtual void actionThink(Battlefield* battlefield) = 0; // Pure virtual function for thinking
};

// Abstract SeeingRobot interface
class SeeingRobot : virtual public Robot {
public:
    virtual ~SeeingRobot() {}
    virtual void actionLook(Battlefield* battlefield) = 0; // Pure virtual function for seeing
};

// Abstract ShootingRobot interface
class ShootingRobot : virtual public Robot {
public:
    virtual ~ShootingRobot() {}
    virtual void actionFire(Battlefield* battlefield) = 0; // Pure virtual function for shooting
};

// Abstract MovingRobot interface
class MovingRobot : virtual public Robot {
public:
    virtual ~MovingRobot() {}
    virtual void actionMove(Battlefield* battlefield) = 0; // Pure virtual function for moving
};

#endif