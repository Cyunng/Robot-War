#ifndef ROBOT_H
#define ROBOT_H

#include <iostream>
#include <vector>
using namespace std;

/*
struct Position {
    int x, y;

    Position(int x = 0, int y = 0) : x(x), y(y) {}

    // Check if 2 positions are equal
    bool operator == (const Position& other) const {
        return x == other.x && y == other.y;
    }
};
*/

class Battlefield; // Forward declatration of Battlefield class

class Robot {
protected:
    int robotPositionX = -1;
    int robotPositionY = -1; // -1 means uninitialised

    string id_ = ""; // Display robot id on the Battlefield such as "GR01"
    string robotType_ = "";
    string robotName_ = ""; // Robot id underscore robot name such as "GR05_Star"

    int numOfLives_ = 3;
    int numOfKills_ = 0;

    vector<string> availableUpgrades_;
    vector<string> usedUpgrades_;

public:
    Robot(string id = "", int x = -1, int y = -1) : id_(id), robotPositionX(x), robotPositionY(y) {
        availableUpgrades_ = {"HideBot", "JumpBot", "TeleportBot", "LongShotBot", "SemiAutoBot", "ThirtyShotBot", "ShieldBot", "ScoutBot", "TrackBot", "RadarBot"};
    }

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
    }

    void setNumOfKills(int numOfKills) {
        numOfKills_ = numOfKills;
    }

    //Game mechanics
    void reduceLife() {
        if (numOfLives_ > 0) {
            numOfLives_--;
        }
    }

    void incrementKills() {
        numOfKills_++;
    }

    bool isAlive() const {
        return numOfLives_ > 0;
    }

    //Upgrade System
    bool canUpgrade() const {
        return !availableUpgrades_.empty() && usedUpgrades_.size() < 3;
    }

    string getNextUpgrade() {
        if (!canUpgrade()) {
            return "";
        }
        string upgrade = availableUpgrades_.back();
        availableUpgrades_.pop_back();
        usedUpgrades_.push_back(upgrade);
        return upgrade;
    }

    // Pure virtual functions
    virtual void setLocation(int x, int y) = 0;
    virtual void actions(Battlefield* battlefield) = 0; // Turn actions
    virtual Robot* upgrade() = 0; // Upgrade to new robot type

    // Overloading the <, operator for Robot class
    friend ostream& operator<<(ostream &out, const Robot& r) {
        out << r.id_ << " at (" << r.robotPositionX << ", " << r.robotPositionY << ")";
        return out;
    }
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