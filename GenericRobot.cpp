#include "GenericRobot.h"
#include "RobotType.h"

#include <iostream>
#include <vector>
#include <map>

using namespace std;

// Initialize static member
int GenericRobot::robotAutoIncrementInt_ = 0;

GenericRobot::GenericRobot(string id = "", int x = -1, int y = -1) : Robot(id, x, y) {
    id_ = id;
    robotPositionX = x;
    robotPositionY = y;

    setRobotType("GenericRobot");

    robotAutoIncrementInt_++;
}

// Getter
int GenericRobot::robotAutoIncrementInt() {
    return robotAutoIncrementInt_;
}

// Position Management
void GenericRobot::setLocation(int x, int y) {
    robotPositionX = x;
    robotPositionY = y;
}

// Action implementations
void GenericRobot::actionThink(Battlefield* battlefield) {
    cout << id_ << " is thinking..." << endl;
}

void GenericRobot::actionLook(Battlefield* battlefield) {
    cout << id_ << " is scanning the battlefield at range of " << lookRange_ << "..." << endl;

    for (int dx = -lookRange_; dx <= lookRange_; dx++) {

        for (int dy = -lookRange_; dy <= lookRange_; dy++) {

            if (dx == 0 && dy == 0) {
                continue;
            }

            int checkX = robotPositionX + dx;
            int checkY = robotPositionY + dy;

            if (battlefield->hasRobotAt(checkX, checkY)) {
                cout << "- Spotted robot at (" << checkX << "," << checkY << ")" << endl;
            }
        }
    }
}

void GenericRobot::actionFire(Battlefield* battlefield) {
    if (shells_ <= 0 && isAlive()) {
        cout << id_ << " has no ammo left and self-destructs!" << endl;
        reduceLife(); // Kill the robot
    }

    int targetX = robotPositionX + (rand() % 3) - 1;
    int targetY = robotPositionY + (rand() % 3) - 1;

    if (battlefield->hasRobotAt(targetX, targetY)) {
        Robot* target = battlefield->getRobotAt(targetX, targetY);

        if (target != this) {
            cout << id_ << " fires at (" << targetX << "," << targetY << ")!" << endl;

            shells_--;

            if (rand() % 100 < 70) {
                target->reduceLife();
                cout << "- Hit!" << target->id() << " now has " << target->numOfLives() << " lives left" << endl;

                if (!target->isAlive()) {
                    numOfKills_++;
                    cout << "-" << target->id() << " destroyed!" << endl;
                }
            }
            else {
                cout << "- Oops, missed!" << endl;
            }
        }
        else {
            cout << id_ << " fires but misses!" << endl;
            shells_--;
        }
    }
}

void GenericRobot::actionMove(Battlefield* battlefield) {
    int dx = (rand() % 3) - 1;
    int dy = (rand() & 3) - 1;

    int newX = robotPositionX + dx;
    int newY = robotPositionY + dy;

    if (newX >= 0 && newX < battlefield->getBattlefieldColumns() && newY >= 0 && newY < battlefield->getBattlefieldRows() && battlefield->isPositionEmpty(newX, newY)) {
        setLocation(newX, newY);
        cout << id_ << " moves to (" << newX << "," << newY << ")" << endl;
    }
    else {
        cout << id_ << " tried to move but failed" << endl;
    }
}

void GenericRobot::actions(Battlefield* battlefield) {
    int randomActionThink = rand() % 2; //Randmoize action order to be 50% chance

    if (randomActionThink == 0) {
        // Order 1: Think -> Look -> Fire -> Move
        actionThink(battlefield);
        actionLook(battlefield);
        actionFire(battlefield);
        actionMove(battlefield);
    }
    else {
        // Order 2: Think -> Look -> Move -> Fire
        actionThink(battlefield);
        actionLook(battlefield);
        actionMove(battlefield);
        actionFire(battlefield);
    }

    if (isHidden_) {
        hideTurnsLeft_--;
        if (hideTurnsLeft_ <= 0) {
            isHidden_ = false;
            cout << id_ << " is no longer hidden!" << endl;
        }
    }
}

// Upgrade System
Robot* GenericRobot::upgrade() {
    if (!canUpgrade()) {
        return nullptr;
    }

    string upgradeType = getNextUpgrade();
    Robot* upgraded = nullptr;

    // Create appropriate upgraded robot
    if (upgradeType == "HideBot") {
        upgraded = new HideBot(id_, robotPositionX, robotPositionY);
    }
    else if (upgradeType == "JumpBot") {
        upgraded = new JumpBot(id_, robotPositionX, robotPositionY);
    }
    else if (upgradeType == "TeleportBot") {
        upgraded = new TeleportBot(id_, robotPositionX, robotPositionY);
    }
    else if (upgradeType == "LongShotBot") {
        upgraded = new LongShotBot(id_, robotPositionX, robotPositionY);
    }
    else if (upgradeType == "SemiAutoBot") {
        upgraded = new SemiAutoBot(id_, robotPositionX, robotPositionY);
    }
    else if (upgradeType == "ThirtyShotBot") {
        upgraded = new ThirtyShotBot(id_, robotPositionX, robotPositionY);
    }
    else if (upgradeType == "ShieldBot") {
        upgraded = new ShieldBot(id_, robotPositionX, robotPositionY);
    }
    else if (upgradeType == "ScoutBot") {
        upgraded = new ScoutBot(id_, robotPositionX, robotPositionY);
    }
    else if (upgradeType == "TrackBot") {
        upgraded = new TrackBot(id_, robotPositionX, robotPositionY);
    }
    else if (upgradeType == "RadarBot") {
        upgraded = new RadarBot(id_, robotPositionX, robotPositionY);
    }

    if (upgraded) {
        // Transfer current state to new robot
        upgraded->setNumOfLives(numOfLives_);
        upgraded->setNumOfKills(numOfKills_);
    }

    return upgraded;
}

// Special Ability Accessors
int GenericRobot::getShellCount() const {
    return shells_;
}

int GenericRobot::getMovementRange() const {
    return 1;
}

bool GenericRobot::isHidden() const {
    return isHidden_;
}

int GenericRobot::getTrackersLeft() const {
    return trackersLeft_;
}
