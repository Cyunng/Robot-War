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

    if (battlefield_.getRobotCount() == 1) { // If theres still robot
        out << "Winner: Last remaining robot" << endl;
    }
    else if (battlefield_.getRobotCount() == 0) { // If theres no robot
        out << "No winner: All robots destroyed" << endl;
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
    initialized_ = false;

    srand(1221109335); // To seed random number generator with a fixed seed (We use leader's ID)

    // Read and parse input file
    if (!battlefield_.readFile(inputFile_)) {
        cout << "Failed to read the input file" << endl;
        return false;
    }

    initialized_ = true;
    return true;
}

// To run the complete simulation
void Simulator::run() {
    if (!initialized_) {
        cout << "Error: Simulation is not initialized" << endl;
        return;
    }

    cout << "===== Battlefield Started  =====" << endl;
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

bool Simulator::isInitialized() const {
    return initialized_;
}