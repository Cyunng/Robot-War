#include "Robot.h"
#include "Battlefield.h"

#include <iostream>
#include <vector>

Robot::Robot(string id, int x, int y) : id_(id), robotPositionX(x), robotPositionY(y) {
    availableUpgrades_ = {"HideBot", "JumpBot", "TeleportBot", "LongShotBot", "SemiAutoBot", "ThirtyShotBot", "ShieldBot", "ScoutBot", "TrackBot", "RadarBot"};
    }

// Getters (Acessors)
int Robot::x() const {
    return robotPositionX;
}

int Robot::y() const {
    return robotPositionY;
}

string Robot::id() const {
    return id_;
}

string Robot::robotType() const {
    return robotType_;
}

string Robot::robotName() const {
    return robotName_;
}

int Robot::numOfLives() const {
    return numOfLives_;
}

int Robot::numOfKills() const {
    return numOfKills_;
}

const vector<string>& Robot::getUsedUpgrades() const {
    return usedUpgrades_;
}

// Setters (Mutators)
void Robot::setX(int x) {
    robotPositionX = x;
}

void Robot::setY(int y) {
    robotPositionY = y;
}

void Robot::setId(string id) {
    id_ = id;
}

void Robot::setRobotType(string robotType) {
    robotType_ = robotType;
}

void Robot::setRobotName(string robotName) {
    robotName_ = robotName;
}

void Robot::setNumOfLives(int numOfLives) {
    numOfLives_ = numOfLives;
}

void Robot::setNumOfKills(int numOfKills) {
    numOfKills_ = numOfKills;
}

//Game mechanics
void Robot::reduceLife() {
    if (numOfLives_ > 0) {
        numOfLives_--;
    }
}

void Robot::incrementKills() {
    numOfKills_++;
}

bool Robot::isAlive() const {
    return numOfLives_ > 0;
}

//Upgrade System
bool Robot::canUpgrade() const {
    return !availableUpgrades_.empty() && usedUpgrades_.size() < 3;
}

string Robot::getNextUpgrade() {
    if (availableUpgrades_.empty()) {
        return "";
    }

    // Randomize avaliable upgrades
    int random = rand() % availableUpgrades_.size();
    string upgrade = availableUpgrades_[random];

    // Remove used upgrades from avaliable and add to used
    availableUpgrades_.erase(availableUpgrades_.begin() + random);
    usedUpgrades_.push_back(upgrade);

    return upgrade;
}

// Overloading the << operator for Robot class
ostream& operator<<(ostream &out, const Robot& r) {
    out << r.id_ << "_" << r.robotName_ << " at (" << r.robotPositionX << ", " << r.robotPositionY << ")" << endl;
    out << "- Lives: " << r.numOfLives_ << ", Kills: " << r.numOfKills_ << endl;

    return out;
}