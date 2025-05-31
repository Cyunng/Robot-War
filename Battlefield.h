#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include "Robot.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>

using namespace std;

class Battlefield {
private:
    // Game Dimensions
    int battlefieldCols_ = -1;
    int battlefieldRows_ = -1;

    // Turn Management
    int currentTurn_ = 0; // Current turn number
    int maxTurns_ = -1; // Total simulation turns 

    // Robot Management
    int robotCount_ = -1; // Number of robots

    vector<Robot*> robots_; // Active robots
    vector<Robot*> stillAlive; // Robots that still alive
    queue<Robot*> destroyedRobots_; // Robots to respawn
    queue<Robot*> waitingRobots_; // Robots waiting to enter

    // 2D vector representing the battlefield
    vector<vector<string>> battlefield_;

    // Process destroyed and waiting robots queues
    void processRobotQueues();

public:
    // Constructor & Destructor
    Battlefield() {}

    ~Battlefield() {
    // Clean up all robot objects
    for (Robot* robot : robots_) {
        delete robot;
    }
    while (!destroyedRobots_.empty()) {
        delete destroyedRobots_.front();
        destroyedRobots_.pop();
    }
    while (!waitingRobots_.empty()) {
        delete waitingRobots_.front();
        waitingRobots_.pop();
    }
}

    // Getter Functions / Accessors
    int getBattlefieldColumns() const;

    int getBattlefieldRows() const;

    int getCurrentTurn() const;

    int getTotalTurns() const;

    int getRobotCount() const;
    
    // Read input file to initialize battlefield and robots
    bool readFile(const string& filename);
    
    // Place robots on the battlefield
    void placeRobots();

    // Display the battlefield in the screen
    void displayBattlefield() const;

    // Run one turn of the simulation
    void runTurn();

    // Helper methods
    bool isPositionEmpty(int robotPositionX, int robotPositionY) const;

    bool hasRobotAt(int robotPositionX, int robotPositionY) const;

    Robot* getRobotAt(int robotPositionX, int robotPositionY) const;

    Robot* getRandomEnemy(Robot* self) const;
};

#endif
