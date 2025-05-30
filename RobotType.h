#ifndef ROBOT_TYPE_H
#define ROBOT_TYPE_H
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include "GenericRobot.h"
#include "Battlefield.h"
using namespace std;

/////// Moving Upgrade ++ ///////
/////// HideBot ///////
class HideBot : public GenericRobot{
private:
    int hideUsesLeft_ = 3;
    bool isHidden_ = false;        
    int hideTurnsLeft_ = 0;
public:
    HideBot(string id = "", int x = -1, int y = -1) : GenericRobot(id, x, y) {
        robotType_ = "HideBot";
        cout << id << " Upgraded to HideBot!" << endl;
    }

    void actionThink(Battlefield* battlefield) {
        if (hideUsesLeft_ > 0 && !isHidden_ && rand() % 2 == 0) { // 50% chance to hide
            isHidden_ = true;
            hideTurnsLeft_ = 3;
            hideUsesLeft_--;
            cout << id() << " is now hidden for 3 turns! (" << hideUsesLeft_ << " charges left)" << endl;
        }
    }

    void actionMove(Battlefield* battlefield) {
        if (isHidden_) {
            hideTurnsLeft_--;
            if (hideTurnsLeft_ <= 0) {
                isHidden_ = false;
                cout << id() << " is no longer hidden!" << endl;
            }
        }
        GenericRobot::actionMove(battlefield);
    }

    bool isHidden() const { return isHidden_; }

    Robot* upgrade() {
        return new JumpBot(id(), x(), y());
    }
};

//////// JumpBot ///////
class JumpBot : public GenericRobot{
private:
    int jumpCount_ = 3;
public:
    JumpBot(string id = "", int x = -1, int y = -1) : GenericRobot(id, x, y) {
        robotType_ = "JumpBot";
        cout << id << " Upgraded to JumpBot!" << endl;
    }

    void actionMove(Battlefield* battlefield) {
        if (jumpCount_ > 0) {
            int newX = rand() % battlefield->getBattlefieldColumns();
            int newY = rand() % battlefield->getBattlefieldRows();
            setLocation(newX, newY);
            jumpCount_--;
            cout << id() << " jumped to (" << newX << ", " << newY << ") (" 
                 << jumpCount_ << " jumps left)" << endl;
        } else {
            GenericRobot::actionMove(battlefield);
        }
    }

    Robot* upgrade() {
        return new TeleportBot(id(), x(), y());
    }
};
/////// TeleportBot //////
class TeleportBot : public GenericRobot{
private:
    int teleportCharges_ = 3;
    
public:
    TeleportBot(string id = "", int x = -1, int y = -1) : GenericRobot(id, x, y) {
        robotType_ = "TeleportBot";
        cout << id << " Upgraded to TeleportBot!" << endl;
    }

    void actionMove(Battlefield* battlefield) {
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
                cout << id() << " teleported to (" << newX << ", " << newY << ") (" 
                     << teleportCharges_ << " teleports left)" << endl;
            }
        } else {
            GenericRobot::actionMove(battlefield);
        }
    }
};

/////// Shooting Upgrade ++ ///////
class LongShotBot : public GenericRobot{
private:
    int fireRange_ = 1;
    int shells_ = 10;
public:
    LongShotBot(string id = "", int x = -1, int y = -1) : GenericRobot(id, x, y) {
        robotType_ = "LongShotBot";
        cout << id << " Upgraded to LongShotBot!" << endl;
    }

    void actionFire(Battlefield* battlefield) {
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
            cout << id() << " couldn't find target in range" << endl;
        } else {
            cout << id() << " is out of ammo!" << endl;
        }
    }
};

/////// SemiAutoBot ///////
class SemiAutoBot : public GenericRobot{
    private:
    int burstCount_ = 3;
    int shells_ = 10;
    
public:
    SemiAutoBot(string id = "", int x = -1, int y = -1) : GenericRobot(id, x, y) {
        robotType_ = "SemiAutoBot";
        cout << id << " Upgraded to SemiAutoBot!" << endl;
    }

    void actionFire(Battlefield* battlefield) {
        if (getShellCount() >= burstCount_) {
            int targetX = x() + (rand() % 3) - 1; // -1, 0, or 1
            int targetY = y() + (rand() % 3) - 1;
            
            if (battlefield->hasRobotAt(targetX, targetY)) {
                cout << id() << " fires 3-shot burst at (" << targetX << ", " << targetY << ")!" << endl;
                shells_ -= burstCount_;
            } else {
                cout << id() << " fires burst but misses!" << endl;
                shells_ -= burstCount_;
            }
        } else {
            GenericRobot::actionFire(battlefield);
        }
    }
};
/////// ThirtyShortBot///////
class ThirtyShotBot : public GenericRobot {
private:
    int shells_ = 10;
public:
    ThirtyShotBot(string id = "", int x = -1, int y = -1) : GenericRobot(id, x, y) {
        robotType_ = "ThirtyShotBot";
        shells_ = 30; // Reset to 30 shells
        cout << id << " upgraded to ThirtyShotBot with 30 shells!" << endl;
    }
};
/////// ShieldBot ///////
class ShieldBot : public GenericRobot{
private:
    int shieldHealth_ = 3;
    bool shieldActive_ = false;
    
public:
    ShieldBot(string id = "", int x = -1, int y = -1) : GenericRobot(id, x, y) {
        robotType_ = "ShieldBot";
        cout << id << " Upgraded to ShieldRobot!" << endl;
    }

    void actionThink(Battlefield* battlefield) {
        if (shieldHealth_ > 0 && !shieldActive_) {
            shieldActive_ = true;
            cout << id() << " activated energy shield (" 
                 << shieldHealth_ << " charges left)" << endl;
        }
    }

    void takeDamage() {
        if (shieldActive_) {
            shieldHealth_--;
            shieldActive_ = false;
            cout << id() << "'s shield blocked the attack! (" 
                 << shieldHealth_ << " charges remain)" << endl;
        } else {
            GenericRobot::takeDamage(); // Normal damage
        }
    }

    // Final upgrade - no further upgrades
    Robot* upgrade() { 
        cout << id() << " has reached maximum upgrade level!" << endl;
        return nullptr; 
    }
};

/////// Seeing Upgrade++ ///////
/////// ScoutBot ///////
class ScoutBot : public GenericRobot{
private:
    int scoutCharges_ = 3;
    
public:
    ScoutBot(string id = "", int x = -1, int y = -1) : GenericRobot(id, x, y) {
        robotType_ = "ScoutBot";
        cout << id << " Upgraded to ScoutBot!" << endl;
    }

    void actionLook(Battlefield* battlefield) {
        if (scoutCharges_ > 0) {
            cout << id() << " is scouting the entire battlefield!" << endl;
            battlefield->displayBattlefield();
            scoutCharges_--;
        } else {
            GenericRobot::actionLook(battlefield);
        }
    }
};
/////// TrackBot ///////
class TrackBot : public GenericRobot{
private:
    map<string, pair<int, int>> trackedRobots_;
    int trackersLeft_ = 3;
    
public:
    TrackBot(string id = "", int x = -1, int y = -1) : GenericRobot(id, x, y) {
        robotType_ = "TrackBot";
        cout << id << " Upgraded to TrackBot!" << endl;
    }

    void actionLook(Battlefield* battlefield) {
        if (trackersLeft_ > 0) {
            // Find a robot to track
            Robot* target = battlefield->getRandomEnemy(this);
            if (target) {
                trackedRobots_[target->id()] = make_pair(target->x(), target->y());
                trackersLeft_--;
                cout << id() << " is now tracking " << target->id() << " (" 
                     << trackersLeft_ << " trackers left)" << endl;
            }
        }
        
        // Display tracked robots
        if (!trackedRobots_.empty()) {
            cout << "Tracked robots:" << endl;
            for (auto& entry : trackedRobots_) {
                cout << entry.first << " at (" << entry.second.first 
                     << ", " << entry.second.second << ")" << endl;
            }
        } else {
            GenericRobot::actionLook(battlefield);
        }
    }
};
/////// RadarBot ///////
class RadarBot : public GenericRobot{
private:
    int radarRange_ = 5;
    int radarCharges_ = 3;
    
public:
    RadarBot(string id = "", int x = -1, int y = -1) : GenericRobot(id, x, y) {
        setRobotType("RadarBot");
        cout << id << " upgraded to RadarBot!" << endl;
    }

    void actionLook(Battlefield* battlefield) override {
        if (radarCharges_ > 0) {
            cout << id() << " activates radar (range " << radarRange_ << ")!" << endl;
            
            // Reveal robots in radar range
            for (int dx = -radarRange_; dx <= radarRange_; dx++) {
                for (int dy = -radarRange_; dy <= radarRange_; dy++) {
                    if (dx != 0 || dy != 0) { // Don't check current position
                        int checkX = x() + dx;
                        int checkY = y() + dy;
                        
                        if (battlefield->hasRobotAt(checkX, checkY)) {
                            Robot* spotted = battlefield->getRobotAt(checkX, checkY);
                            cout << " - Spotted " << spotted->id() << " at (" 
                                 << checkX << "," << checkY << ")" << endl;
                        }
                    }
                }
            }
            radarCharges_--;
        } else {
            GenericRobot::actionLook(battlefield);
        }
    }

    Robot* upgrade() override {
        // RadarBot can upgrade to ShieldRobot
        return nullptr;
    }

};





#endif