#ifndef __PUNCH_OUT_REF_TIMERS__
#define __PUNCH_OUT_REF_TIMERS__
#include "PunchOutTimer.h"
#include <cstdint>
class Referee;

class sayFightTimer : public PunchOutTimer
{
public:
    sayFightTimer(Referee* ref);
    void onActive() override;
    
    void onExpire() override;
private:
Referee* mario;
};

class WalkAwayTimer : public PunchOutTimer
{
public:
    WalkAwayTimer(Referee* ref);
    void onActive() override;
    void onExpire() override;
private:
    Referee* mario;
    uint32_t last_frame_change=0;
};

class WalkInTimer : public PunchOutTimer
{
public:
    WalkInTimer(Referee* ref);
    void onActive() override;
    void onExpire() override;
private:
    Referee* mario;
    uint32_t last_frame_change=0;
};

class countTimer :public PunchOutTimer
{
    public:
    countTimer(Referee* ref,bool player=true);
    void onActive();
    void onExpire();
    private:
    Referee* mario;
    uint32_t animations[13];
    uint32_t lastAnimation=0;
    int count=2;
    bool _player;
};

class decideTimer : public PunchOutTimer
{
public:
    decideTimer(Referee* ref,bool has_player_won);
    void onActive()override;
    void onExpire() override;
private:
    Referee* mario;
    bool _player_has_won;

};

#endif
