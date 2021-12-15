#ifndef __PUNCH_OUT_TIMER__
#define __PUNCH_OUT_TIMER__

#include <cstdint>

enum class TIMER_TYPE_ID 
{
    ONE_SHOT,
    REPEATING
};

class PunchOutTimer
{
public:
    PunchOutTimer(TIMER_TYPE_ID Type_ID,uint32_t ID);
    virtual ~PunchOutTimer(); //if a timer can be stopped by outside forces.A deconstructor should be created to handle such behavior
    void virtual onActive(); //what should happen while the timer is active
    void virtual onExpire(); //what should happen when the timer expires naturally
    void virtual onStart();
    bool  shouldActionReset(); // should be false if the timer triggers another timer after him. resetAction=false; true by default
   
    uint32_t remaining_ms(); //remaining time in milliseconds
    uint32_t remaining_s(); //remaining time in seconds

    uint32_t passed_ms(); //remaining time in milliseconds
    uint32_t passed_s(); //remaining time in seconds
    void reset_timer();
    void start_timer(int32_t duration);
    void expireNow();
    
    bool  isExpired();
    bool  isActive();

    void pauseTimer(); //pause button,pauses the timer
    void resumeTimer(); ///resumes the timer
   

 const uint32_t id;

protected:
    uint32_t total_duration=0;
    int32_t loops; //how many times a repeating timer 
    bool resetAction=true;
private:
    TIMER_TYPE_ID type_id;
   
    bool active_status=false;
    bool isPaused=false;
    uint32_t start_time=0; 
    uint32_t pause_time=0; 
};

class PunchOutBehaviorTimer:public PunchOutTimer
{
    public:
    PunchOutBehaviorTimer(TIMER_TYPE_ID Type_ID,uint32_t ID);
    virtual ~PunchOutBehaviorTimer();

};
#endif