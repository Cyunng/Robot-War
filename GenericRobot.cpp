#include "GenericRobot.h"
#include "RobotType.h"

#include <iostream>
#include <vector>
#include <map>

using namespace std;

// Initialize static member
int GenericRobot::robotAutoIncrementInt_ = 0;

GenericRobot::GenericRobot(string id, int x, int y) : Robot(id, x, y) {
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
    battlefield->log(id_ + " is thinking...");
}

void GenericRobot::actionLook(Battlefield* battlefield) {
    cout << id_ << " is scanning the battlefield at range of " << lookRange_ << "..." << endl;
   battlefield->log(id_ + " is scanning the battlefield at range of " + to_string(lookRange_) + "...");

    for (int dx = -1; dx <= 1; dx++) {

        for (int dy = -1; dy <= 1; dy++) {

            if (dx == 0 && dy == 0) {
                continue; // Skip self
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
    if (shells_ <= 0) {
        string msg = id_ + " has no ammo left and self-destructs!";
        cout << msg << endl;
        
        if (battlefield->isLogging()) {
            battlefield->log(msg);
        }
        reduceLife(); // Kill the robot
        return;
    }

    // Only fire at 8 neigboring locations
    vector<pair<int, int>> targets;

    for (int dx = -1; dx <= 1; dx++) {

        for (int dy = -1; dy <= 1; dy++) {
            
            if (dx == 0 && dy == 0) {
                continue; // Do not fire at self
            }

            int targetX = robotPositionX + dx;
            int targetY = robotPositionY + dy;

            if (battlefield->hasRobotAt(targetX, targetY)) {
                targets.emplace_back(targetX, targetY);
            }
        }
    }

    if (!targets.empty()) {
        const auto& target = targets[rand() % targets.size()];

        int targetX = target.first;
        int targetY = target.second;

        Robot* targetRobot = battlefield->getRobotAt(targetX, targetY);
        cout << id_ << " fires at " << targetRobot->id();

        // Check if target is hidden
        if (targetRobot->isHidden()) {
            cout << " but it is hidden!" << endl;
            shells_--;
            return;
        }

        cout << "!" << endl;
        shells_--;

        if (rand() % 100 < 70) { // 70% hit chance
            targetRobot->reduceLife();
            cout << "- Hit! " << targetRobot->id() << " now has " << targetRobot->numOfLives() << " lives left" << endl;

            if (!targetRobot->isAlive()) {
                numOfKills_++;
                cout << "- " << targetRobot->id() << " destroyed!" << endl;

                //Check for upgrade after kill
                if (canUpgrade()) {
                    Robot* upgraded = upgrade();

                    if (upgraded) {
                        battlefield->replaceRobot(this, upgraded);
                        return; // Skip move after upgrade
                    }
                }
            } 
        }
        else {
            cout << "- Missed!" << endl;
        }
    }
    else {
        cout << id_ << " could not find a target to fire at" << endl;
    }
}

void GenericRobot::actionMove(Battlefield* battlefield) {
    vector<pair<int, int>> possibleMoves;

    for (int dx = -1; dx <= 1; dx++) {

        for (int dy = -1; dy <=  1; dy++) {
            int newX = robotPositionX + dx;
            int newY = robotPositionY + dy;

            if (battlefield->isPositionEmpty(newX, newY)) {
                possibleMoves.emplace_back(newX, newY);
            }
        }
    }

    if (!possibleMoves.empty()) {
        const auto& move = possibleMoves[rand() % possibleMoves.size()];

        int newX = move.first;
        int newY = move.second;

        setLocation(newX, newY);
        cout << id_ << " moves to (" << newX << "," << newY << ")" << endl;
    }
    else {
        cout << id_ << " could not find a valid move" << endl;
    }
}

void GenericRobot::actions(Battlefield* battlefield) {
    if (!isAlive()) {
        return;
    }

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

    // Check for upgrades after actions
    if (numOfKills_ > usedUpgrades_.size() && canUpgrade()) {
        Robot* upgraded = upgrade();
        if (upgraded) {
            battlefield->replaceRobot(this, upgraded);
        }
    }
}

// Upgrade System
Robot* GenericRobot::upgrade() {
    if (!canUpgrade() || numOfKills_ <= usedUpgrades_.size()) {
        return nullptr;
    }

    string upgradeType = getNextUpgrade();

    if (upgradeType.empty()) {
        return nullptr;
    }

    cout << id_ << " can upgrade! Available options: ";
    for (const auto& upgrade : availableUpgrades_) {
        cout << upgrade << " ";
    }
    cout << endl;

    upgradeType = availableUpgrades_[0];
    availableUpgrades_.erase(availableUpgrades_.begin());
    usedUpgrades_.push_back(upgradeType);

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
        upgraded->setShells(shells_);
        cout << id_ << " upgraded to " << upgradeType << "!" << endl;
    }

    return upgraded;
}
