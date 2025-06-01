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
        for (Robot* r : battlefield_.getRobots()) { // Find the winner
            if (r->isAlive()) {
                cout << "Winner: " << r->id() << " (" << r->robotType() << ")" << endl;
                log("Winner: " + r->id() + " (" + r->robotType() + ")");
                break;
            }
        }
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
    if (!initialized_) {
        cout << "Error: Simulation is not initialized" << endl;
        log("Error: Simulation is not initialized");
        return;
    }

    if (!outputfile_.empty()) {
        battlefield_.setLogFile(outputfile_);
    }

    battlefield_.openLogFile("fileOutput1.txt");

    cout << "===== Battlefield Started  =====" << endl;
    battlefield_.log("===== Battlefield Started  =====");
    

    battlefield_.displayBattlefield();
    
    cout << "Loop start: currentTurn = " + to_string(battlefield_.getCurrentTurn()) << endl;

    while (battlefield_.getCurrentTurn() < battlefield_.getTotalTurns() && battlefield_.getRobotCount() > 1) {
        cout << "Starting turn " << battlefield_.getCurrentTurn() + 1 << endl;
        battlefield_.runTurn();
        cout << "Completed turn " << battlefield_.getCurrentTurn() << endl;
        cout << "Robots remaining: " << battlefield_.getRobotCount() << endl;
    }

    displayResults();
    battlefield_.log("Simulation complete. Results saved to " + outputfile_);
}

// To create output file
void Simulator::setOutputFile(const string& filename) {
    outputfile_ = filename;
    if (!battlefield_.openLogFile(filename)) {
        cout << "Failed to open output file: " << filename << endl;
    }
    cout << "Output file set to: " << outputfile_ << endl;
    
}