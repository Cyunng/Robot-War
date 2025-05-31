#include "Simulator.h"

#include <iostream>
#include <fstream>

using namespace std;

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

    ostream& out = useFile ? fileStream : cout;

    out << "\n===== Battlefield Results =====" << endl;
    out << "Total turns played: " << battlefield_.getCurrentTurn() << endl;
    out << "Robots remaining" << battlefield_.getRobotCount() << endl;

    if (battlefield_.getRobotCount() == 1) { // If theres still robot
        Robot* winner = battlefield_.getRobotAt(0, 0); // Find actual winner
        out << "Winner: " << winner->id() << " (" << winner->robotType() << ")" << endl;
    }
    else if (battlefield_.getRobotCount() == 0) { // If theres no robot
        out << "All robots destroyed!" << endl;
    }
    else {
        out << "Game ended with " << battlefield_.getRobotCount() << " robots still alive" << endl;
    }
    
    if (fileStream.is_open()){
        fileStream.close();
    }
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
        return;
    }

    if (!outputfile_.empty()) {
        battlefield_.setLogFile(outputfile_);
    }

    cout << "===== Battlefield Started  =====" << endl;
    cout << "Initial battlefield state:" << endl;
    battlefield_.displayBattlefield();

    while (battlefield_.getCurrentTurn() < battlefield_.getTotalTurns() && battlefield_.getRobotCount() > 1) {
        battlefield_.runTurn();
    }

    displayResults();
}

// To create output file
void Simulator::setOutputFile(const string& filename) {
    outputfile_ = filename;
}