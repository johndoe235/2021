#include "../../include/fight/Referee.h"
#include "../../include/timers/RefereeTimers.h"

sayFightTimer::sayFightTimer(Referee* ref)
:PunchOutTimer(TIMER_TYPE_ID::ONE_SHOT,static_cast<uint32_t>(REFEREE_TIMERS_ID::SAY_FIGHT_TIMER)),mario(ref)
{
    total_duration=600;
    resetAction=false;
}
void sayFightTimer::onActive()
{
    if(remaining_ms()>500)
    {
        if(mario->getFrameName()!=REFEREE_FRAMES::PRE_COUNT_ZERO)
        {
            mario->changeFrame(REFEREE_FRAMES::PRE_COUNT_ZERO);
        }
    }
    else if(remaining_ms()>400)
    {
        if(mario->getFrameName()!=REFEREE_FRAMES::WALK_ZERO)
        {
            mario->changeFrame(REFEREE_FRAMES::WALK_ZERO);
        }
    }
    else if(remaining_ms()>300)
    {
        if(mario->getFrameName()!=REFEREE_FRAMES::PRE_COUNT_ZERO)
        {
            mario->changeFrame(REFEREE_FRAMES::PRE_COUNT_ZERO);
        }
    }
    else if(remaining_ms()>200)
    {
        if(mario->getFrameName()!=REFEREE_FRAMES::WALK_ONE)
        {
            mario->changeFrame(REFEREE_FRAMES::WALK_ONE);
        }
    }
    else if(remaining_ms()>0)
    {
        if(mario->getFrameName()!=REFEREE_FRAMES::FIGHT)
        {
            mario->changeFrame(REFEREE_FRAMES::FIGHT);
        }
    }
   
}
void sayFightTimer::onExpire()
{
    mario->setAction(REFEREE_TIMERS_ID::WALK_AWAY_TIMER);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

WalkAwayTimer::WalkAwayTimer(Referee* ref)
:PunchOutTimer(TIMER_TYPE_ID::ONE_SHOT,static_cast<uint32_t>(REFEREE_TIMERS_ID::WALK_AWAY_TIMER)),mario(ref)
{
    total_duration=1000;

}
void WalkAwayTimer::onActive()
{
    if(mario->getXposition()<860)
    mario->moveRight(3);

    if(passed_ms()>last_frame_change+200)
    {
        if(mario->getFrameName()!=REFEREE_FRAMES::WALK_ZERO)
        {

            mario->changeFrame(REFEREE_FRAMES::WALK_ZERO);
        }
        else
         mario->changeFrame(REFEREE_FRAMES::WALK_ONE);

    last_frame_change=passed_ms();
    }
    
}
void WalkAwayTimer::onExpire()
{
    mario->setXposition(860);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

countTimer::countTimer(Referee* ref,bool player)
:PunchOutTimer(TIMER_TYPE_ID::ONE_SHOT,static_cast<uint32_t>(REFEREE_TIMERS_ID::COUNT_TIMER)),mario(ref),_player(player)
{
    total_duration=14000;
    for(uint32_t i=static_cast<uint32_t>(REFEREE_FRAMES::PRE_COUNT_ZERO);i<=static_cast<uint32_t>(REFEREE_FRAMES::COUNT_TEN);i++)
    {
        animations[i]=i;
    }

}

void countTimer::onActive()
{
    if(passed_ms()>lastAnimation+500)
    {
        if(mario->getFrameName()==REFEREE_FRAMES::WALK_ONE)
        {
            if(count<13)
            mario->changeFrame(static_cast<REFEREE_FRAMES>(animations[count++]));
        }
        else
        mario->changeFrame(REFEREE_FRAMES::WALK_ONE);
        
        lastAnimation=passed_ms();
    }
    

}
void countTimer::onExpire()
{
    if(_player)
    mario->changeFrame(REFEREE_FRAMES::POINT_TO_OPPONENT);
    else
    mario->changeFrame(REFEREE_FRAMES::POINT_TO_PLAYER);

    mario->endCount();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


WalkInTimer::WalkInTimer(Referee* ref)
:PunchOutTimer(TIMER_TYPE_ID::ONE_SHOT,static_cast<uint32_t>(REFEREE_TIMERS_ID::WALK_IN_TIMER)),mario(ref)
{
    total_duration=3500;
}
void WalkInTimer::onActive()
{
    if(mario->getXposition()>640)
    {
    mario->moveLeft(3);
    }
    else
    expireNow();

    if(passed_ms()>last_frame_change+200)
    {
        if(mario->getFrameName()!=REFEREE_FRAMES::WALK_ZERO)
        {

            mario->changeFrame(REFEREE_FRAMES::WALK_ZERO);
        }
        else
         mario->changeFrame(REFEREE_FRAMES::WALK_ONE);

    last_frame_change=passed_ms();
    }
}
void WalkInTimer::onExpire()
{
    mario->setXposition(640);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


decideTimer::decideTimer(Referee* ref,bool has_player_won)
:PunchOutTimer(TIMER_TYPE_ID::ONE_SHOT,static_cast<uint32_t>(REFEREE_TIMERS_ID::DECIDE_TIMER)),mario(ref),_player_has_won(has_player_won)
{
    total_duration=3000;
}
void decideTimer::onActive()
{
    
    if(passed_s()>2)
    {
        
        if(_player_has_won)
        mario->changeFrame(REFEREE_FRAMES::POINT_TO_PLAYER);
        else
        mario->changeFrame(REFEREE_FRAMES::POINT_TO_OPPONENT);
    }
    else if(passed_s()>1)
    {
        mario->changeFrame(REFEREE_FRAMES::HAND_UP);
    }
    else if(passed_s()>0)
    {
        mario->changeFrame(REFEREE_FRAMES::PRE_COUNT_ZERO);
    }
}
void decideTimer::onExpire()
{
    mario->setAnnounceDecisionToTrue();
    
}
