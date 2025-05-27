#ifndef GENERIC_ROBOT_H
#define GENERIC_ROBOT_H

#include "Robot.h"
#include "BattleField.h"

#include <iostream>
#include <map>
#include <cstdlib>

using namespace std;

class GenericRobot : public ThinkingRobot, public SeeingRobot, public ShootingRobot, public MovingRobot {
private:
    // Static member for auto-incrementing ID
    static int robotAutoIncrementInt_;

    // Combat Attributes
    int shells_ = 10;
    int fireRange_ = 1;
    bool shieldActive_ = false;
    int shieldCharges_ = 0;

    // Vision Atrributes
    int lookRange_ = 1;
    int scoutUsesLeft_ = 0;
    int trackersLeft_ = 3;
    map<string, pair<int, int>> trackedRobots_; // Tracked enemies
    int radarUses_ = 0;
    int radarRange_ = 0;

    // Movement Attributes
    bool isHidden_ = false;
    int hideTurnsLeft_ = 0;
    int jumpCount_ = 0;
    int teleportCharges_ = 0;

public:
    GenericRobot(string id = "", int x = -1, int y = -1) : Robot(id, x, y) {
        id_ = id;
        robotPositionX = x;
        robotPositionY = y;

        robotType_ = "GenericRobot";

        robotAutoIncrementInt_++;
    }

    // Static getter
    static int robotAutoIncrementInt() {
        return robotAutoIncrementInt_;
    }

    virtual ~GenericRobot() {}

    // Position Management
    virtual void setLocation(int x, int y) {
        robotPositionX = x;
        robotPositionY = y;
    }

    // Action implementations
    virtual void actionThink(Battlefield* battlefield);
    virtual void actionLook(Battlefield* battlefield);
    virtual void actionFire(Battlefield* battlefield);
    virtual void actionMove(Battlefield* battlefield);

    virtual void actions(Battlefield* battlefield) {
        int randomActionThink = rand() % 2; //Randmoise action order to be 50% chance

        if(randomActionThink == 0) {
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

    /*
        if(isHidden_) {
            hideTurnsLeft_--;
            if(hideTurnsLeft_ <= 0) {
                isHidden_ = false;
                cout << id_ << " is no longer hidden!" << endl;
            }
        }
    */
    }

    /*
    // Upgrade System
    virtual Robot* upgrade() {
        if(!canUpgrade()) {
            return nullptr;
        }

        string upgradeType = getNextUpgrade();
        Robot* upgraded = nullptr;

        // Create appropriate upgraded robot
        if(upgradeType == "HideBot") {
            upgraded = new HideBot(id_, robotPositionX, robotPositionY);
        }
        else if(upgradeType == "JumpBot") {
            upgraded = new JumpBot(id_, robotPositionX, robotPositionY);
        }
        else if(upgradeType == "JumpBot") {
            upgraded = new JumpBot(id_, robotPositionX, robotPositionY);
        }
        else if(upgradeType == "TeleportBot") {
            upgraded = new TeleportBot(id_, robotPositionX, robotPositionY);
        }
        else if(upgradeType == "LongShotBot") {
            upgraded = new LongShotBot(id_, robotPositionX, robotPositionY);
        }
        else if(upgradeType == "SemiAutoBot") {
            upgraded = new SemiAutoBot(id_, robotPositionX, robotPositionY);
        }
        else if(upgradeType == "ThirtyShotBot") {
            upgraded = new ThirtyShotBot(id_, robotPositionX, robotPositionY);
        }
        else if(upgradeType == "ShieldBot") {
            upgraded = new ShieldBot(id_, robotPositionX, robotPositionY);
        }
        else if(upgradeType == "ScoutBot") {
            upgraded = new ScoutBot(id_, robotPositionX, robotPositionY);
        }
        else if(upgradeType == "TrackBot") {
            upgraded = new TrackBot(id_, robotPositionX, robotPositionY);
        }
        else if(upgradeType == "RadarBot") {
            upgraded = new RadarBot(id_, robotPositionX, robotPositionY);
        }

        if(upgraded) {
            // Transfer current state to new robot
            upgraded->setNumOfLives(numOfLives_);
            upgraded->setNumOfKills(numOfKills_);
        }

        return upgraded;
    }
    */

    // Special Ability Accessors
    bool isHidden() const {
        return isHidden_;
    }

    int getShellCount() const {
        return shells_;
    }

    int getTrackersLeft() const {
        return trackersLeft_;
    }

    bool isShielded() const {
        return shieldActive_;
    }

    int getShieldCharges() const {
        return shieldCharges_;
    }
};

// Initialise static member
int GenericRobot::robotAutoIncrementInt_ = 0;

#endif