/**********|**********|**********|
Program: TC3L_GJ_main.cpp / BattleField.h / GenericRobot.h / Robot.h / RobotType.h / Simulator.h
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

#include "Battlefield.h"
#include "GenericRobot.h"
#include "Robot.h"
#include "RobotType.h"
#include "Simulator.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <queue>

using namespace std;

void GenericRobot::actionThink(Battlefield* battlefield) {
    cout << id_ << " is thinking..." << endl;
}

void GenericRobot::actionLook(Battlefield* battlefield) {
    cout << id_ << " is scanning the battlefield at range of " << lookRange_ << "..." << endl;
}

void GenericRobot::actionFire(Battlefield* battlefield) {
    shells_--;
    cout << id_ << " fires! (Shells left: " << shells_ << ")" << endl;
}

void GenericRobot::actionMove(Battlefield* battlefield) {
    cout << id_ << " is moving to a new position..." << endl;
}

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
    cout << "Running simulation:" << endl;

    Simulator simulator;
    string inputfile = "fileInput1.txt";
    string outputfile = "fileOutput1.txt";

    if (simulator.initialize(inputfile)) {
        simulator.setOutputFile(outputfile);
        simulator.run();
    }
    else {
        cout << "Failed to initialize simulator!" << endl;
    }

    return 0;
}

