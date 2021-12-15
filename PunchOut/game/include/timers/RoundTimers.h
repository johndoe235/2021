#ifndef __PUNCH_OUT_ROUND_TIMERS__
#define __PUNCH_OUT_ROUND_TIMERS__

#include "PunchOutTimer.h"

#include <cstdint>
#include <string>

class RoundTimer:public PunchOutTimer
{
public:
    RoundTimer();
    void onActive() override;
    bool shouldRefresh();
    std::string clockToString();
    private:
    bool Refresh=false;
    uint32_t previousSecond=0;
    int _lazyclock[4]{0};
    
    
};
#endif