#ifndef __PUNCH_OUT_REFEREE__
#define __PUNCH_OUT_REFEREE__


#include "../boxers/Boxer.h"

enum class REFEREE_TIMERS_ID
{
    SAY_FIGHT_TIMER,
    WALK_AWAY_TIMER,
    WALK_IN_TIMER,
    COUNT_TIMER,
    DECIDE_TIMER,
};

enum class REFEREE_FRAMES
{
    PRE_COUNT_ZERO,
    PRE_COUNT_ONE,
    COUNT_ZERO,
    COUNT_ONE,
    COUNT_TWO,
    COUNT_THREE,
    COUNT_FOUR,
    COUNT_FIVE,
    COUNT_SIX,
    COUNT_SEVEN,
    COUNT_EIGHT,
    COUNT_NINE,
    COUNT_TEN,
    WALK_ZERO,
    WALK_ONE,
    FIGHT,
    HAND_UP,
    POINT_TO_PLAYER,
    KO,
    TKO,
    POINT_TO_OPPONENT


};

class Referee :public Boxer
{
    public:
    void init() override;
    void update() override;
    void sayFight();
    void walkAway();
    void walkIn();
    void decide(bool player_has_won);
    bool hasAnnouncedDecision();
    bool handleIncomingPunch(Punch& punch_type) override;
    void loadFrames() override;
    void count(bool isplayerDown);


    void  cheer() override;
    void  IntroAnimation()override;
    bool  isInNeutralPosition()override;
    void  moveToNeutralPosition()override;
    void  moveToBattlePosition()override;
    

    void setAnnounceDecisionToTrue();
    void changeFrame(REFEREE_FRAMES frame_name);
    REFEREE_FRAMES getFrameName();
    void setAction(REFEREE_TIMERS_ID id);
    bool finishedCount();
    void endCount();
    private:
    REFEREE_FRAMES CURRENT_FRAME;
    bool exitStatus=false;
    bool _finishedCount=false;
    bool _countOnlyOnce=false;
    bool _hasAnnouncedDecision=false;
    bool decide_only_once=false;
};

#endif