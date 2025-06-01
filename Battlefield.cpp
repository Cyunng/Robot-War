#include "Battlefield.h"
#include "GenericRobot.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

Battlefield::Battlefield() {
    srand(time(0));
}

Battlefield::~Battlefield() {
    // Clean up all robot objects
    for (Robot* robot : robots_) {
        delete robot;
    }
    robots_.clear();

    while (!destroyedRobots_.empty()) {
        delete destroyedRobots_.front();
        destroyedRobots_.pop();
    }
    while (!waitingRobots_.empty()) {
        delete waitingRobots_.front();
        waitingRobots_.pop();
    }
    if (logFile_.is_open()) {
        logFile_.close();
    }
}

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

            robot->setLocation(newX, newY);
            waitingRobots_.push(robot);
            cout << robot->id() << " waiting to respawn..." << endl;
            log(robot->id() + " waiting to respawn...");
        }    
        else {
            string robotId = robot->id();
            delete robot; // Clean up destroyed robots
            cout << robotId << " permanently destroyed" << endl;
            log(robotId + " permanently destroyed");
        }
    }
    // Process waiting robots to add back to active list
    if (!waitingRobots_.empty()) {
        Robot* robot = waitingRobots_.front();
        waitingRobots_.pop();
        robots_.push_back(robot);
        cout << robot->id() << " has respawned!" << endl;
        log(robot->id() + " has respawned!");
    }
}

// Read input file to initialize battlefield and robots
bool Battlefield::readFile(const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error opening file: " << filename << endl;
        log("Error opening file: " + filename);
        return false;
    }

    string line;
    
    while (getline(file, line)) {
        //Parse battlefield dimensions
        if (line.find("M by N:") != string::npos) {
            istringstream iss(line.substr(7));
            iss >> battlefieldCols_ >> battlefieldRows_;
            battlefield_.resize(battlefieldRows_, vector<string>(battlefieldCols_, "."));
            cout << "Battlefield dimensens set to: " << battlefieldCols_ << "x" << battlefieldRows_ << endl;
            log("Battlefield dimensens set to: " + to_string(battlefieldCols_) + "x" + to_string(battlefieldRows_));
        }
        // Parse total turns
        else if (line.find("turns:") != string::npos) {
            maxTurns_ = stoi(line.substr(6));
            cout << "Total turns set to: " << maxTurns_ << endl;
            log("Total turns set to: " + to_string(maxTurns_));
        }
        // Parse robot count
        else if (line.find("robots:") != string::npos) {
            robotCount_ = stoi(line.substr(7));
            cout << "Robot count set to: " << robotCount_ << endl;
            log("Robot count set to: " + to_string(robotCount_));
        }
        // Prase robot specifications
        else if (line.find("GenericRobot") != string::npos) {
            istringstream iss(line);
            string id_, robotType_, robotName_, robotPositionX, robotPositionY;

            iss >> robotType_ >> id_ >> robotPositionX >> robotPositionY;

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
            robot->setRobotName(id_.substr(id_.find("_") + 1));
            robots_.push_back(robot);
            cout << "Created robot: " << id_ << " at (" << x << "," << y << ")" << endl;
            log("created robot: " + id_ + " at (" + to_string(x) + "," + to_string(y) + ")");
        }
    }
    placeRobots();
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
            battlefield_[robots_[i]->y()][robots_[i]->x()] = robots_[i]->id().substr(0, 4);
        }
        else {
            cout << "Error message: Invalid location for the robot" << robots_[i]->id() << endl;
            log("Error message: Invalid location for the robot " + robots_[i]->id());
            exit(1);
        }
    }
}

// Display the battlefield in the screen
void Battlefield::displayBattlefield() const {
    ostringstream oss;

    cout << "Display Battlefield" << endl << "    ";
    oss << "Display Battlefield" << endl << "    ";

    // Column headers
    for (int j = 0; j < battlefield_[0].size(); ++j) {
        cout << "  " << right << setfill('0') << setw(2) << j << " ";
        oss << "  " << right << setfill('0') << setw(2) << j << " ";
    }
    cout << endl;
    oss << endl;

    // Battlefield grid
    for (int i = 0; i < battlefield_.size(); ++i) {
        // Top border
        cout << "    ";
        oss << "    ";

        for (int j = 0; j < battlefield_[i].size(); ++j) {
            cout << "+----";
            oss << "+----";
        }
        cout << "+" << endl;
        oss << "+" << endl;

        // Row content
        cout << "  " << right << setfill('0') << setw(2) << i;
        oss << "  " << right << setfill('0') << setw(2) << i;

        for (int j = 0; j < battlefield_[0].size(); ++j) {
            if (battlefield_[i][j] == "") {
                cout << "|" << "    ";
                oss << "|" << "    ";
            }
            else {
                cout << "|" << left << setfill(' ') << setw(4) << battlefield_[i][j];
                oss << "|" << left << setfill(' ') << setw(4) << battlefield_[i][j];
            }
        }
        cout << "|" << endl;
        oss << "|" << endl;
    }
    // Bottom border
    cout << "    ";
    oss << "    ";

    for (int j = 0; j < battlefield_[0].size(); ++j) {
        cout << "+----";
        oss << "+----";
    }
    cout << "+" << endl;
    oss << "+" << endl;

    // Log all at once
    log(oss.str());
}

// Run one turn of the simulation
void Battlefield::runTurn() {
    if (currentTurn_ >= maxTurns_ || robots_.empty()) {
        return;
    }

    cout << "\n=== Starting Turn " << currentTurn_ + 1 << " ===" << endl;
    log("\n=== Turn " + to_string(currentTurn_ + 1) + " ===");

    cout << "Robots count: " << robots_.size() << endl;
    log("Robots count: " + to_string(robots_.size()));

    for (Robot* r : robots_) {
        if (r->x() < 0 || r->x() >= battlefieldCols_ || r->y() < 0 || r->y() >= battlefieldRows_) {
            cout << "Error: Robot " << r->id() << " is out of bounds at (" << r->x() << "," << r->y() << ")" << endl;
            log("Error: Robot " + r->id() + " is out of bounds at (" + to_string(r->x()) + "," + to_string(r->y()) + ")");
            return;
        }
    }

    vector<Robot*> activeRobots = robots_;

    for (Robot* robot : activeRobots) {
        if (robot->isAlive()) {
            log(robot->id() + " actions:");
            robot->actions(this);
        }
    }

    cout << "Finished all robot actions for turn " << currentTurn_ + 1 << endl; // DEBUG

    // Remove dead robots
    for (int i = 0; i < robots_.size(); ) {
        if (!robots_[i]->isAlive()) {
            destroyedRobots_.push(robots_[i]);
            robots_.erase(robots_.begin() + i);
        } else {
            ++i;
        }
    }

    // Process destroyed and waiting robots
    processRobotQueues();

    // Update battlefield state
    placeRobots();
    displayBattlefield();

    currentTurn_++;
    cout << "Turn completed. CurrentTurn is now " << currentTurn_ << endl;
    cout << "Turn " << currentTurn_ + 1 << " complete. Robots remaining: " << robots_.size() << endl;

}

void Battlefield::setLogFile(const string& filename) {
    if (logFile_.is_open()) {
        logFile_.close();
    }

    logFile_.open(filename);
    if (!logFile_.is_open()) {
        cout << "Failed to open log file: " << filename << endl;
    }
    else {
        logFileName_ = filename;
    }
}

bool Battlefield::openLogFile(const string& filename) {
    if (logFile_.is_open()) {
        logFile_.close();
    }

    logFile_.open(filename);

    if (!logFile_.is_open()) {
        cout << "Error while opening the log file: " << filename << endl;
        return false;
    }
    return true;
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

    if (battlefield_[robotPositionY][robotPositionX].empty()) {
        return false;
    }

    // Check if robot is hidden
    for (Robot* robot : robots_) {
        if (robot->x() == robotPositionX && robot->y() == robotPositionY && !robot->isHidden()) {
            return true;
        }
    }
    return false;
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

void Battlefield::replaceRobot(Robot* oldRobot, Robot* newRobot) {
    auto it = find(robots_.begin(), robots_.end(), oldRobot);
    if (it != robots_.end()) {
        *it = newRobot;
        delete oldRobot;
    }
}