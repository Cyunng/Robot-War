#include "Battlefield.h"
#include "GenericRobot.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>

using namespace std;

void Battlefield::processRobotQueues() {
    // Process destroyed robots respawn if they have lives left
    while (!destroyedRobots_.empty()) {
        Robot* robot = destroyedRobots_.front();
        destroyedRobots_.pop();

        if (robot->isAlive()) {
            // Respawn at random locataion
            int newX, newY;
            do {
                newX = rand() % battlefieldCols_;
                newY = rand() % battlefieldRows_;
            } while (!isPositionEmpty(newX, newY));
        }    
        else {
            delete robot; // Clean up destroyed robots
        }
    }
    // Process waiting robots to add back to active list
    while (!waitingRobots_.empty() && waitingRobots_.front()->isAlive()) {
        Robot* robot = waitingRobots_.front();
        waitingRobots_.pop();
        robots_.push_back(robot);
    }
}

// Getter Functions / Accessors
int Battlefield::getBattlefieldColumns() const {
    return battlefieldCols_;
}

int Battlefield::getBattlefieldRows() const {
    return battlefieldRows_;
}

int Battlefield::getCurrentTurn() const {
    return currentTurn_;
}

int Battlefield::getTotalTurns() const {
    return maxTurns_;
}

int Battlefield::getRobotCount() const {
    return robots_.size();
}

// Read input file to initialize battlefield and robots
bool Battlefield::readFile(const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return false;
    }

    string line;
    
    while (getline(file, line)) {
        //Parse battlefield dimensions
        if (line.find("M by N:") != string::npos) {
            istringstream iss(line.substr(7));
            iss >> battlefieldCols_ >> battlefieldRows_;
            battlefield_.resize(battlefieldRows_, vector<string>(battlefieldCols_, "."));
        }
        // Parse total turns
        else if (line.find("turns:") != string::npos) {
            maxTurns_ = stoi(line.substr(6));
        }
        // Parse robot count
        else if (line.find("robots:") != string::npos) {
            robotCount_ = stoi(line.substr(7));
        }
        // Prase robot specifications
        else if (line.find("GenericRobot") != string::npos) {
            istringstream iss(line);
            string id_, robotType_, robotName_, robotPositionX, robotPositionY;

            iss >> robotType_ >> id_;

            int underscore = id_.find("_");
            if (underscore != string::npos) {
                robotName_ = id_.substr(underscore + 1);
                id_ = id_.substr(0, underscore);
            }

            iss >> robotPositionX >> robotPositionY;

            // Handle random positions
            int x, y;

            if (robotPositionX == "random") {
                x = rand() % battlefieldCols_;
            }
            else {
                x = stoi(robotPositionX);
            }

            if (robotPositionY == "random") {
                y = rand() % battlefieldRows_;
            }
            else {
                y = stoi(robotPositionY);
            }

            Robot* robot = new GenericRobot(id_, x, y);
            robot->setRobotName(robotName_);
            robot->setRobotType(robotType_);
            robots_.push_back(robot);
        }
    }
    return true;
}

// Place robots on the battlefield
void Battlefield::placeRobots() {
    for (int i = 0; i < battlefield_.size(); ++i) {
        for (int j = 0; j < battlefield_[i].size(); ++j) {
            battlefield_[i][j] = "";
        }
    }

    for ( int i = 0; i < robots_.size(); ++i) {
        if (robots_[i]->y() >=0 && robots_[i]->y() < battlefield_.size() && robots_[i]->x() >=0 && robots_[i]->x() < battlefield_[0].size()) {
            battlefield_[robots_[i]->y()][robots_[i]->x()] = robots_[i]->id();
        }
        else {
            cout << "Error message: Invalid location for the robot" << robots_[i]->id() << endl;
            exit(1);
        }
    }
}

// Display the battlefield in the screen
void Battlefield::displayBattlefield() const {
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
void Battlefield::runTurn() {
    if (currentTurn_ >= maxTurns_ || robots_.empty()) {
        return;
    }

    cout << "\n=== Turn " << currentTurn_ + 1 << " ===" << endl;

    stillAlive.clear();

    // Process each robot's actions
    for (Robot* robot : robots_) {
        if (robot->isAlive()) {
            robot->actions(this);
            stillAlive.push_back(robot);
        }
        else {
            destroyedRobots_.push(robot);
        }
    }
    robots_ = stillAlive;

    // Update battlefield state
    placeRobots();
    displayBattlefield();

    // Process destroyed and waiting robots
    processRobotQueues();

    currentTurn_++;
}

// Helper methods
bool Battlefield::isPositionEmpty(int robotPositionX, int robotPositionY) const {
    if (robotPositionX < 0 || robotPositionX >= battlefieldCols_ || robotPositionY < 0 || robotPositionY >= battlefieldRows_) {
        return false;
    }
    return battlefield_[robotPositionY][robotPositionX].empty();
}

bool Battlefield::hasRobotAt(int robotPositionX, int robotPositionY) const {
    if (robotPositionX < 0 || robotPositionX >= battlefieldCols_ || robotPositionY < 0 || robotPositionY >= battlefieldRows_) {
        return false;
    }
    return !battlefield_[robotPositionY][robotPositionX].empty();
}

Robot* Battlefield::getRobotAt(int robotPositionX, int robotPositionY) const {
    if (!hasRobotAt(robotPositionX, robotPositionY)) {
        return nullptr;
    }

    for (Robot* robot : robots_) {
        if (robot->x() == robotPositionX && robot->y() == robotPositionY) {
            return robot;
        }
    }
    return nullptr;
}

Robot* Battlefield::getRandomEnemy(Robot* self) const {
    if (robots_.empty()) {
        return nullptr;
    }

    vector<Robot*> enemyRobots;
    for (Robot* robot : robots_) {
        if (robot != self && robot->isAlive()) {
            enemyRobots.push_back(robot);
        }
    }
    
    if (enemyRobots.empty()) {
        return nullptr;
    }

    return enemyRobots[rand() % enemyRobots.size()];
}