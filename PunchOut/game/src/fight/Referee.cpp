#include "../../include/fight/Referee.h"
#include "../../include/timers/RefereeTimers.h"


void Referee::init()
{
  positions[INTRO_POSITION].x=640;
  positions[INTRO_POSITION].y=350;
  positions[NEUTRAL_POSITION].x=860;
  positions[NEUTRAL_POSITION].y=350;
  positions[BATTLE_POSITION].x=860;
  positions[BATTLE_POSITION].y=350;

  setPosition(640,350,120,140);

//if(sources.size()==0)
    loadFrames();
}
void Referee::loadFrames()
{
    int w=29, h=48,w2=38,h2=48;
    insert_AnimationFrame(2,64,w2,h);//PRE_COUNT_ZERO
    insert_AnimationFrame(39,64,w2,h);//PRE_COUNT_ONE
    insert_AnimationFrame(77,64,w2,h2);//COUNT_ZERO
    insert_AnimationFrame(125,64,w2,h2);//COUNT_ONE
    insert_AnimationFrame(172,64,w2,h2); //COUNT_TWO
    insert_AnimationFrame(218,64,w2,h2); //COUNT THREE
    insert_AnimationFrame(264,64,w2,h2); // COUNT FOUR
    insert_AnimationFrame(8,121,w2,h2);//COUNT FIVE
    insert_AnimationFrame(54,121,w2,h2); //COUNT SIX
    insert_AnimationFrame(101,121,w2,h2); //COUNT SEVEN
    insert_AnimationFrame(146,121,w2,h2); //COUNT EIGHT
    insert_AnimationFrame(193,121,w2,h2); //COUNT NINE
    insert_AnimationFrame(239,121,w2,h2);// COUNT TEN
    insert_AnimationFrame(3,8,w2,h); //WALK ZERO
    insert_AnimationFrame(38,8,w2,h); //WALK ONE
    insert_AnimationFrame(8,178,62,h2);//FIGHT
    insert_AnimationFrame(3,236,w2,h2);//HAND_UP
    insert_AnimationFrame(38,236,w2,h2);//POINT_TO_PLAYER
    insert_AnimationFrame(77,236,62,h2);//KO
    insert_AnimationFrame(148,236,62,h2);//TKO
    insert_AnimationFrame(8,294,w,h2);

    changeFrame(REFEREE_FRAMES::PRE_COUNT_ZERO);

}
void Referee::changeFrame(REFEREE_FRAMES frame_name)
{
    CURRENT_FRAME=frame_name;
    changeSource(static_cast<int32_t>(frame_name));
}
REFEREE_FRAMES Referee::getFrameName()
{
    return CURRENT_FRAME;
}
void Referee::update()
{
    if(action!=nullptr)
    {
        if(action->isActive())
        {
            action->onActive();
        }
        if(action->isExpired())
        {
            if(action->shouldActionReset())
            {
            action->onExpire();
            action.reset();
            }
            else
            {
                action->onExpire();
                
            }
            
        }
    }
}

void Referee::sayFight()
{
    if(action==nullptr)
    {
    
    action.reset(new sayFightTimer(this));
    action->onStart();
    }
}
void Referee::walkAway()
{
    if(action==nullptr)
    {
    
    action.reset(new WalkAwayTimer(this));
    action->onStart();
    }
}
void Referee::walkIn()
{
 if(action==nullptr)
    {
    
    action.reset(new WalkInTimer(this));
    action->onStart();
    }
}
void Referee::decide(bool player_has_won)
{
    if(!decide_only_once)
    {
        action.reset(new decideTimer(this,player_has_won));
        action->onStart();
        decide_only_once=true;
    }
}
bool Referee::hasAnnouncedDecision()
{
    return _hasAnnouncedDecision;
}
bool Referee::handleIncomingPunch([[maybe_unused]]Punch& punch_type)
{
    return false;  
}
void Referee::count(bool isplayerDown)
{
    if(action==nullptr && _countOnlyOnce==false)
    {
    _countOnlyOnce=true;
    action.reset(new countTimer(this,isplayerDown));
    action->onStart();
    }
}

void Referee::setAction(REFEREE_TIMERS_ID id)
{
    
     switch(id)
    {
        case REFEREE_TIMERS_ID::SAY_FIGHT_TIMER:
        action.reset(new sayFightTimer(this));
        break;
        case REFEREE_TIMERS_ID::WALK_AWAY_TIMER:
        action.reset(new WalkAwayTimer(this));
        break;
        case REFEREE_TIMERS_ID::WALK_IN_TIMER:
        action.reset(new WalkAwayTimer(this));
        break;
        case REFEREE_TIMERS_ID::COUNT_TIMER:
        action.reset(new WalkInTimer(this));
        break;
        default:
        ///std::cerr<<"Should not come here referee.cpp line 52\n";
        break;
        
       
    }
     action->onStart();
}
bool Referee::finishedCount()
{
    if(action==nullptr)
    return true;
    else
    return false;
}

void Referee::endCount()
{
    _finishedCount=true;
}
void  Referee::cheer()
{
    //referee does not cheer ,it's against boxing rules
}
void  Referee::IntroAnimation()
{
    ///no Intro Animation he's there to referee the fight not win hearts
}
bool  Referee::isInNeutralPosition()
{
    return(getXposition()==positions[NEUTRAL_POSITION].x && getYposition()==positions[NEUTRAL_POSITION].y);
}

void  Referee::moveToNeutralPosition()
{
    setAction(REFEREE_TIMERS_ID::WALK_IN_TIMER);
}
void Referee::moveToBattlePosition()
{
    //because he's not present during the actual fight he's there when someone is kncoked out.
    setAction(REFEREE_TIMERS_ID::WALK_AWAY_TIMER);
}
void Referee::setAnnounceDecisionToTrue()
{
    _hasAnnouncedDecision=true;
}

