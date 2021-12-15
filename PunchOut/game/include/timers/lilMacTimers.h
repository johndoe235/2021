#ifndef __PUNCH_OUT_LILMAC_TIMERS__
#define __PUNCH_OUT_LILMAC_TIMERS__

#include "PunchOutTimer.h"

//forward declare
class lilMac;

namespace lilMacTimers
{

class dodgeTimer: public PunchOutTimer
{
public:
    dodgeTimer(lilMac* fighter);
    ~dodgeTimer();
    void onActive() override;
    private:
        lilMac* mac;
       int desired_distance;
       bool shouldReturn=false;

       int startingX;
       int startingY;
    

};

class defaultTimer:public PunchOutBehaviorTimer
{
    public:
    defaultTimer(lilMac* fighter);
    ~defaultTimer();
    void onActive() override;
     
    private:
    void randomize_step();
    lilMac* mac;
    int32_t x_offset=0;
    uint32_t lastanimation=0;
};

class bodyShotTimer:public PunchOutTimer
{
    public:
    bodyShotTimer(lilMac* fighter);
    ~bodyShotTimer();
    void onActive() override;
    private:
    bool activated_once=false;
    lilMac* mac;
};

class headShotTimer:public PunchOutTimer
{
     public:
    headShotTimer(lilMac* fighter);
    ~headShotTimer();
    void onActive() override;
    private:
    lilMac* mac;
    bool hasMovedOnce=false;
    bool hasMovedTwice=false;
    bool activated_once=false;
};

class superShotTimer:public PunchOutTimer
{
 public:
    superShotTimer(lilMac* fighter);
    ~superShotTimer();
    void onActive() override;
    void onExpire() override;
    void onStart() override;
private:
    lilMac* mac;
};


class tiredTimer:public PunchOutBehaviorTimer
{
    public:
    tiredTimer(lilMac* fighter);
    void onActive()override;
    void onExpire()override;
    private:
    lilMac* mac;
    
};
class punchedTimer:public PunchOutTimer
{
    public:
    punchedTimer(lilMac* fighter);
    ~punchedTimer();
    void onActive()override;
    void onExpire() override;
    
    
    private:
    lilMac* mac;
};

class cheerTimer:public PunchOutTimer
{
public:
    cheerTimer(lilMac* fighter);
    ~cheerTimer();
    void onActive() override;
    void onExpire() override;
private:
    lilMac* mac;
};
class KO_dTimer: public PunchOutTimer
{
public:
     KO_dTimer(lilMac* fighter);
     ~KO_dTimer();

     void onActive()override;
     void onExpire() override;
     
     void onStart() override;
private:
     lilMac* mac;

};

class canDodgeAfterBlockTimer: public PunchOutTimer //TO DO: Must be activated after player releases the block key
{
    public:
     canDodgeAfterBlockTimer();
    


};

class blockTimer: public PunchOutTimer //TO DO: Must deactive it after player releases the block key
{
    public:
    blockTimer(lilMac* fighter);
    ~blockTimer();

    void onActive() override;
    void onStart() override;
    private:
    bool animate_only_once=false;
    lilMac* mac;
};

class dodgeAfterBlockTimer: public PunchOutTimer //Must add TIMER_ID so to identify if this canDodgeAfterBlockTimer is the one active
{
public:
     dodgeAfterBlockTimer(lilMac* fighter);

    void onActive() override;
    void onExpire() override;
    void onStart() override;
    private:
    lilMac* mac;
};


class walkToNeutralPosition :public PunchOutTimer
{
public:
    walkToNeutralPosition(lilMac* fighter,int destX,int destY);
    void onActive() override;
    void onExpire() override;
private:
    uint32_t last_animation=0;
    uint32_t animations[2];
    int frame_count=2;
    int current_frame=0;
    lilMac* mac;
    int desiredX,desiredY;
  


};
class walkToBattlePosition :public PunchOutTimer
{
    public:
    walkToBattlePosition(lilMac* fighter,int destX,int destY);
    void onActive() override;
    void onExpire() override;
    private:
    uint32_t animations[2];
    int frame_count=2;
    uint32_t last_animation=0;
    int current_frame=0;
    lilMac* mac;
    int desiredX,desiredY;
   
};
class portraitAnimationTimer :public PunchOutTimer
{
    public:
    portraitAnimationTimer(lilMac* fighter);
    void onActive() override;
    private:
    lilMac* mac;
};

}
#endif