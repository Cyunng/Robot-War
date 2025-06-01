#include "RobotType.h"

#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

/////// Moving Upgrade ++ ///////

/////// HideBot ///////
HideBot::HideBot(string id, int x, int y) : GenericRobot(id, x, y) {
    setRobotType("HideBot");
}

void HideBot::actionThink(Battlefield* battlefield) {
    if (hideCharges_ > 0 && !isHidden()) {
        setHidden(true, 3);
        hideCharges_--;
        cout << id() << " is now hidden for 3 turns! (" << hideCharges_ << " charges left)" << endl;
        battlefield->log(id() + " is now hidden for 3 turns! (" + to_string(hideCharges_) + " charges left)");
    }
}

void HideBot::actionMove(Battlefield* battlefield) {
    decrementHideTurns();
    GenericRobot::actionMove(battlefield);
}

Robot* HideBot::upgrade() {
    return nullptr;
}

//////// JumpBot ///////
JumpBot::JumpBot(string id, int x, int y) : GenericRobot(id, x, y) {
    setRobotType("JumpBot");
}

void JumpBot::actionMove(Battlefield* battlefield) {
    if (jumpCharges_ > 0) {
        int newX, newY;
        do {
            newX = rand() % battlefield->getBattlefieldColumns();
            newY = rand() % battlefield->getBattlefieldRows();
        } while (!battlefield->isPositionEmpty(newX, newY));

        setLocation(newX, newY);
        jumpCharges_--;
        cout << id() << " jumped to (" << newX << ", " << newY << ") (" << jumpCharges_ << " jumps left)" << endl;
        battlefield->log(id() + " jumped to (" + to_string(newX) + ", " + to_string(newY) + ") (" + to_string(jumpCharges_) + " jumps left)");
    }
    else {
        GenericRobot::actionMove(battlefield);
    }
}

Robot* JumpBot::upgrade() {
    return nullptr;
}

/////// TeleportBot //////
TeleportBot::TeleportBot(string id, int x, int y) : GenericRobot(id, x, y) {
    setRobotType("TeleportBot");
}

void TeleportBot::actionMove(Battlefield* battlefield) {
    if (teleportCharges_ > 0) {
        // Find empty position to teleport to
        int newX, newY;

        do {
            newX = rand() % battlefield->getBattlefieldColumns();
            newY = rand() % battlefield->getBattlefieldRows();
        } while (!battlefield->isPositionEmpty(newX, newY));
        
        setLocation(newX, newY);
        teleportCharges_--;
        cout << id() << " teleported to (" << newX << ", " << newY << ") (" << teleportCharges_ << " teleports left)" << endl;
        battlefield->log(id() + " teleported to (" + to_string(newX) + ", " + to_string(newY) + ") (" + to_string(teleportCharges_) + " teleports left)");
    }
    else {
        GenericRobot::actionMove(battlefield);
    }
}

Robot* TeleportBot::upgrade() {
    return nullptr;
}

/////// Shooting Upgrade ++ ///////

/////// LongShotBot ///////
LongShotBot::LongShotBot(string id, int x, int y) : GenericRobot(id, x, y) {
    setRobotType("LongShotBot");
}

void LongShotBot::actionFire(Battlefield* battlefield) {

    // Find target within range
    for (int dx = -fireRange_; dx <= fireRange_; dx++) {

        for (int dy = -fireRange_; dy <= fireRange_; dy++) {

            if (abs(dx) + abs(dy) <= fireRange_ && (dx != 0 || dy != 0)) {
                int targetX = x() + dx;
                int targetY = y() + dy;
                
                if (battlefield->hasRobotAt(targetX, targetY)) {
                    cout << id() << " fires long shot at (" << targetX << ", " << targetY << ")!" << endl;
                    battlefield->log(id() + " fires long shot at (" + to_string(targetX) + ", " + to_string(targetY) + ")!");

                    setShells(getShells() - 1);
                    return;
                }
            }
        }
    }
    cout << id() << " could not find target in range" << endl;
    battlefield->log(id() + " could not find target in range");

}

Robot* LongShotBot::upgrade() {
    return nullptr;
}

/////// SemiAutoBot ///////
SemiAutoBot::SemiAutoBot(string id, int x, int y) : GenericRobot(id, x, y) {
    setRobotType("SemiAutoBot");
}

void SemiAutoBot::actionFire(Battlefield* battlefield) {
    if (getShells() >= burstSize_) {
        int targetX = x() + (rand() % 3) - 1; // -1, 0, or 1
        int targetY = y() + (rand() % 3) - 1;
        
        if (battlefield->hasRobotAt(targetX, targetY)) {
            cout << id() << " fires 3-shot burst at (" << targetX << ", " << targetY << ")!" << endl;
            battlefield->log(id() + " fires 3-shot burst at (" + to_string(targetX) + ", " + to_string(targetY) + ")!");

            shells_ -= burstSize_;
        }
        else {
            cout << id() << " fires burst but misses!" << endl;
            battlefield->log(id() + " fires burst but misses!");
            shells_ -= burstSize_;
        }
    }
    else {
        GenericRobot::actionFire(battlefield);
    }
}

Robot* SemiAutoBot::upgrade() {
    return nullptr;
}

/////// ThirtyShotBot///////
ThirtyShotBot::ThirtyShotBot(string id, int x, int y) : GenericRobot(id, x, y) {
    setRobotType("ThirtyShotBot");
    setShells(30); // Reset to 30 shells
}

Robot* ThirtyShotBot::upgrade() {
    return nullptr;
}

/////// ShieldBot ///////
ShieldBot::ShieldBot(string id, int x, int y) : GenericRobot(id, x, y) {
    setRobotType("ShieldBot");
}

void ShieldBot::actionThink(Battlefield* battlefield) {
    if (shieldCharges_ > 0 && !shieldActive_) {
        shieldActive_ = true;
        shieldCharges_--;
        cout << id() << " activated energy shield (" << shieldCharges_ << " charges left)" << endl;
        battlefield->log(id() + " activated energy shield (" + to_string(shieldCharges_) + " charges left)");
    }
}

void ShieldBot::reduceLife(Battlefield* battlefield) {
    if (shieldActive_) {
        shieldActive_ = false;
        cout << id() << "'s shield blocked the attack! (" << shieldCharges_ << " charges remain)" << endl;
        battlefield->log(id() + "'s shield blocked the attack! (" + to_string(shieldCharges_) + " charges remain)");
    }
    else {
        GenericRobot::reduceLife(); // Normal damage
    }
}

Robot* ShieldBot::upgrade() {
    return nullptr;
}

/////// Seeing Upgrade++ ///////

/////// ScoutBot ///////
ScoutBot::ScoutBot(string id, int x, int y) : GenericRobot(id, x, y) {
    setRobotType("ScoutBot");
}

void ScoutBot::actionLook(Battlefield* battlefield) {
    if (scoutCharges_ > 0) {
        cout << id() << " is scouting the entire battlefield!" << endl;
        battlefield->log(id() + " is scouting the entire battlefield!");
        battlefield->displayBattlefield();
        scoutCharges_--;
    }
    else {
        GenericRobot::actionLook(battlefield);
    }
}

Robot* ScoutBot::upgrade() {
    return nullptr;
}

/////// TrackBot ///////
TrackBot::TrackBot(string id, int x, int y) : GenericRobot(id, x, y) {
    setRobotType("TrackBot");
}

void TrackBot::actionLook(Battlefield* battlefield) {
    if (trackersLeft_ > 0) {
        // Find a robot to track
        Robot* target = battlefield->getRandomEnemy(this);
        if (target) {
            trackedRobots_[target->id()] = make_pair(target->x(), target->y());
            trackersLeft_--;
            cout << id() << " is now tracking " << target->id() << " (" << trackersLeft_ << " trackers left)" << endl;
            battlefield->log(id() + " is now tracking " + target->id() + " (" + to_string(trackersLeft_) + " trackers left)");
        }
    }
    
    // Display tracked robots
    if (!trackedRobots_.empty()) {
        cout << "Tracked robots:" << endl;
        battlefield->log("Tracked robots:");

        for (auto& entry : trackedRobots_) {
            cout << entry.first << " at (" << entry.second.first << ", " << entry.second.second << ")" << endl;
            battlefield->log(entry.first + " at (" + to_string(entry.second.first) + ", " + to_string(entry.second.second) + ")"); 
        }
    }
    else {
        GenericRobot::actionLook(battlefield);
    }
}

Robot* TrackBot::upgrade() {
    return nullptr;
}

/////// RadarBot ///////
RadarBot::RadarBot(string id, int x, int y) : GenericRobot(id, x, y) {
    setRobotType("RadarBot");
}

void RadarBot::actionLook(Battlefield* battlefield) {
    if (radarCharges_ > 0) {
        cout << id() << " activates radar! (range " << radarRange_ << ")" << endl;
        battlefield->log(id() + " activates radar! (range " + to_string(radarRange_) + ")");
        
        // Reveal robots in radar range
        for (int dx = -radarRange_; dx <= radarRange_; dx++) {

            for (int dy = -radarRange_; dy <= radarRange_; dy++) {

                if (dx != 0 || dy != 0) { // Don't check current position
                    int checkX = x() + dx;
                    int checkY = y() + dy;
                    
                    if (battlefield-> hasRobotAt(checkX, checkY)) {
                        Robot* spotted = battlefield->getRobotAt(checkX, checkY);
                        cout << " - Spotted " << spotted->id() << " at (" << checkX << "," << checkY << ")" << endl;
                        battlefield->log(" - Spotted " + spotted->id() + " at (" + to_string(checkX) + "," + to_string(checkY) + ")");
                    }
                }
            }
        }
        radarCharges_--;
    }
    else {
        GenericRobot::actionLook(battlefield);
    }
}

Robot* RadarBot::upgrade() {
    return nullptr;
}