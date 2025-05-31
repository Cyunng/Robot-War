#include "RobotType.h"

#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

/////// Moving Upgrade ++ ///////

/////// HideBot ///////
HideBot::HideBot(string id = "", int x = -1, int y = -1) : GenericRobot(id, x, y) {
    setRobotType("HideBot");
    cout << id << " upgraded to HideBot!" << endl;
}

void HideBot::actionThink(Battlefield* battlefield) {
    if (hideUsesLeft_ > 0 && !isHidden_ && rand() % 2 == 0) { // 50% chance to hide
        isHidden_ = true;
        hideTurnsLeft_ = 3;
        hideUsesLeft_--;
        cout << id() << " is now hidden for 3 turns! (" << hideUsesLeft_ << " charges left)" << endl;
    }
}

void HideBot::actionMove(Battlefield* battlefield) {
    if (isHidden_) {
        hideTurnsLeft_--;
        if (hideTurnsLeft_ <= 0) {
            isHidden_ = false;
            cout << id() << " is no longer hidden!" << endl;
        }
    }
    GenericRobot::actionMove(battlefield);
}

Robot* HideBot::upgrade() {
    return new HideBot(id(), x(), y());
}

//////// JumpBot ///////
JumpBot::JumpBot(string id = "", int x = -1, int y = -1) : GenericRobot(id, x, y) {
    setRobotType("JumpBot");
    cout << id << " upgraded to JumpBot!" << endl;
}

void JumpBot::actionMove(Battlefield* battlefield) {
    if (jumpCount_ > 0) {
        int newX = rand() % battlefield->getBattlefieldColumns();
        int newY = rand() % battlefield->getBattlefieldRows();
        setLocation(newX, newY);
        jumpCount_--;
        cout << id() << " jumped to (" << newX << ", " << newY << ") (" << jumpCount_ << " jumps left)" << endl;
    }
    else {
        GenericRobot::actionMove(battlefield);
    }
}

Robot* JumpBot::upgrade() {
    return new JumpBot(id(), x(), y());
}

/////// TeleportBot //////
TeleportBot::TeleportBot(string id = "", int x = -1, int y = -1) : GenericRobot(id, x, y) {
    setRobotType("TeleportBot");
    cout << id << " upgraded to TeleportBot!" << endl;
}

void TeleportBot::actionMove(Battlefield* battlefield) {
    if (teleportCharges_ > 0) {
        // Find empty position to teleport to
        int newX, newY;
        int attempts = 0;
        do {
            newX = rand() % battlefield->getBattlefieldColumns();
            newY = rand() % battlefield->getBattlefieldRows();
            attempts++;
        } while (attempts < 100 && !battlefield->isPositionEmpty(newX, newY));
        
        if (attempts < 100) {
            setLocation(newX, newY);
            teleportCharges_--;
            cout << id() << " teleported to (" << newX << ", " << newY << ") (" << teleportCharges_ << " teleports left)" << endl;
        }
    }
    else {
        GenericRobot::actionMove(battlefield);
    }
}

Robot* TeleportBot::upgrade() {
    return new TeleportBot(id(), x(), y());
}

/////// Shooting Upgrade ++ ///////

/////// LongShotBot ///////
LongShotBot::LongShotBot(string id = "", int x = -1, int y = -1) : GenericRobot(id, x, y) {
    setRobotType("LongShotBot");
    cout << id << " upgraded to LongShotBot!" << endl;
}

void LongShotBot::actionFire(Battlefield* battlefield) {
    if (getShellCount() > 0) {
        // Find target within range
        for (int dx = -fireRange_; dx <= fireRange_; dx++) {

            for (int dy = -fireRange_; dy <= fireRange_; dy++) {

                if (abs(dx) + abs(dy) <= fireRange_ && (dx != 0 || dy != 0)) {
                    int targetX = x() + dx;
                    int targetY = y() + dy;
                    
                    if (battlefield->hasRobotAt(targetX, targetY)) {
                        cout << id() << " fires long shot at (" << targetX << ", " << targetY << ")!" << endl;
                        shells_--;
                        return;
                    }
                }
            }
        }
        cout << id() << " could not find target in range" << endl;
    }
    else {
        cout << id() << " has no ammo left and self-destructs!" << endl;
        reduceLife(); // Kill the robot
    }
}

Robot* LongShotBot::upgrade() {
    return new LongShotBot(id(), x(), y());
}

/////// SemiAutoBot ///////
SemiAutoBot::SemiAutoBot(string id = "", int x = -1, int y = -1) : GenericRobot(id, x, y) {
    setRobotType("SemiAutoBot");
    cout << id << " upgraded to SemiAutoBot!" << endl;
}

void SemiAutoBot::actionFire(Battlefield* battlefield) {
    if (getShellCount() >= burstCount_) {
        int targetX = x() + (rand() % 3) - 1; // -1, 0, or 1
        int targetY = y() + (rand() % 3) - 1;
        
        if (battlefield->hasRobotAt(targetX, targetY)) {
            cout << id() << " fires 3-shot burst at (" << targetX << ", " << targetY << ")!" << endl;
            shells_ -= burstCount_;
        }
        else {
            cout << id() << " fires burst but misses!" << endl;
            shells_ -= burstCount_;
        }
    }
    else {
        GenericRobot::actionFire(battlefield);
    }
}

Robot* SemiAutoBot::upgrade() {
    return new SemiAutoBot(id(), x(), y());
}

/////// ThirtyShortBot///////
ThirtyShotBot::ThirtyShotBot(string id = "", int x = -1, int y = -1) : GenericRobot(id, x, y) {
    setRobotType("ThirtyShotBot");
    shells_ = 30; // Reset to 30 shells
    cout << id << " upgraded to ThirtyShotBot with 30 shells!" << endl;
}

Robot* ThirtyShotBot::upgrade() {
    return new ThirtyShotBot(id(), x(), y());
}

/////// ShieldBot ///////
ShieldBot::ShieldBot(string id = "", int x = -1, int y = -1) : GenericRobot(id, x, y) {
    setRobotType("ShieldBot");
    cout << id << " upgraded to ShieldRobot!" << endl;
}

void ShieldBot::actionThink(Battlefield* battlefield) {
    if (shieldHealth_ > 0 && !shieldActive_) {
        shieldActive_ = true;
        cout << id() << " activated energy shield (" << shieldHealth_ << " charges left)" << endl;
    }
}

void ShieldBot::takeDamage() {
    if (shieldActive_) {
        shieldHealth_--;
        shieldActive_ = false;
        cout << id() << "'s shield blocked the attack! (" << shieldHealth_ << " charges remain)" << endl;
    }
    else {
        GenericRobot::reduceLife(); // Normal damage
    }
}

Robot* ShieldBot::upgrade() {
    return new ShieldBot(id(), x(), y());
}

/////// Seeing Upgrade++ ///////

/////// ScoutBot ///////
ScoutBot::ScoutBot(string id = "", int x = -1, int y = -1) : GenericRobot(id, x, y) {
    setRobotType("ScoutBot");
    cout << id << " upgraded to ScoutBot!" << endl;
}

void ScoutBot::actionLook(Battlefield* battlefield) {
    if (scoutCharges_ > 0) {
        cout << id() << " is scouting the entire battlefield!" << endl;
        battlefield->displayBattlefield();
        scoutCharges_--;
    }
    else {
        GenericRobot::actionLook(battlefield);
    }
}

Robot* ScoutBot::upgrade() {
    return new ScoutBot(id(), x(), y());
}

/////// TrackBot ///////
TrackBot::TrackBot(string id = "", int x = -1, int y = -1) : GenericRobot(id, x, y) {
    setRobotType("TrackBot");
    cout << id << " upgraded to TrackBot!" << endl;
}

void TrackBot::actionLook(Battlefield* battlefield) {
    if (trackersLeft_ > 0) {
        // Find a robot to track
        Robot* target = battlefield->getRandomEnemy(this);
        if (target) {
            trackedRobots_[target->id()] = make_pair(target->x(), target->y());
            trackersLeft_--;
            cout << id() << " is now tracking " << target->id() << " (" << trackersLeft_ << " trackers left)" << endl;
        }
    }
    
    // Display tracked robots
    if (!trackedRobots_.empty()) {
        cout << "Tracked robots:" << endl;

        for (auto& entry : trackedRobots_) {
            cout << entry.first << " at (" << entry.second.first << ", " << entry.second.second << ")" << endl;
        }
    }
    else {
        GenericRobot::actionLook(battlefield);
    }
}

Robot* TrackBot::upgrade() {
    return new TrackBot(id(), x(), y());
}

/////// RadarBot ///////
RadarBot::RadarBot(string id = "", int x = -1, int y = -1) : GenericRobot(id, x, y) {
    setRobotType("RdarBot");
    cout << id << " upgraded to RadarBot!" << endl;
}

void RadarBot::actionLook(Battlefield* battlefield) {
    if (radarCharges_ > 0) {
        cout << id() << " activates radar! (range " << radarRange_ << ")" << endl;
        
        // Reveal robots in radar range
        for (int dx = -radarRange_; dx <= radarRange_; dx++) {

            for (int dy = -radarRange_; dy <= radarRange_; dy++) {

                if (dx != 0 || dy != 0) { // Don't check current position
                    int checkX = x() + dx;
                    int checkY = y() + dy;
                    
                    if (battlefield-> hasRobotAt(checkX, checkY)) {
                        Robot* spotted = battlefield->getRobotAt(checkX, checkY);
                        cout << " - Spotted " << spotted->id() << " at (" << checkX << "," << checkY << ")" << endl;
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
    return new RadarBot(id(), x(), y());
}