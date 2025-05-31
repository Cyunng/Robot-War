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

    vector<string> availableUpgrades_;
    vector<string> usedUpgrades_;

public:
    Robot(string id = "", int x = -1, int y = -1);

    virtual ~Robot() {}

    // Getters (Acessors)
    int x() const;

    int y() const;

    string id() const;

    string robotType() const;

    string robotName() const;

    int numOfLives() const;

    int numOfKills() const;

    const vector<string>& getUsedUpgrades() const;

    // Setters (Mutators)
    void setX(int x);

    void setY(int y);

    void setId(string id);

    void setRobotType(string robotType);

    void setRobotName(string robotName);

    void setNumOfLives(int numOfLives);

    void setNumOfKills(int numOfKills);

    //Game mechanics
    void reduceLife();

    void incrementKills();

    bool isAlive() const;

    //Upgrade System
    bool canUpgrade() const;

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
    virtual int getShellCount() const = 0;
};

// Abstract MovingRobot interface
class MovingRobot : virtual public Robot {
public:
    virtual ~MovingRobot() {}
    virtual void actionMove(Battlefield* battlefield) = 0; // Pure virtual function for moving
    virtual int getMovementRange() const = 0;
};

#endif