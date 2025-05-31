#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "Battlefield.h"

#include <iostream>
#include <fstream>

using namespace std;

class Simulator {
private:
    Battlefield battlefield_; // For the game world
    string inputFile_; // To input file
    string outputfile_; // To output log file 
    bool initialized_ = false; // Track initialization status

    // To display the final results in output file
    void displayResults() const;

public:
    Simulator() {} // This is to construct a new simulator object

    ~Simulator() {} // This is to destroy the simulator object

    bool initialize(const string& inputFile);

    // To run the complete simulation
    void run();

    // To create output file
    void setOutputFile(const string& filename);

    bool isInitialized() const {
        return initialized_;
    }
};

#endif