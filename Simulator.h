#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "Battlefield.h"
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <string>
#include <cstdlib> // include this to use rand()

using namespace std;

class Simulator {
private:
    Battlefield battlefield_; // For the game world
    string inputFile_; // To input file
    string outputfile_; // To output log file 

public:
    Simulator() = default; // This is to construct a new simulator object

    ~Simulator() = default; // This is to destroy the simulator object

    void initalize(const string& inputFile) {
        inputFile_ = inputFile;

        srand(1211109038); // To seed random number generator with a fixed seed (We use leader's ID)

        if (!battlefield_.readFile(inputFile_)) {
            cout << "Failed to read the input file" << endl;
            return;
        }

        if (!battlefield_.placeRobots()) {
            cout << "Failed to place robots on the battlefield." << endl;
            return;
        }
    }

    // To run the complete simulation
    void run() {
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

private:
    // To display the final results in output file
    void displayResults() cosnt {
        ofstream* out = &cout;
        ofstream fileStream;

        if (!outputfile_.empty()) {
            fileStream.open(outputfile_);
            if (fileStream.is_open()) {
                out = &fileStream;
            } else {
                cout << "Could not open output file!" << outputfile_ << endl;
            }
        }
    
        *out << "\n===== Battlefield Results =====" << endl;
        *out << "Total turns played: " << battlefield_.getCurrentTurn() << endl;

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