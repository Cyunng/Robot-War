/**********|**********|**********|
Program: TC3L_GJ_main.cpp / BattleField.h / BattleField.cpp / GenericRobot.h / GenericRobot.cpp / Robot.h / Robot.cpp / RobotType.h / RobotType.cpp / Simulator.h / Simulator.cpp
Course: Object-Oriented Programming and Data Structures (OOPDS)
Trimester: 2420
Name1: Ng Chi Yuan
ID: 242UC244F5
Email: NG.CHI.YUAN@student.mmu.edu.my
Phone: 017-7855626
Name2: Jireh Chai E-Lok
ID: 242UC244M5
Email: JIREH.CHAI.ELOK@student.mmu.edu.my
Phone: 012-5131505
Name3: Lee Ru Zhen
ID: 243UC247CN
Email: LEE.RU.ZHEN@student.mmu.edu.my
Phone: 011-53530330
Name4: Hervin Kumar S/O Baloo
ID: 243UC247M4
Email: HERVIN.KUMAR.BALOO@student.mmu.edu.my
Phone: 018-9713530
Lecture Section: TC3L
Tutorial Section: T12L
**********|**********|**********/

#include "Simulator.h"

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;


int main()
{
    /*
    srand(1221109335); // To seed random number generator with a fixed seed (We use leader's ID)

    Battlefield battlefield;

    Robot* robotGenericRobot = new GenericRobot("GR01", 4, 4);
    cout << "Created robot: " << *robotGenericRobot << endl;

    robotGenericRobot->actions(&battlefield);

    delete robotGenericRobot;
    robotGenericRobot = nullptr;
    */

    /*
    // Test queues
    srand(1234567890);

    Robot* GR01 = new GenericRobot("GR01", 1, 1);
    Robot* GR02 = new GenericRobot("GR02", 2, 2);

    cout << "Queue data structure: " << endl;
    queue<Robot*> destroyedRobots_;
    queue<Robot*> waitingRobots_;

    // Add robots to destroyed queue
    destroyedRobots_.push(new GenericRobot("GR03", 3, 3));
    destroyedRobots_.push(new GenericRobot("GR04", 4, 4));

    // Show contents of destroyed queue
    cout << "Destroyed robots queue: " << endl;

    while(!destroyedRobots_.empty()) {
        Robot* r = destroyedRobots_.front();
        cout << "Destroyed Robots: Robot " << *r << endl;
        delete r; // Clean up memory
        destroyedRobots_.pop();
    }

    cout << "Waiting Robots: " << (waitingRobots_.empty() ? "Empty" : "Not empty") << endl;

    // Clean up
    delete GR01;
    delete GR02;

    GR01 = nullptr;
    GR02 = nullptr;
    */

    // Run Simulation

    srand(1234567890);

    
    cout << "Running simulation:" << endl;

    Simulator simulator;
    if (simulator.initialize("fileInput1.txt")) {
        simulator.setOutputFile("fileOutput1.txt");
        simulator.run();

        ifstream checkFile("fileOutput1.txt");

        if (!checkFile) {
            cout << "Warning: Output file was not created successfully!" << endl;
        }
        checkFile.close();
    }
    else {
        cout << "Failed to initialize simulator!" << endl;
        return 1;
    }


    return 0;
}

/*
void displayResults(const Battlefield& battlefield, ostream& out) {
    out << "\n===== Battlefield Results =====" << endl;
    out << "Total turns played: " << battlefield.getCurrentTurn() << endl;
    out << "Robots remaining: " << battlefield.getRobotCount() << endl;

    if (battlefield.getRobotCount() == 1) {
        Robot* winner = battlefield.getRobotAt(0, 0);
        out << "Winner: " << winner->id() << " (" << winner->robotType() << ")" << endl;
    }
    else if (battlefield.getRobotCount() == 0) {
        out << "All robots destroyed!" << endl;
    }
    else {
        out << "Game ended with " << battlefield.getRobotCount() << " robots still alive" << endl;
    }
}

int main() {
    srand(1234567890);
    cout << "Running simulation..." << endl;

    // Set up output file
    ofstream outputFile("fileOutput1.txt");
    if (!outputFile) {
        cerr << "Error: Could not create output file!" << endl;
        return 1;
    }

    // Initialize battlefield
    Battlefield battlefield;
    if (!battlefield.readFile("fileInput1.txt")) {
        cerr << "Failed to initialize battlefield!" << endl;
        return 1;
    }
    battlefield.placeRobots();

    // Set up logging
    battlefield.setLogFile("fileOutput1.txt");

    // Run simulation
    cout << "===== Battlefield Started =====" << endl;
    outputFile << "===== Battlefield Started =====" << endl;

    cout << "Initial battlefield state:" << endl;
    outputFile << "Initial battlefield state:" << endl;
    battlefield.displayBattlefield();

    while (battlefield.getCurrentTurn() < battlefield.getTotalTurns() && 
           battlefield.getRobotCount() > 0) {
        battlefield.runTurn();
    }

    // Display results to both console and file
    displayResults(battlefield, cout);
    displayResults(battlefield, outputFile);

    outputFile.close();
    cout << "Simulation complete. Results saved to fileOutput1.txt" << endl;

    return 0;
}
*/
