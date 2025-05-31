#include "Robot.h"
#include "Battlefield.h"

#include <iostream>
#include <vector>

Robot::Robot(string id, int x, int y) : id_(id), robotPositionX(x), robotPositionY(y) {
    availableUpgrades_ = {"HideBot", "JumpBot", "TeleportBot", "LongShotBot", "SemiAutoBot", "ThirtyShotBot", "ShieldBot", "ScoutBot", "TrackBot", "RadarBot"};
    }

string Robot::getNextUpgrade() {
    if (availableUpgrades_.empty()) {
        return "";
    }

    // Get first available upgrade
    string upgrade = availableUpgrades_.back();
    availableUpgrades_.pop_back();
    usedUpgrades_.push_back(upgrade);

    return upgrade;
}

// Overloading the << operator for Robot class
ostream& operator<<(ostream &out, const Robot& r) {
    out << r.id_ << "_" << r.robotName_ << " at (" << r.robotPositionX << ", " << r.robotPositionY << ")" << endl;
    out << "- Lives: " << r.numOfLives_ << ", Kills: " << r.numOfKills_ << ", Shells: " << r.shells_ << endl;

    return out;
}