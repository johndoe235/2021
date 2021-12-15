#include "../../include/fight/Ring.h"

Ring::Ring()
{
    allocate_source();
   // allocate_texture();


    setSourcePosition(2,2,256,224);
}
Ring::~Ring()
{
    deallocate_source();
   // deallocate_texture();
}
/*
void Ring::startRound()
{
    round_timer.reset(new RoundTimer());
}
bool Ring::hasRoundEnded()
{
    if( round_timer!=nullptr)
    return  round_timer->isExpired();
    else
    return true;
    

}


*/

