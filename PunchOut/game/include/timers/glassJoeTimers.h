#ifndef __PUNCH_OUT_GLASS_JOE_TIMERS__
#define __PUNCH_OUT_GLASS_JOE_TIMERS__

#include "PunchOutTimer.h"
#include <utility>
//forward declare
class glassJoe;

namespace glassJoeTimers
{

class defaultTimer:public PunchOutTimer
{
public:
    defaultTimer(glassJoe* fighter);
    void onActive()override;
private:
    glassJoe* joe;
    
};

class straightPunchTimer: public PunchOutTimer
{
public:
    straightPunchTimer(glassJoe* fighter);
    ~straightPunchTimer();
    void onActive()override;
    void onExpire()override;

private:
    glassJoe* joe;
};

class hookPunchTimer:public PunchOutTimer
{
public:
    hookPunchTimer(glassJoe* fighter);
    void onActive()override;
    void onExpire() override;
private:
    glassJoe* joe;

};
class blockedDownTimer: public PunchOutTimer
{
public:
    blockedDownTimer(glassJoe* fighter);
    ~blockedDownTimer();
    void onActive()override;
    
private:
    glassJoe* joe;

};
class blockedUpTimer: public PunchOutTimer
{
public:
    blockedUpTimer(glassJoe* fighter);
    ~blockedUpTimer();
    void onActive()override;
    
private:
    glassJoe* joe;

};
class bodyPunchedTimer:public PunchOutTimer
{
public:
    bodyPunchedTimer(glassJoe* fighter);
    ~bodyPunchedTimer();
    void onActive()override;
    void onExpire() override;
private:
    glassJoe* joe;

};
class headPunchedTimer: public PunchOutTimer
{
public:
    headPunchedTimer(glassJoe* fighter);
    ~headPunchedTimer();
    void onActive()override;
    void onExpire()override;
private:
glassJoe* joe;
};

class KO_fallTimer:public PunchOutTimer
{
public:
    KO_fallTimer(glassJoe* fighter);
    void onActive() override;
private:
    glassJoe* joe;
};

class KO_getUpTimer : public PunchOutTimer
{
    public:
    KO_getUpTimer(glassJoe* fighter);
    void onActive() override;
    void onExpire() override;
private:
    glassJoe* joe;
};

class cheerTimer:public PunchOutTimer
{
public:
    cheerTimer(glassJoe* fighter);
    void onActive() override;
    void onExpire() override;
private:
    glassJoe* joe;
   

};




class guardUpTimer: public PunchOutTimer
{
public:
    guardUpTimer(glassJoe* fighter);
    void onActive()override;
private:
glassJoe* joe;
};

class guardDownTimer: public PunchOutTimer
{
public:
    guardDownTimer(glassJoe* fighter);
    void onActive()override;
private:
glassJoe* joe;
};

class BehaviorTimer:public PunchOutBehaviorTimer
{
public:
    BehaviorTimer(glassJoe* fighter);
    void onActive() override;

private:
glassJoe* joe;
};

class IntroTimer :public PunchOutTimer
{
public:
    IntroTimer(glassJoe* fighter);
    void onActive() override;
    void onExpire() override;
private:
glassJoe* joe;
};
class walkToNeutralPosition :public PunchOutTimer
{
public:
    walkToNeutralPosition(glassJoe* fighter,int destX,int destY);
    void onActive() override;
    void onExpire() override;
private:
    uint32_t last_animation=0;
    uint32_t animations[6];
    int frame_count=6;
    int current_frame=0;
    glassJoe* joe;
    int desiredX,desiredY;



};
class walkToBattlePosition :public PunchOutTimer
{
    public:
    walkToBattlePosition(glassJoe* fighter,int destX,int destY);
    void onActive() override;
    void onExpire() override;
    private:
    uint32_t animations[3];
    int frame_count=3;
    uint32_t last_animation=0;
    int current_frame=0;
    glassJoe* joe;
    int desiredX,desiredY;
    
};
class portraitAnimationTimer :public PunchOutTimer
{
    public:
    portraitAnimationTimer(glassJoe* fighter);
    void onActive() override;
    private:
    glassJoe* joe;
};


}




#endif
