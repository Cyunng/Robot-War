#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include "Robot.h"
#include "GenericRobot.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <fstream>

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
    queue<Robot*> destroyedRobots_; // Robots to respawn
    queue<Robot*> waitingRobots_; // Robots waiting to enter

    // 2D vector representing the battlefield
    vector<vector<string>> battlefield_;

    // Process destroyed and waiting robots queues
    void processRobotQueues() {
        // Process destroyed robots respawn if they have lives left
        while (!destroyedRobots_.empty()) {
            Robot* robot = destroyedRobots_.front();
            destroyedRobots_.pop();

            if (robot->isAlive()) {
                // Respawn at random locataion
                robot->setLocation(rand() % battlefieldCols_, rand() % battlefieldRows_);
                waitingRobots_.push(robot);
            }
            else {
                delete robot; // Clean up destroyed robots
                robotCount_--;
            }
        }
        // Process waiting robots to add back to active list
        while (!waitingRobots_.empty() && waitingRobots_.front()->isAlive()) {
            robots_.push_back(waitingRobots_.front());
            waitingRobots_.pop();
        }
    }

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
    int getBattlefieldColumns() const {
        return battlefieldCols_;
    }

    int getBattlefieldRows() const {
        return battlefieldRows_;
    }

    int getCurrentTurn() const {
        return currentTurn_;
    }

    int getTotalTurns() const {
        return maxTurns_;
    }

    int getRobotCount() const {
        return robotCount_;
    }
    
    // Read input file to initialize battlefield and robots
    bool readFile(const string& filename) {
        ifstream file(filename);

        if (!file.is_open()) {
            cout << "Error opening file: " << filename << endl;
            return false;
        }

        string line;
        bool success = false;
        
        while (getline(file, line)) {
            //Parse battlefield dimensions
            if (line.find("M by N:") != string::npos) {
                istringstream iss(line.substr(7));
                iss >> battlefieldCols_ >> battlefieldRows_;
                battlefield_.resize(battlefieldRows_, vector<string>(battlefieldCols_, "."));
                success = false;
            }
            // Parse total turns
            else if (line.find("turns:") != string::npos) {
                maxTurns_ = stoi(line.substr(6));
                success = false;
            }
            // Parse robot count
            else if (line.find("robots:") != string::npos) {
                robotCount_ = stoi(line.substr(7));
                success = false;
            }
            // Prase robot specifications
            else if (line.find("GenericRobot") != string::npos) {
                istringstream iss(line);
                string id_, robotType_, robotName_;
                int robotPositionX, robotPositionY;

                iss >> robotType_ >> id_;
                int underscore = id_.find("_");
                if (underscore != string::npos) {
                    robotName_ = id_.substr(underscore + 1);
                    id_ = id_.substr(0, underscore);
                }

                iss >> robotPositionX >> robotPositionY;

                // Handle random positions
                if (robotPositionX == -1 && robotPositionY == -1) {
                    robotPositionX = rand() % battlefieldCols_;
                    robotPositionY = rand() % battlefieldRows_;
                }

                Robot* robot = new GenericRobot(id_, robotPositionX, robotPositionY);
                robot->setRobotName(robotName_);
                robot->setRobotType(robotType_);
                robots_.push_back(robot);
                success = true;
            }
        }
        return true;
    }
    
    // Place robots on the battlefield
    void placeRobots() {
        for (int i = 0; i < battlefield_.size(); ++i) {
            for (int j = 0; j < battlefield_[i].size(); ++j) {
                battlefield_[i][j] = "";
            }
        }

        for ( int i = 0; i < robots_.size(); ++i) {
            if (robots_[i]->y() < battlefield_.size() && robots_[i]->x() < battlefield_[0].size()) {
                battlefield_[robots_[i]->y()][robots_[i]->x()] = robots_[i]->id();
            }
            else {
                cout << "Error message: Invalid location for the robot" << robots_[i]->id() << endl;
                exit(1);
            }
        }
    }

    // Display the battlefield in the screen
    void displayBattlefield() const {
        cout << "Display Battlefield" << endl << "    ";

        // Column headers
        for (int j = 0; j < battlefield_[0].size(); ++j) {
            cout << "  " << right << setfill('0') << setw(2) << j << " ";
        }
        cout << endl;

        // Battlefield grid
        for (int i = 0; i < battlefield_.size(); ++i) {
            // Top border
            cout << "    ";

            for (int j = 0; j < battlefield_[i].size(); ++j) {
                cout << "+----";
            }
            cout << "+" << endl;

            // Row content
            cout << "  " << right << setfill('0') << setw(2) << i;

            for (int j = 0; j < battlefield_[0].size(); ++j) {
                if (battlefield_[i][j] == "") {
                    cout << "|" << "    ";
                }
                else {
                    cout << "|" << left << setfill(' ') << setw(4) << battlefield_[i][j];
                }
            }
            cout << "|" << endl;
        }
        // Bottom border
        cout << "    ";

        for (int j = 0; j < battlefield_[0].size(); ++j) {
            cout << "+----";
        }
        cout << "+" << endl;
    }

    // Run one turn of the simulation
    void runTurn() {
        if (currentTurn_ >= maxTurns_ || robots_.empty() || battlefield_.empty()) {
            return;
        }

        cout << "\n=== Turn " << currentTurn_ + 1 << " ===" << endl;

        // Process each robot's actions
        for (Robot* robot : robots_) {
            if (robot->isAlive()) {
                robot->actions(this);
            }
        }

        // Update battlefield state
        placeRobots();
        displayBattlefield();

        // Process destroyed and waiting robots
        processRobotQueues();

        currentTurn_++;
    }
};

#endif
