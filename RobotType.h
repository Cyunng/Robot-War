#ifndef ROBOT_TYPE_H
#define ROBOT_TYPE_H
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include "GenericRobot.h"
#include "Battlefield.h"
using namespace std;

static bool upgradeUsedThisRound = false;
/////// Moving Upgrade ++ ///////
/////// HideBot ///////
class HideBot : public GenericRobot{
private:
    int hideUsesLeft_ = 3;
    bool isHidden_ = false;        
    int hideTurnsLeft_ = 0;
public:
    HideBot(string id, int x, int y) : GenericRobot(id, x, y){
        robotType_ = "HideBot";
    }
    void actionThink(Battlefield* battlefield) override {
        if(hideUsesLeft_ > 0 && !isHidden()){
            isHidden_ = true;
            hideTurnsLeft_ = 1; ///// hide for 1 turn
            hideUsesLeft_--;
            cout << id_ << "is now hidden! Remaining:" << hideUsesLeft_ << endl;
        }
    }
};

//////// JumpBot ///////
class JumpBot : public GenericRobot{
private:
    int jumpUsesLeft = 3;
public:
    JumpBot(string id, int x, int y): GenericRobot(id, x, y){
        robotType_ = "JumpBot" ;
    }
    void actionMove(Battlefield* battlefield) override{
        if(jumpUsesLeft > 0){
            int newX = x()+ 2;
            int newY = y()+ 2;
            if(newX < battlefield->getBattlefieldColumns() && newY < battlefield->getBattlefieldRows()){
            setLocation(newX, newY);
            cout << id_ << "Jumped to (" << newX << ", " << newY << ")" << endl;
            }
        }
        GenericRobot::actionMove(battlefield);
    }
};
/////// TeleportBot //////
/*class TeleportBot : public GenericRobot{
public:
    TeleportBot(string id, int x, int y) : GenericRobot(id, x, y){
        robotType_ = "TeleportBot";
    }
    void actionMove(Battlefield* battlefield) override{
        int newX = rand() % battlefield->getWidth();
        int newY = rand() % battlefield->getHeight();
        if (battlefield->isLocationEmpty(newX, newY)) {
            battlefield->moveRobot(this, newX, newY);
            cout << id_ << " Teleports to (" << newX << ", " << newY << ")" << endl;
        } else {
            GenericRobot::actionMove(battlefield);
        }
    }
};*/

/////// Shooting Upgrade ++ ///////
class LongShotBot : public GenericRobot{
protected:
    int fireRange_ = 1;
public:
    LongShotBot(string id, int x, int y) : GenericRobot(id, x, y){
        robotType_ = "LongShotBot";
        fireRange_ = 3;
    }
    void actionFire(Battlefield* battlefield) override {
        cout << id << "fire up to 3 units away!!\n";}
};

/////// SemiAutoBot ///////
class SemiAutoBot : public GenericRobot{

};
/////// ThirtyShortBot///////
class ThirtyShotBot : public GenericRobot {
protected:
    int shells_ = 10;
public:
    ThirtyShotBot(string id, int x, int y) : GenericRobot(id, x, y) {
        robotType_ = "ThirtyShotBot";
        shells_ = 30;
    }
    void actionFire(Battlefield* battlefield) override{
        if (shells_ > 0) {
            shells_--;
            cout << id << "fires a shot!! Remaining shells: " << shells_ << endl;
        }
        else{
            cout << id << "is out of ammo...." << endl;
        }
    }
};
/////// ShieldBot ///////
/*class ShieldBot : public GenericRobot{
private:
    int shieldHealth_ = 3;
    bool isShieldActive_ = false;
*/
/* public:
    ShieldBot(string id, int x, int y) : GenericRobot(id, x, y){
        robotType_ = "ShieldBot";
        shieldCharges_ = 3;
    }

    void actionThink(Battlefield* battlefield) override {
        if (!shieldActive_ && shieldCharges_ > 0) {
            shieldActive_ = true;
            shieldCharges_--;
            cout << id << "activated shield!! Remaining charges: " << shieldCharges_ << endl;
        }
    }

};*/


/////// Seeing Upgrade++ ///////
/////// ScoutBot ///////
class ScoutBot : public GenericRobot{

};
/////// TrackBot ///////
class TrackBot : public GenericRobot{

};
/////// RadarBot ///////
class RadarBot : public GenericRobot{

};





#endif