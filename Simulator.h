#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "Battlefield.h"
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

class Simulator {
private:
    Battlefield battlefield_; // For the game world
    string inputFile_; // To input file
    string outputfile_; // To output log file 
    bool initialized_ = false; // Track initialization status

public:
    Simulator() {} // This is to construct a new simulator object

    ~Simulator() {} // This is to destroy the simulator object

    bool initialize(const string& inputFile) {
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
    void run() {
        if (!initialized_) {
            cout << "Error: Simulation is not nitialized" << endl;
        }

        cout << "===== Battlefield Started  =====" << endl;
        battlefield_.displayBattlefield();

        while (battlefield_.getCurrentTurn() < battlefield_.getTotalTurns() && battlefield_.getRobotCount() > 1) {
            battlefield_.runTurn();
        }

        displayResults();
    }

    // To create output file
    void setOutputFile(const string& filename) {
        outputfile_ = filename;
    }

    bool isInitialized() const {
        return initialized_;
    }

private:
    // To display the final results in output file
    void displayResults() const {
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
            *out << "Winner: Last remaining robot" << endl;
        } else if (battlefield_.getRobotCount() == 0) { // If theres no robot
            *out << "No winner: All robots destroyed" << endl;
        } else {
            *out << "Game ended with " << battlefield_.getRobotCount() << " robots still alive" << endl;
        }
        
        if (fileStream.is_open()){
            fileStream.close();
        }
    }
};

#endif