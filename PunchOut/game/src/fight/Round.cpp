#include "../../include/fight/Round.h"
#include "../../../engine/include/Text.h"
//#include "../../include/timers/RoundTimers.h"

Round::Round()
{
    visual_clock=new Text();
    round_num=new Text();
    visual_clock->setPosition(690,40,25,25);
    visual_clock->write("00:00");

    round_num->setPosition(790,70,25,25);
    
}
Round::~Round()
{
    if(visual_clock!=nullptr)
    {
        delete visual_clock;
        visual_clock=nullptr;
    }
    if(round_num!=nullptr)
    {
        delete round_num;
        round_num=nullptr;
    }
}

bool Round::hasRoundEnded()
{
    return round_timer->isExpired();
}
void Round::roundStart()
{
    
        round_timer.reset(new RoundTimer());

        round++;
        round_num->write(std::to_string(round));

    round_timer->onStart();
}
void Round::roundPause()
{
    
}
void Round::update()
{
    if(!round_timer->isExpired())
    {
    round_timer->onActive();

    if(round_timer->shouldRefresh())
    {
        
        
        visual_clock->write(round_timer->clockToString());
    }
    }
}
void Round::draw()
{
    visual_clock->draw();
    round_num->draw();
}
int Round::currentRound()
{
    return round;
}