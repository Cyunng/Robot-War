/**********|**********|**********|
Program: Robot_War.cpp / BattleField.h / GenericRobot.h / Robot.h / RobotType.h / Simulator.h
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
Name4: 
ID: 
Email: HERVIN.KUMAR.BALOO@student.mmu.edu.my
Phone: 018-9713530
Lecture Section: TC3L
Tutorial Section: T12L
**********|**********|**********/

#include "BattleField.h"
#include "GenericRobot.h"
#include "Robot.h"
#include "RobotType.h"
#include "Simulator.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    srand(1211109038);

    Battlefield battlefield;

    Robot* robotGenericRobot = new GenericRobot("GR01", 4, 4);

    cout << *robotGenericRobot << endl;
    robotGenericRobot->actions(&battlefield);

    delete robotGenericRobot;
    robotGenericRobot = nullptr;

    srand(1234567890);

    Robot* GR01 = new GenericRobot("GR01", 1, 1);
    Robot* GR02 = new GenericRobot("GR02", 2, 2);

    cout << "queue data structure: " << endl;
    queue<Robot*> destroyedRobots_;
    queue<Robot*> waitingRobots_;

    destroyedRobots_.push(new GenericRobot("GR03", 3, 3));
    destroyedRobots_.push(new GenericRobot("GR04", 4, 4));

    while(!destroyedRobots_.empty()) {
        Robot* r = destroyedRobots_.front();
        cout << "destroyedRobots_: Robot " << *r << endl;
        destroyedRobots_.pop();
    }

    cout << "waitingRobots_: ?" << endl;

    delete GR01;
    delete GR02;

    GR01 = nullptr;
    GR02 = nullptr;

    /*
    Simulator simulator;
    */
   
    return 0;
}

