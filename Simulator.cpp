#include "Simulator.h"

#include <iostream>
#include <fstream>

using namespace std;

int Simulator::remainingRobots() const {
    int count = 0;
    for (Robot* r : battlefield_.getRobots()) {
        if (r->isAlive()) {
            count++;
        }
    }
    return count;
}

void Simulator::displayResults() const {
    ofstream fileStream;
    bool useFile = false;

    if (!outputfile_.empty()) {
        fileStream.open(outputfile_);
        if (fileStream.is_open()) {
            useFile = true;
        }
        else {
            cout << "Could not open output file!" << outputfile_ << endl;
        }
    }

    cout << "\n===== Battlefield Results =====" << endl;
    log("\n===== Battlefield Results =====");
    cout << "Total turns played: " << battlefield_.getCurrentTurn() << endl;
    log("Total turns played: " + to_string(battlefield_.getCurrentTurn()));
    cout << "Robots remaining: " << battlefield_.getRobotCount() << endl;
    log("Robots remaining: " + to_string(battlefield_.getRobotCount()));

    if (battlefield_.getRobotCount() == 1) { // If theres still robot
        Robot* winner = battlefield_.getRobotAt(0, 0); // Find actual winner
        cout << "Winner: " << winner->id() << " (" << winner->robotType() << ")" << endl;
        log("Winner: " + winner->id() + " (" + winner->robotType() + ")");
    }
    else if (battlefield_.getRobotCount() == 0) { // If theres no robot
        cout << "All robots destroyed!" << endl;
        log("All robots destroyed!");
    }
    else {
        cout << "Game ended with " << battlefield_.getRobotCount() << " robots still alive" << endl;
        log("Game ended with " + to_string(battlefield_.getRobotCount()) + " robots still alive");
    }
    
    /*
    cout << oss.str();
    if (useFile) {
        fileStream << oss.str();
        fileStream.close();
    }
    */
}

bool Simulator::initialize(const string& inputFile) {
    inputFile_ = inputFile;
    initialized_ = battlefield_.readFile(inputFile_);

    // Read and parse input file
    if (initialized_) {
        battlefield_.placeRobots();
    }
    return initialized_;
}

// To run the complete simulation
void Simulator::run() {
    /*
    ofstream fileOut("fileOutput1.txt");

    for (int t = 1; t <= maxTurns_; ++t) {
        string turnHeader = "=== Turn " + to_string(t) + " ===";
        cout << turnHeader << endl;
        battlefield_.log(turnHeader); // Logs to output file

        for (Robot* r : battlefield_.getRobots()) {
            if (r->isAlive()) {
                r->actions(&battlefield_); // Assume robot logs
            }
        }

        battlefield_.placeRobots();
        battlefield_.displayBattlefield();

        if (battlefield_.getRobotCount() <= 1) {
            cout << "Only one robot remains. Ending simulations." << endl;
            battlefield_.log("Only one robot remains. Ending simulations.");
            break;
        }
    }
    battlefield_.closeLogFile();
    */

    if (!initialized_) {
        cout << "Error: Simulation is not initialized" << endl;
        log("Error: Simulation is not initialized");
        return;
    }

    if (!outputfile_.empty()) {
        battlefield_.setLogFile(outputfile_);
    }

    cout << "===== Battlefield Started  =====" << endl;
    log("===== Battlefield Started  =====");
    
    /*
    if (logFile_.is_open()) {
        logFile_ << "===== Battlefield Started  =====" << endl;
    }

    cout << "Initial battlefield state:" << endl;

    if (logFile_.is_open()) {
        logFile_ << "Initial battlefield state:" << endl;
    }
    */

    battlefield_.displayBattlefield();

    while (battlefield_.getCurrentTurn() < battlefield_.getTotalTurns() && battlefield_.getRobotCount() > 1) {
        battlefield_.runTurn();
    }

    displayResults();
    log("Simulation complete. Results saved to " + outputfile_);
}

// To create output file
void Simulator::setOutputFile(const string& filename) {
    outputfile_ = filename;
    cout << "Output file set to: " << outputfile_ << endl;
}