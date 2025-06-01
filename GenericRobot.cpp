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
                battlefield->log("- Spotted robot at (" + to_string(checkX) + "," + to_string(checkY) + ")");
            }
        }
    }
}

void GenericRobot::actionFire(Battlefield* battlefield) {
    if (shells_ <= 0) {
        cout << id_ << " has no ammo left and self-destructs!" << endl;
        battlefield->log(id_ + " has no ammo left and self-destructs!");
        reduceLife();
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
        battlefield->log(id_ + " fires at " + targetRobot->id() + ")");

        // Check if target is hidden
        if (targetRobot->isHidden()) {
            cout << " but it is hidden!" << endl;
            battlefield->log(" but it is hidden!");
            shells_--;
            return;
        }

        cout << "!" << endl;
        battlefield->log("!");
        shells_--;

        if (rand() % 100 < 70) { // 70% hit chance
            targetRobot->reduceLife();
            cout << "- Hit! " << targetRobot->id() << " now has " << targetRobot->numOfLives() << " lives left" << endl;
            battlefield->log("- Hit" + targetRobot->id() + " now has " + to_string(targetRobot->numOfLives()) + " lives left");

            if (!targetRobot->isAlive()) {
                numOfKills_++;
                cout << "- " << targetRobot->id() << " destroyed!" << endl;
                battlefield->log("- " + targetRobot->id() + " destroyed!");

                //Check for upgrade after kill
                if (canUpgrade()) {
                    Robot* upgraded = upgrade(battlefield);

                    if (upgraded) {
                        battlefield->replaceRobot(this, upgraded);
                        return; // Skip move after upgrade
                    }
                }
            } 
        }
        else {
            cout << "- Missed!" << endl;
            battlefield->log("- Missed!");
        }
    }
    else {
        cout << id_ << " could not find a target to fire at" << endl;
        battlefield->log(id_ + " could not find a target to fire at");

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
        battlefield->log(id_ + " moves to (" + to_string(newX) + "," + to_string(newY) + ")");
    }
    else {
        cout << id_ << " could not find a valid move" << endl;
        battlefield->log(id_ + " could not find a valid move");
    }
}

void GenericRobot::actions(Battlefield* battlefield) {
    cout << id_ << ": actions() START" << endl; // DEBUG

    if (!isAlive()) {
        return;
    }

    int randomActionThink = rand() % 2;

    if (randomActionThink == 0) {
        actionThink(battlefield);
        actionLook(battlefield);
        actionFire(battlefield);
        actionMove(battlefield);
    }
    else {
        actionThink(battlefield);
        actionLook(battlefield);
        actionMove(battlefield);
        actionFire(battlefield);
    }

    if (numOfKills_ > usedUpgrades_.size() && canUpgrade()) {
        Robot* upgraded = upgrade(battlefield);
        if (upgraded) {
            battlefield->replaceRobot(this, upgraded);
        }
    }
    cout << id_ << ": lives=" << numOfLives_ << ", shells=" << shells_ << ", alive=" << (isAlive() ? "true" : "false") << endl;

    cout << id_ << ": actions() END" << endl; // DEBUG
}

// Upgrade System
Robot* GenericRobot::upgrade(Battlefield* battlefield) {
    if (!canUpgrade() || numOfKills_ <= usedUpgrades_.size()) {
        return nullptr;
    }

    string upgradeType = getNextUpgrade();

    if (upgradeType.empty()) {
        return nullptr;
    }

    cout << id_ << " can upgrade! Available options: ";
    battlefield->log(id_ + " can upgrade! Available options: ");

    for (const auto& upgrade : availableUpgrades_) {
        cout << upgrade << " ";
        battlefield->log(upgrade + " ");
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
        battlefield->log(id_ + " upgraded to " + upgradeType + "!");
    }

    return upgraded;
}
