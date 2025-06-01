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
    // Run Simulation

    srand(1234567890);

    
    cout << "Running simulation:" << endl;

    Simulator simulator;
    
    if (simulator.initialize("fileInput3.txt")) {
        simulator.setOutputFile("fileOutput3.txt");
        simulator.run();

        ifstream checkFile("fileOutput3.txt");

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
