#include "../../include/timers/PunchOutTimer.h"
#include "../../../engine/include/Timer.h"


PunchOutTimer::PunchOutTimer(TIMER_TYPE_ID ID,uint32_t Id)
:id(Id),type_id(ID),active_status(false)
{
    loops=0;
}
PunchOutTimer::~PunchOutTimer()
{
    
}
void PunchOutTimer::onActive()
{

}
void PunchOutTimer::onStart()
{   
    start_timer(total_duration);
}
void  PunchOutTimer::onExpire()
{
    active_status=false;
}
bool  PunchOutTimer::shouldActionReset()
{
    return resetAction;
}
void PunchOutTimer::start_timer(int32_t Duratation)
{
    active_status=true;
    total_duration=Duratation;
    start_time=timer::GetTicks();
}

uint32_t  PunchOutTimer::remaining_ms()
{
    uint32_t now=timer::GetTicks();
    uint32_t elapsedTime=now-start_time;
    
    int32_t current_duration=total_duration-elapsedTime;

    if(current_duration<0)
    current_duration=0;
    
    

    return current_duration;
}
uint32_t PunchOutTimer::passed_ms()
{
    uint32_t now=timer::GetTicks();
    uint32_t elapsedTime=now-start_time;

    return elapsedTime;
}
uint32_t PunchOutTimer::passed_s()
{
    return passed_ms()/1000;
}

uint32_t  PunchOutTimer::remaining_s()
{
    return remaining_ms()/1000;
}
void PunchOutTimer::reset_timer()
{
    start_time=timer::GetTicks();
    
}
bool PunchOutTimer::isExpired()
{   
    if(isPaused)
    return false;

    if(remaining_ms()==0)
    {
        if(type_id==TIMER_TYPE_ID::ONE_SHOT)
        return true;
        else //if REPEATING
        {
           if(loops==-1)
           {
                reset_timer();
                return false;
           }
           else
           {
               if(loops>0)
               {
                    loops--;
                    reset_timer();   
               }
               else
               return true;
           }
        }
    }

    return false;
}
bool  PunchOutTimer::isActive()
{
    if(isPaused)
    return false;

    return active_status;
}

void PunchOutTimer::expireNow()
{
    total_duration=0;
}
void PunchOutTimer::pauseTimer()
{
    pause_time=timer::GetTicks();
    isPaused=true;

}
void PunchOutTimer::resumeTimer()
{
    uint32_t resume_time=timer::GetTicks();
    start_time=start_time +(pause_time-resume_time);
    isPaused=false;
}
PunchOutBehaviorTimer::PunchOutBehaviorTimer(TIMER_TYPE_ID ID,uint32_t Id)
:PunchOutTimer(ID,Id)
{
    
}
 PunchOutBehaviorTimer::~PunchOutBehaviorTimer()
 {

 }


   
