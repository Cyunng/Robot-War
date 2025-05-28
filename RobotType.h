#ifndef ROBOT_TYPE_H
#define ROBOT_TYPE_H

#include "GenericRobot.h"
#include "Battlefield.h"

#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

/////// Moving Upgrade ++ ///////
/////// HideBot ///////
class HideBot : public GenericRobot{
public:
    HideBot(string id ="", int x = -1, int y = -1) : GenericRobot(id, x, y){
        setRobotType("HideBot");
        setLocation(x, y);
    }
    void actionThink(Battlefield* battlefield) override {
        if(!isHidden()){
            cout << id() << "is now hidden!" << endl;
        }
    }
    Robot* upgrade() override {
        return new JumpBot(id(), x(), y());
    }
};

//////// JumpBot ///////
class JumpBot : public GenericRobot{
public:
    JumpBot(string id = "", int x = -1, int y = -1): GenericRobot(id, x, y){
        setRobotType("JumpBot");
        setLocation(x, y);
    }
    void actionMove(Battlefield * battlefield) override{
        int newX = x()+ 2;
        int newY = y()+ 2;
        if(newX < battlefield->getBattlefieldColumns() && newY < battlefield->getBattlefieldRows()){
            setLocation(newX, newY);
            cout << id() << "Jumped to (" << newX << ", " << newY << ")" << endl;
        }
    }
    Robot* upgrade() override{
        return new TeleportBot(id(), x(), y());
    }
};
/////// TeleportBot //////


/////// Shooting Upgrade ++ ///////
/////// ShieldBot ///////
/* class ShieldBot : public GenericRobot{
private:
    int shieldHealth_ = 3;

public:
    ShieldBot(string id = "", int x = -1, int y = -1) : GenericRobot(id, x, y){
        setRobotType("ShieldBot");
        setLocation(x, y);
    }
    void activateShield(){
        if(shieldHealth_ > 0 && !isShielded()){
            shieldHealth_--;
            shieldActive_ = true;
            cout << id() << "Defend! Charges left: " << shieldHealth_ << endl;
        }
    }
    void actionThink(Battlefield* battlefield) override {
        if (!isShielded()) {
            activateShield();
        }
    }

    void takeHit() {
        if (shieldActive_) {
            shieldActive_ = false;
            cout << id() << "'s SHIELD blocked the attack!" << endl;
        } else {
            reduceLife();
        }
    }

    Robot* upgrade() override {
        return new RadarBot(id(), x(), y());
    }
};
*/





#endif