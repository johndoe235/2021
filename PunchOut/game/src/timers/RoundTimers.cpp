#include "../../include/timers/RoundTimers.h"
#include "../../include/fight/Round.h"

RoundTimer::RoundTimer()
:PunchOutTimer(TIMER_TYPE_ID::ONE_SHOT,static_cast<uint32_t>(ROUND_TIMERS_ID::ROUND_TIMER))
{
   /// total_duration=181000;
     total_duration=60000;
}

bool RoundTimer::shouldRefresh()
{
    if(Refresh)
    {
    Refresh=false;
    return true;
    }
    else
    return false;
}
void RoundTimer::onActive()
{
    if(passed_s()>previousSecond)
    {
        Refresh=true;
        previousSecond=passed_s();
        bool one_left_over=false;

        if(_lazyclock[3]+1>9)
        {
            _lazyclock[3]=0;
            one_left_over=true;
            _lazyclock[2]++;
        }
        else
        {
            _lazyclock[3]++;
        }

        if(one_left_over)
        for(int i=2;i>=0;i--)
        {
            if(_lazyclock[i]>5)
            {
                _lazyclock[i]=0;
                if(i!=0)
                _lazyclock[i-1]++;
                else
                for(int j=0;j<3;j++)_lazyclock[j]=0;
                
            }
            
        }

    }
}
 std::string RoundTimer::clockToString()
 {
     std::string temp;
    temp.resize(5);
     temp[0]=static_cast<char>(_lazyclock[0]+'0');
     temp[1]=static_cast<char>(_lazyclock[1]+'0');
     temp[2]=':';
     temp[3]=static_cast<char>(_lazyclock[2]+'0');
     temp[4]=static_cast<char>(_lazyclock[3]+'0');

     return temp;
 }