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
class HideBot : public GenericRobot {
private:
    int hideUsesLeft_ = 3;
    bool isHidden_ = false;        
    int hideTurnsLeft_ = 0;

public:
    HideBot(string id, int x, int y);

    void actionThink(Battlefield* battlefield);

    void actionMove(Battlefield* battlefield);

    Robot* upgrade();
};

//////// JumpBot ///////
class JumpBot : public GenericRobot{
private:
    int jumpCount_ = 3;

public:
    JumpBot(string id, int x, int y);

    void actionMove(Battlefield* battlefield);

    Robot* upgrade();
};

/////// TeleportBot //////
class TeleportBot : public GenericRobot {
private:
    int teleportCharges_ = 3;
    
public:
    TeleportBot(string id, int x, int y);

    void actionMove(Battlefield* battlefield);

    Robot* upgrade();
};

/////// Shooting Upgrade ++ ///////
class LongShotBot : public GenericRobot{
private:
    int fireRange_ = 3;
    int shells_ = 10;

public:
    LongShotBot(string id, int x, int y);

    void actionFire(Battlefield* battlefield);

    Robot* upgrade();
};

/////// SemiAutoBot ///////
class SemiAutoBot : public GenericRobot{
    private:
    int burstCount_ = 3;
    int shells_ = 10;
    
public:
    SemiAutoBot(string id, int x, int y);

    void actionFire(Battlefield* battlefield);

    Robot* upgrade();
};

/////// ThirtyShortBot///////
class ThirtyShotBot : public GenericRobot {
private:
    int shells_;

public:
    ThirtyShotBot(string id, int x, int y);

    Robot* upgrade();
};

/////// ShieldBot ///////
class ShieldBot : public GenericRobot{
private:
    int shieldHealth_ = 3;
    bool shieldActive_ = false;
    
public:
    ShieldBot(string id, int x, int y);

    void actionThink(Battlefield* battlefield);

    void takeDamage();

    Robot* upgrade();
};

/////// Seeing Upgrade++ ///////
/////// ScoutBot ///////
class ScoutBot : public GenericRobot{
private:
    int scoutCharges_ = 3;
    
public:
    ScoutBot(string id, int x, int y);

    void actionLook(Battlefield* battlefield);

    Robot* upgrade();
};

/////// TrackBot ///////
class TrackBot : public GenericRobot{
private:
    int trackersLeft_ = 3;
    map<string, pair<int, int>> trackedRobots_;
    
public:
    TrackBot(string id, int x, int y);

    void actionLook(Battlefield* battlefield);

    Robot* upgrade();
};

/////// RadarBot ///////
class RadarBot : public GenericRobot{
private:
    int radarRange_ = 5;
    int radarCharges_ = 3;
    
public:
    RadarBot(string id, int x, int y);

    void actionLook(Battlefield* battlefield);

    Robot* upgrade();
};

#endif