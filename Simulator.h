#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Battlefield
{
private:
    int battefieldColumns = -1;
    int battlefieldRows = -1;
    
    int currentTurn = 0; // Current turn count 
    int totalTurns = -1; //  Total simulation turns 

    int robotCount = -1; // Number of robots
    std::vector<Robot*> robots;
    std::queue<Robot*> destroyedRobots;
    std::queue<Robot*> waitingRobots;
    
    std::vector<std::vector<std::string>> grid; // To display battlefield

public:
    int getBattlefieldColumns() const {return battlefieldColumns;}
    int getBattlefieldRows() const {return battlefieldRows;}
    int getTotalTurns() const {return totalTurns;}
    int getRobotCount() const {return robotCount;}

    void readFile(string& filename) // Read input file
    {
    }

    void placeRobots() { // To place robot at the battlefield
        grid.assign(battlefieldRows, std::vector<std::string>(battlefieldColumns, "*"));

        for (size_t i = 0; i < robots.size(); ++i) {
            int x = robots[i]->x();
            int y = robots[i]->y();
            
            if (y >= 0 && y < battlefieldRows && x >= 0 && x < battlefieldColumns) {
                grid[y][x] = robots[i]->id(); //To place robot on grid
            } else {
                std::cout << "Error: Invalid location for Robot!" << robots[i]->id() << "\n";
                std::exit(1);
            }
        }
    }
};  

#endif